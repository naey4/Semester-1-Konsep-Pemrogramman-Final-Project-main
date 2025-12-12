# WORDLE C - Dokumentasi & README

## Ringkasan Program

Program ini adalah klon game Wordle sederhana yang ditulis dalam bahasa C, dengan fitur-fitur tambahan seperti:
- **Menu Login**: Sistem login tanpa password (seperti arcade scoreboard)
- **Multiple Levels**: Easy (15 percobaan), Medium (10 percobaan), Hard (5 percobaan)
- **Statistik Pemain**: Menyimpan statistik lengkap untuk setiap pemain per mode
- **Leaderboard/Top Scores**: Menampilkan top 5 pemain per level
- **Player History**: Riwayat all-time untuk setiap pemain
- **Persistent Storage**: Data disimpan dalam format JSON (`scores.json`)

## Fitur Utama

### 1. Login Sederhana (Tanpa Password)
- Pemain input nama mereka sebelum bermain
- Nama digunakan sebagai identitas dalam leaderboard
- Nama diperbaharui dengan menginput nama baru di menu login

### 2. Tiga Level Kesulitan
| Level | Percobaan | Mode |
|-------|-----------|------|
| Easy  | 15        | E    |
| Medium| 10        | M    |
| Hard  | 5         | H    |

### 3. Statistik & Leaderboard
Setiap pemain memiliki statistik lengkap per mode:
- **games_played**: Total game yang dimainkan
- **wins**: Total kemenangan
- **best_attempts**: Jumlah percobaan terbaik (semakin kecil semakin baik)
- **total_attempts**: Total akumulasi percobaan (untuk rata-rata)
- **last_win**: Tanggal kemenangan terakhir (YYYY-MM-DD)

### 4. Format Data JSON
File `scores.json` menyimpan data dalam format JSON array:
```json
[
  {
    "mode":"E",
    "name":"Alice",
    "games_played":10,
    "wins":3,
    "best_attempts":3,
    "total_attempts":28,
    "last_win":"2025-12-09"
  }
]
```

## Struktur File

```
/workspaces/210705390/
├── score.h          # Header file untuk score management
├── score.c          # Implementasi score management (load/save JSON, leaderboard)
├── game.c           # Implementasi game logic (play session, evaluasi tebakan)
├── main.c           # Menu utama dan program entry point
├── Makefile         # Build configuration
├── wordle           # Executable (hasil compile)
└── README.md        # File dokumentasi ini
```

## Cara Menggunakan

### 1. Compile Program
```bash
cd /workspaces/210705390
make
```

Output:
```
gcc -O2 -Wall -std=c99 -c main.c
gcc -O2 -Wall -std=c99 -c game.c
gcc -O2 -Wall -std=c99 -c score.c
gcc -O2 -Wall -std=c99 -o wordle main.o game.o score.o
```

### 2. Jalankan Program
```bash
./wordle
```

### 3. Menu Utama
```
=== WORDLE C (Menu) ===
1) Login / Set nama pemain (current: (belum login))
2) Tampilkan Top Scores (pilih mode)
3) Tampilkan Riwayat Pemain (all-time per mode)
4) Mainkan Game (wajib login)
5) Keluar
Pilih (1-5): 
```

### 4. Opsi Menu

**Opsi 1: Login / Set Nama**
- Masukkan nama pemain (tanpa koma, max 31 karakter)
- Nama digunakan untuk tracking skor dan leaderboard

**Opsi 2: Tampilkan Top Scores**
- Pilih mode: (E)asy, (M)edium, (H)ard
- Menampilkan Top 5 pemain dengan statistik:
  - Peringkat, Nama, Best Attempts, Total Wins, Total Games, Rata-rata Attempts, Tanggal Win Terakhir

**Opsi 3: Tampilkan Riwayat Pemain**
- Masukkan nama pemain untuk lihat all-time history
- Menampilkan statistik per mode (E, M, H) untuk pemain tersebut

**Opsi 4: Mainkan Game**
- Wajib login terlebih dahulu
- Pilih level (1=Easy, 2=Medium, 3=Hard)
- Game dimulai dengan kata rahasia dan petunjuk (anagram)
- Feedback per tebakan: `[X]` = benar posisi, `(X)` = huruf ada tapi posisi salah, ` X ` = huruf tidak ada

**Opsi 5: Keluar**
- Simpan semua perubahan dan keluar dari program

## Contoh Penggunaan

### Skenario 1: Pemain Baru Bermain Easy Mode
```
Menu → Opsi 1 → Nama: "Alice" → Opsi 4 → Level: 1 (Easy)
[Game dimulai dengan 15 percobaan]
Petunjuk: mszoo  [anagram dari zooms]
Percobaan 1: apple → Feedback
Percobaan 2: zumes → Feedback
Percobaan 3: zooms → SELAMAT! Score tercatat
```

