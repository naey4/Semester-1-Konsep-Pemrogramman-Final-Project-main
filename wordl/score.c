#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "score.h"

#define SCORE_FILE "scores.json"

/* helper: get today's date as YYYY-MM-DD */
static void today_date(char *out, size_t n) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(out, n, "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
}

/* find entry pointer or NULL */
static ScoreEntry* find_entry(ScoreList *sl, char mode, const char *name) {
    for (int i=0;i<sl->count;++i) {
        if (sl->entries[i].mode == mode && strcasecmp(sl->entries[i].name, name) == 0) return &sl->entries[i];
    }
    return NULL;
}

/* --- JSON helpers (simple, tailored to our format) --- */
/* parse int value from object substring for key (e.g. "games_played":123) */
static int extract_json_int(const char *obj, const char *key, int *out) {
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "\"%s\"", key);
    char *p = strstr(obj, pattern);
    if (!p) return 0;
    p = strchr(p, ':');
    if (!p) return 0;
    ++p;
    while (*p==' ' || *p=='\t') ++p;
    int val = 0;
    if (sscanf(p, "%d", &val) == 1) { *out = val; return 1; }
    return 0;
}

/* parse string value from object substring for key (e.g. "name":"Alice") */
static int extract_json_str(const char *obj, const char *key, char *out, size_t outsz) {
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "\"%s\"", key);
    char *p = strstr(obj, pattern);
    if (!p) return 0;
    p = strchr(p, ':');
    if (!p) return 0;
    p++;
    while (*p==' ' || *p=='\t') ++p;
    if (*p != '"') return 0;
    p++;
    char *q = strchr(p, '"');
    if (!q) return 0;
    size_t len = (size_t)(q - p);
    if (len >= outsz) len = outsz - 1;
    strncpy(out, p, len);
    out[len] = '\0';
    return 1;
}

/* parse single object content between { ... } into ScoreEntry */
static int parse_object_to_entry(const char *obj_start, const char *obj_end, ScoreEntry *e) {
    size_t len = obj_end - obj_start + 1;
    char *buf = (char*)malloc(len+1);
    if (!buf) return 0;
    strncpy(buf, obj_start, len);
    buf[len] = '\0';

    char tmp[MAKS_PLAYERNAME];
    memset(e, 0, sizeof(ScoreEntry));

    if (!extract_json_str(buf, "name", tmp, sizeof(tmp))) { free(buf); return 0; }
    strncpy(e->name, tmp, MAKS_PLAYERNAME-1);
    e->name[MAKS_PLAYERNAME-1] = '\0';

    if (!extract_json_str(buf, "mode", tmp, sizeof(tmp))) { free(buf); return 0; }
    e->mode = tmp[0];

    extract_json_int(buf, "games_played", &e->games_played);
    extract_json_int(buf, "wins", &e->wins);
    extract_json_int(buf, "best_attempts", &e->best_attempts);
    extract_json_int(buf, "total_attempts", &e->total_attempts);
    if (!extract_json_str(buf, "last_win", e->last_win, DATE_STRLEN)) e->last_win[0] = '\0';

    free(buf);
    return 1;
}

void load_scores(ScoreList *sl) {
    sl->count = 0;
    FILE *f = fopen(SCORE_FILE, "r");
    if (!f) return; /* not found -> empty */
    /* read full file into memory */
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = (char*)malloc(sz+1);
    if (!buf) { fclose(f); return; }
    fread(buf, 1, sz, f);
    buf[sz] = '\0';
    fclose(f);

    /* find objects {} */
    char *p = buf;
    while ((p = strchr(p, '{')) != NULL) {
        char *q = strchr(p, '}');
        if (!q) break;
        if (sl->count < MAX_SCORES) {
            ScoreEntry e;
            if (parse_object_to_entry(p+1, q-1, &e)) {
                sl->entries[sl->count++] = e;
            }
        }
        p = q+1;
    }
    free(buf);
}

static void write_json_string(FILE *f, const char *key, const char *val) {
    fprintf(f, "\"%s\":\"%s\"", key, val ? val : "");
}

