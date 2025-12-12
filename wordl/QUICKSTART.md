# QUICK START GUIDE - WORDLE C KP 2025

## Langkah Cepat

### 1️⃣ Compile
```bash
cd /workspaces/210705390
make
```
Output: Program `wordle` berhasil dikompilasi

### 2️⃣ Run
```bash
./wordle
```

### 3️⃣ Main Menu Muncul
```
=== WORDLE C (Menu) ===
1) Login / Set nama pemain (current: (belum login))
2) Tampilkan Top Scores (pilih mode)
3) Tampilkan Riwayat Pemain (all-time per mode)
4) Mainkan Game (wajib login)
5) Keluar
Pilih (1-5): 
```

## Alur Penggunaan Tipikal

### Pemain Baru: Ingin Bermain
```
1. Ketik 1 (Login) → Masukkan nama "Alice"
2. Ketik 4 (Mainkan Game) → Pilih 1 (Easy)
3. Terima petunjuk anagram
4. Tebak 5 huruf, hingga benar atau kehabisan percobaan
5. Score otomatis tersimpan
6. Ketik 5 (Keluar)
```

### Lihat Leaderboard
```
1. Ketik 2 (Top Scores) → Pilih mode E/M/H
2. Lihat Top 5 pemain
3. Ketik nomor lagi untuk menu
```

### Lihat Riwayat Pemain
```
1. Ketik 3 (Riwayat Pemain) → Masukkan nama "Alice"
2. Lihat statistik all-time Alice untuk ketiga mode
3. Ketik nomor lagi untuk menu
```

## File Structure Setelah Compile

```
/workspaces/210705390/
├── score.h              ← Header untuk score management
├── score.c              ← JSON load/save, leaderboard logic
├── game.c               ← Game loop logic
├── main.c               ← Menu & entry point
├── Makefile             ← Build config
├── wordle               ← EXECUTABLE (hasil compile)
├── scores.json          ← Data skor pemain (auto-created after first win)
├── README.md            ← Dokumentasi lengkap
└── IMPLEMENTATION_SUMMARY.md ← Summary implementasi
```

## Menu Options Explained

| Pilihan | Fungsi | Input | Output |
|---------|--------|-------|--------|
| 1 | Login/Ganti Nama | Nama pemain | "Logged in sebagai: {nama}" |
| 2 | Top Scores | Mode (E/M/H) | Top 5 pemain dengan statistik |
| 3 | Riwayat Pemain | Nama pemain | All-time stats per mode (E,M,H) |
| 4 | Mainkan Game | Level (1/2/3) | Game loop dengan tebakan |
| 5 | Keluar | - | Exit program |

## Game Mechanics

### Petunjuk (Hint)
- Anagram dari kata rahasia
- Contoh: Kata "zooms" → Hint "mszoo"

### Feedback Per Tebakan
- `[X]` = Huruf benar di posisi yang tepat (GREEN)
- `(X)` = Huruf ada di kata tapi posisi salah (YELLOW)
- ` X ` = Huruf tidak ada di kata (GREY)

### Contoh Game Flow Easy (15 percobaan)
```
Mode E - Anda 15 percobaan untuk menebak kata 5 huruf.
Petunjuk (anagram): mszoo

Percobaan 1/15 - masukkan tebakan: apple
 A  (P) (P) (L) (E)
[Feedback: P ada tapi posisi salah]

Percobaan 2/15 - masukkan tebakan: zooms
[Z] [O] [O] [M] [S]
Selamat! Tebakan benar dalam 2 percobaan.
[Score tersimpan: Mode E, Best 2 attempts]
```

## Statistik yang Disimpan (Per Pemain Per Mode)

Setelah menang, program otomatis menyimpan:
- ✅ **games_played**: +1
- ✅ **wins**: +1
- ✅ **best_attempts**: Ambil nilai terkecil dari sebelumnya
- ✅ **total_attempts**: Akumulasi dengan percobaan saat ini
- ✅ **last_win**: Update dengan tanggal hari ini (YYYY-MM-DD)

