#ifndef SCORE_H
#define SCORE_H

#define MAKS_PLAYERNAME 32
#define MAX_SCORES 2000
#define DATE_STRLEN 11 /* "YYYY-MM-DD" + '\0' */

typedef struct {
    char mode; /* 'E','M','H' */
    char name[MAKS_PLAYERNAME];
    int games_played;
    int wins;
    int best_attempts;    /* smaller is better; 0 = not set */
    int total_attempts;   /* sum of attempts in won games or all games (we'll accumulate attempts) */
    char last_win[DATE_STRLEN]; /* "YYYY-MM-DD" or empty */
} ScoreEntry;

typedef struct {
    ScoreEntry entries[MAX_SCORES];
    int count;
} ScoreList;

/* load/save JSON file (scores.json) */
void load_scores(ScoreList *sl);
void save_scores(const ScoreList *sl);

/* update stats after a finished game */
void record_game_result(ScoreList *sl, char mode, const char *name, int attempts_used, int won);

/* display functions */
void show_top_scores(const ScoreList *sl, char mode);
void show_player_history(const ScoreList *sl, const char *name);

#endif /* SCORE_H */