### Skenario 2: Lihat Leaderboard Mode Easy
```
Menu → Opsi 2 → Mode: E
== Top skor (mode E) ==
1. Bob - best: 2 attempts, wins: 5, games: 7, avg attempts: 3.14, last_win: 2025-12-09
2. Alice - best: 3 attempts, wins: 3, games: 10, avg attempts: 2.80, last_win: 2025-12-09
...
```

## Fitur Teknis

### Struct & Data Structure
```c
typedef struct {
    char mode;              // 'E', 'M', 'H'
    char name[32];          // Nama pemain
    int games_played;       // Total game
    int wins;               // Total menang
    int best_attempts;      // Best score (0 = belum menang)
    int total_attempts;     // Akumulasi percobaan
    char last_win[11];      // YYYY-MM-DD
} ScoreEntry;

typedef struct {
    ScoreEntry entries[2000];  // Max 2000 pemain
    int count;                 // Jumlah entri aktif
} ScoreList;
```

### Fungsi-Fungsi Utama

**score.h/score.c:**
- `load_scores(ScoreList*)` - Load dari scores.json
- `save_scores(const ScoreList*)` - Save ke scores.json
- `record_game_result(...)` - Update statistik setelah game
- `show_top_scores(const ScoreList*, char mode)` - Display leaderboard
- `show_player_history(const ScoreList*, const char* name)` - Display player history

**game.c:**
- `play_game_session(...)` - Main game loop
- `acak_kata(...)` - Fisher-Yates shuffle untuk anagram
- `evaluate_and_print(...)` - Evaluasi tebakan dan print feedback

**main.c:**
- `main()` - Menu loop utama

## Pengecualian Implementasi (Sesuai Request)

Fitur yang **TIDAK** diimplementasikan (per pengecualian user):
1. ❌ Auto-login / Mode persisten session
2. ❌ Validasi tebakan (tebakan tidak harus ada di kata_bawaan)

Fitur yang **SUDAH** diimplementasikan:
1. ✅ Menu login / scoreboard
2. ✅ Penyimpanan statistik lengkap (games_played, wins, best_attempts, dll)
3. ✅ Leaderboard / Top Scores per mode
4. ✅ Player History / All-time record
5. ✅ Format JSON untuk flexibility
6. ✅ Modular code structure (main.c, game.c, score.c)
7. ✅ Makefile untuk build management

## Catatan Penting

### Daftar Kata
File `game.c` saat ini menggunakan daftar kata minimal (15 kata) sebagai contoh:
```c
static const char *kata_bawaan[] = {
    "about","above","abuse","actor","acute","admit","adopt","adult","after","again",
    "zoned","zones","zonks","zooms","zowie"
};
```

**Untuk menggunakan daftar kata lengkap**, Anda bisa:
1. Mengganti array `kata_bawaan[]` dengan daftar lengkap
2. Mengubah `jumlah_bawaan` atau menggunakan dynamic loading dari file `words.txt`

### Format JSON
Format JSON dipilih untuk flexibility. Program memiliki simple JSON parser yang robust untuk format yang dihasilkan program sendiri. Hindari mengedit file `scores.json` manual dengan karakter aneh.

### Kompilasi & Peringatan
Program dikompilasi dengan `-Wall -std=c99`. Beberapa warning minor (strcpy truncation) adalah hasil dari GCC's fortify source dan tidak mempengaruhi fungsionalitas.

## Command Cepat

```bash
# Bersihkan dan rebuild
make clean && make

# Jalankan program
./wordle

# Hapus executable dan data skor
make clean
```

## Struktur Menu yang Tersedia

```
MAIN MENU
├── 1. Login/Set Nama Pemain
│   └── Input: nama pemain (string)
├── 2. Tampilkan Top Scores
│   └── Input: pilih mode (E/M/H)
│   └── Output: Top 5 per mode dengan statistik
├── 3. Tampilkan Riwayat Pemain
│   └── Input: nama pemain
│   └── Output: History all-time per mode
├── 4. Mainkan Game (Perlu Login)
│   ├── Input: pilih level (1=Easy/2=Medium/3=Hard)
│   ├── Game Loop
│   │   ├── Input: tebakan 5 huruf
│   │   ├── Output: feedback feedback per huruf
│   │   └── Repeat hingga menang atau kehabisan percobaan
│   └── Auto-save score ke scores.json
└── 5. Keluar
```

## Troubleshooting

| Masalah | Solusi |
|---------|--------|
| Compile error | Pastikan gcc dan make sudah terinstall: `apt-get install build-essential` |
| `scores.json` tidak terbuat | Normal - file dibuat saat pertama kali menang. Jalankan beberapa game. |
| Program stuck di menu | Input harus diikuti Enter. Gunakan `Ctrl+C` untuk exit paksa. |
| Nama pemain tidak tersimpan | Pastikan Anda login di menu 1 sebelum memainkan game |

---

**Author**: Implementation berdasarkan spesifikasi KP 2025  
**Tanggal**: December 2025  
**Bahasa**: C (C99 Standard)  
**Build Tool**: Makefile (GCC)