## Data Persistence (scores.json)

Format yang tersimpan:
```json
[
  {
    "mode":"E",
    "name":"Alice",
    "games_played":5,
    "wins":3,
    "best_attempts":2,
    "total_attempts":14,
    "last_win":"2025-12-09"
  },
  {
    "mode":"E",
    "name":"Bob",
    "games_played":3,
    "wins":2,
    "best_attempts":4,
    "total_attempts":12,
    "last_win":"2025-12-09"
  }
]
```

File ini:
- Auto-created saat pertama kali ada pemain menang
- Auto-loaded saat program start
- Auto-saved setelah setiap game finish

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `make: command not found` | Install build-essential: `apt-get install build-essential` |
| `gcc: not found` | Install gcc: `apt-get install gcc` |
| Compile error | Check `score.c` line numbers di error message |
| Program stuck | Press `Ctrl+C` to exit |
| Scores tidak muncul | Pastikan login dulu, main game, dan menang |
| scores.json kosong | Normal, dibuat saat ada pemain menang untuk pertama kali |

## Contoh Sesi Lengkap

```bash
$ ./wordle

=== WORDLE C (Menu) ===
1) Login / Set nama pemain (current: (belum login))
2) Tampilkan Top Scores (pilih mode)
3) Tampilkan Riwayat Pemain (all-time per mode)
4) Mainkan Game (wajib login)
5) Keluar
Pilih (1-5): 1
Masukkan nama pemain (tanpa koma, max 31 char): Alice
Logged in sebagai: Alice

=== WORDLE C (Menu) ===
1) Login / Set nama pemain (current: Alice)
...
Pilih (1-5): 4
Pilih level: 1) Easy (15)  2) Medium (10)  3) Hard (5) : 1
Petunjuk (anagram): mszoo
Mode E - Anda 15 percobaan untuk menebak kata 5 huruf.
Percobaan 1/15 - masukkan tebakan: zooms
[Z] [O] [O] [M] [S]
Selamat! Tebakan benar dalam 1 percobaan.
Score tersimpan untuk Alice pada mode E : 1 percobaan.

=== WORDLE C (Menu) ===
Pilih (1-5): 2
Pilih mode: (E)asy, (M)edium, (H)ard: E
== Top skor (mode E) ==
1. Alice - best: 1 attempts, wins: 1, games: 1, avg attempts: 1.00, last_win: 2025-12-09

=== WORDLE C (Menu) ===
Pilih (1-5): 5
Terima kasih, sampai jumpa!
```

## Tambahan: Modifikasi Daftar Kata

Jika ingin menambah daftar kata, edit `game.c` baris 14-20:

**Sebelum:**
```c
static const char *kata_bawaan[] = {
    "about","above","abuse",...,"zowie"
};
static const int jumlah_bawaan = sizeof(kata_bawaan)/sizeof(kata_bawaan[0]);
```

**Sesudah (contoh):**
```c
static const char *kata_bawaan[] = {
    "about","above","abuse","actor","acute",
    "admit","adopt","adult","after","again",
    // Tambah lebih banyak kata di sini
    "zoned","zones","zonks","zooms","zowie"
};
static const int jumlah_bawaan = sizeof(kata_bawaan)/sizeof(kata_bawaan[0]);
```

Kemudian re-compile: `make clean && make`

## Keyboard Shortcuts / Tips

- **Ctrl+C**: Force exit program
- **Enter**: Confirm input
- **Backspace**: Delete karakter (saat input)

## Performance & Limits

- Max 2000 pemain (definisi MAX_SCORES di score.h)
- Max 32 karakter nama pemain
- JSON parsing otomatis untuk scalability
- No external dependencies (pure C + standard lib)

---

**Selamat bermain WORDLE C! 🎮**