void save_scores(const ScoreList *sl) {
    FILE *f = fopen(SCORE_FILE, "w");
    if (!f) {
        fprintf(stderr, "Gagal membuka %s untuk menulis\n", SCORE_FILE);
        return;
    }
    fprintf(f, "[\n");
    for (int i=0;i<sl->count;++i) {
        const ScoreEntry *e = &sl->entries[i];
        fprintf(f, "  {\n");
        fprintf(f, "    ");
        write_json_string(f, "mode", (char[]){e->mode, '\0'});
        fprintf(f, ",\n    ");
        write_json_string(f, "name", e->name);
        fprintf(f, ",\n    ");
        fprintf(f, "\"games_played\":%d,\n    \"wins\":%d,\n    \"best_attempts\":%d,\n    \"total_attempts\":%d,\n    ",
                e->games_played, e->wins, e->best_attempts, e->total_attempts);
        write_json_string(f, "last_win", e->last_win);
        fprintf(f, "\n  }%s\n", (i==sl->count-1) ? "" : ",");
    }
    fprintf(f, "]\n");
    fclose(f);
}

/* record game: won (1) or lost (0). attempts_used is attempts taken (if lost, attempts_used == max attempts) */
void record_game_result(ScoreList *sl, char mode, const char *name, int attempts_used, int won) {
    ScoreEntry *e = find_entry(sl, mode, name);
    if (!e) {
        if (sl->count >= MAX_SCORES) {
            fprintf(stderr, "Leaderboard penuh, tidak bisa mencatat skor baru.\n");
            return;
        }
        /* create new entry */
        ScoreEntry ne;
        ne.mode = mode;
        strncpy(ne.name, name, MAKS_PLAYERNAME-1); ne.name[MAKS_PLAYERNAME-1] = '\0';
        ne.games_played = 0;
        ne.wins = 0;
        ne.best_attempts = 0;
        ne.total_attempts = 0;
        ne.last_win[0] = '\0';
        sl->entries[sl->count++] = ne;
        e = &sl->entries[sl->count-1];
    }
    e->games_played += 1;
    e->total_attempts += attempts_used;
    if (won) {
        e->wins += 1;
        if (e->best_attempts == 0 || attempts_used < e->best_attempts) e->best_attempts = attempts_used;
        today_date(e->last_win, DATE_STRLEN);
    }
    save_scores(sl);
}

/* show top N (5) for mode */
void show_top_scores(const ScoreList *sl, char mode) {
    /* collect */
    ScoreEntry tmp[MAX_SCORES];
    int c = 0;
    for (int i=0;i<sl->count;++i) {
        if (sl->entries[i].mode == mode) tmp[c++] = sl->entries[i];
    }
    if (c==0) {
        printf("Belum ada skor untuk mode %c.\n", mode);
        return;
    }
    /* sort by best_attempts (non-zero first, smaller better), then by wins desc */
    /* Because using C99 blocks is non-portable, implement manual sort: */
    for (int i=0;i<c-1;++i) {
        for (int j=i+1;j<c;++j) {
            int ai = tmp[i].best_attempts==0 ? 1000000 : tmp[i].best_attempts;
            int aj = tmp[j].best_attempts==0 ? 1000000 : tmp[j].best_attempts;
            if (aj < ai || (aj==ai && tmp[j].wins > tmp[i].wins)) {
                ScoreEntry sw = tmp[i]; tmp[i] = tmp[j]; tmp[j] = sw;
            }
        }
    }

    printf("== Top skor (mode %c) ==\n", mode);
    int limit = c < 5 ? c : 5;
    for (int i=0;i<limit;++i) {
        printf("%d. %s - best: %d attempts, wins: %d, games: %d, avg attempts: %.2f, last_win: %s\n",
               i+1, tmp[i].name,
               tmp[i].best_attempts==0 ? -1 : tmp[i].best_attempts,
               tmp[i].wins, tmp[i].games_played,
               tmp[i].games_played ? (double)tmp[i].total_attempts / tmp[i].games_played : 0.0,
               tmp[i].last_win[0] ? tmp[i].last_win : "-");
    }
}

/* show all-time history for a player across modes */
void show_player_history(const ScoreList *sl, const char *name) {
    int found = 0;
    for (int m=0;m<3;++m) {
        char mode = (m==0)?'E':(m==1)?'M':'H';
        for (int i=0;i<sl->count;++i) {
            if (sl->entries[i].mode==mode && strcasecmp(sl->entries[i].name, name)==0) {
                const ScoreEntry *e = &sl->entries[i];
                printf("Mode %c -> games: %d, wins: %d, best: %d, total_attempts: %d, avg_attempts: %.2f, last_win: %s\n",
                       mode, e->games_played, e->wins,
                       e->best_attempts==0? -1 : e->best_attempts,
                       e->total_attempts,
                       e->games_played ? (double)e->total_attempts / e->games_played : 0.0,
                       e->last_win[0]? e->last_win : "-");
                found = 1;
            }
        }
    }
    if (!found) printf("Tidak ada riwayat untuk pemain '%s'.\n", name);
}
