#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "score.h"

/* prototypes from game.c (we don't have game.h to keep minimal) */
int play_game_session(char mode_char, const char *player_name, ScoreList *sl);

#define MAKS_PLAYERNAME 32

static void clear_stdin_line(void) {
    int c;
    while ((c=getchar())!='\n' && c!=EOF) {}
}

int main(void) {
    srand((unsigned)time(NULL));

    ScoreList sl;
    load_scores(&sl);

    char player_name[MAKS_PLAYERNAME] = "";
    int logged_in = 0;
    int running = 1;

    while (running) {
        printf("\n=== WORDLE C (Menu) ===\n");
        printf("1) Login / Set nama pemain (current: %s)\n", logged_in ? player_name : "(belum login)");
        printf("2) Tampilkan Top Scores (pilih mode)\n");
        printf("3) Tampilkan Riwayat Pemain (all-time per mode)\n");
        printf("4) Mainkan Game (wajib login)\n");
        printf("5) Keluar\n");
        printf("Pilih (1-5): ");
        int pilihan=0;
        if (scanf("%d", &pilihan) != 1) { clear_stdin_line(); continue; }
        clear_stdin_line();

        if (pilihan == 1) {
            printf("Masukkan nama pemain (tanpa koma, max %d char): ", MAKS_PLAYERNAME-1);
            char tmp[128];
            if (!fgets(tmp, sizeof(tmp), stdin)) { printf("Input gagal.\n"); continue; }
            size_t L = strlen(tmp);
            while (L>0 && (tmp[L-1]=='\n' || tmp[L-1]=='\r')) { tmp[L-1]='\0'; L--; }
            if (L==0) { printf("Nama tidak boleh kosong.\n"); continue; }
            for (char *p=tmp; *p; ++p) if (*p==',') *p=' ';
            strncpy(player_name, tmp, MAKS_PLAYERNAME-1);
            player_name[MAKS_PLAYERNAME-1]='\0';
            logged_in = 1;
            printf("Logged in sebagai: %s\n", player_name);
        } else if (pilihan == 2) {
            printf("Pilih mode: (E)asy, (M)edium, (H)ard: ");
            char m=' ';
            if (scanf(" %c", &m) != 1) { clear_stdin_line(); continue; }
            clear_stdin_line();
            m = toupper((unsigned char)m);
            if (m!='E' && m!='M' && m!='H') { printf("Mode tidak valid.\n"); continue; }
            show_top_scores(&sl, m);
        } else if (pilihan == 3) {
            printf("Masukkan nama pemain untuk lihat riwayat: ");
            char tmp[128];
            if (!fgets(tmp, sizeof(tmp), stdin)) continue;
            size_t L = strlen(tmp);
            while (L>0 && (tmp[L-1]=='\n' || tmp[L-1]=='\r')) { tmp[L-1]='\0'; L--; }
            if (L==0) { printf("Nama kosong.\n"); continue; }
            show_player_history(&sl, tmp);
        } else if (pilihan == 4) {
            if (!logged_in) { printf("Anda harus login dulu (menu 1).\n"); continue; }
            printf("Pilih level: 1) Easy (15)  2) Medium (10)  3) Hard (5) : ");
            int lv = 0;
            if (scanf("%d", &lv) != 1) { clear_stdin_line(); continue; }
            clear_stdin_line();
            if (lv < 1 || lv > 3) { printf("Level tidak valid.\n"); continue; }
            char mode = (lv==1)?'E':(lv==2)?'M':'H';
            play_game_session(mode, player_name, &sl);
        } else if (pilihan == 5) {
            running = 0;
            printf("Terima kasih, sampai jumpa!\n");
        } else {
            printf("Pilihan tidak dikenal.\n");
        }
    }
    return 0;
}
