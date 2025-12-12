#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "score.h"

/* constants */
#define PANJANG_KATA 5

/* minimal word list — Anda bisa ganti/isi lengkap */
static const char *kata_bawaan[] = {
    "about","above","abuse","actor","acute","admit","adopt","adult","after","again",
    "zoned","zones","zonks","zooms","zowie"
};
static const int jumlah_bawaan = sizeof(kata_bawaan)/sizeof(kata_bawaan[0]);

/* Fisher-Yates scramble, ensure not equal to source (try up to 100 times) */
static void acak_kata(const char *sumber, char *tujuan) {
    char tmp[PANJANG_KATA+1];
    int percobaan = 0;
    do {
        for (int i = 0; i < PANJANG_KATA; ++i) tmp[i] = sumber[i];
        tmp[PANJANG_KATA] = '\0';
        for (int i = PANJANG_KATA - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            char c = tmp[i]; tmp[i] = tmp[j]; tmp[j] = c;
        }
        strncpy(tujuan, tmp, PANJANG_KATA+1);
        percobaan++;
    } while (strcmp(tujuan, sumber) == 0 && percobaan < 100);
}

/* evaluate guess and print colored feedback; returns 1 if guess==secret */
static int evaluate_and_print(const char *guess, const char *secret) {
    int penanda[PANJANG_KATA] = {0};
    int terpakai[PANJANG_KATA] = {0};
    for (int i=0;i<PANJANG_KATA;++i) {
        if (guess[i] == secret[i]) {
            penanda[i] = 2;
            terpakai[i] = 1;
        }
    }
    int jumlah_rahasia[26] = {0};
    for (int i=0;i<PANJANG_KATA;++i) {
        if (!terpakai[i]) jumlah_rahasia[(unsigned char)secret[i]-'a']++;
    }
    for (int i=0;i<PANJANG_KATA;++i) {
        if (penanda[i]==0) {
            int idx = (unsigned char)guess[i]-'a';
            if (idx>=0 && idx<26 && jumlah_rahasia[idx]>0) {
                penanda[i]=1; jumlah_rahasia[idx]--;
            } else penanda[i]=0;
        }
    }
    /* print (simple, no ANSI for portability) */
    for (int i=0;i<PANJANG_KATA;++i) {
        char c = toupper((unsigned char)guess[i]);
        if (penanda[i]==2) printf("[%c]", c);
        else if (penanda[i]==1) printf("(%c)", c);
        else printf(" %c ", c);
        if (i < PANJANG_KATA-1) printf(" ");
    }
    printf("\n");
    return strncmp(guess, secret, PANJANG_KATA) == 0;
}

/* play one game, returns attempts used and won flag (1=won,0=lost) */
int play_game_session(char mode_char, const char *player_name, ScoreList *sl) {
    int max_attempts = (mode_char=='E') ? 15 : (mode_char=='M') ? 10 : 5;
    /* pick secret and hint */
    const char *rahasia_src = kata_bawaan[rand() % jumlah_bawaan];
    char secret[PANJANG_KATA+1];
    strncpy(secret, rahasia_src, PANJANG_KATA+1);
    secret[PANJANG_KATA] = '\0';
    char hint[PANJANG_KATA+1];
    acak_kata(secret, hint);

    printf("Petunjuk (anagram): %s\n", hint);
    printf("Mode %c - Anda %d percobaan untuk menebak kata %d huruf.\n", mode_char, max_attempts, PANJANG_KATA);
    char buf[128];
    for (int attempt=1; attempt<=max_attempts; ++attempt) {
        printf("Percobaan %d/%d - masukkan tebakan: ", attempt, max_attempts);
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Input error.\n");
            return 0;
        }
        size_t L = strlen(buf);
        while (L>0 && (buf[L-1]=='\n' || buf[L-1]=='\r')) { buf[L-1]='\0'; L--; }
        if (L != PANJANG_KATA) {
            printf("Tebakan harus tepat %d huruf.\n", PANJANG_KATA);
            attempt--; /* don't consume attempt */
            continue;
        }
        /* normalize to lowercase */
        for (int i=0;i<PANJANG_KATA;++i) buf[i] = tolower((unsigned char)buf[i]);

        /* NOTE: sesuai permintaan, kita TIDAK memaksa tebakan harus ada di kata_bawaan. */

        int won = evaluate_and_print(buf, secret);
        if (won) {
            printf("Selamat! Tebakan benar dalam %d percobaan.\n", attempt);
            /* record */
            record_game_result(sl, mode_char, player_name, attempt, 1);
            return 1; /* won */
        }
    }
    /* lost */
    printf("Maaf, Anda kalah. Kata yang benar: %s\n", secret);
    record_game_result(sl, mode_char, player_name, max_attempts, 0);
    return 0;
}
