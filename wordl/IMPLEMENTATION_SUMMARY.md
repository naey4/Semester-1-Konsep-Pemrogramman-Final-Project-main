# RINGKASAN IMPLEMENTASI WORDLE C - KP 2025

## Status Implementasi ✅

Semua fitur yang diminta telah berhasil diimplementasikan. Program dapat dikompilasi tanpa error dan siap dijalankan.

## File-File yang Dibuat

### 1. **score.h** (34 baris)
- Header file untuk score management
- Mendefinisikan struct `ScoreEntry` dan `ScoreList`
- Prototype fungsi load/save JSON, recording game result, display leaderboard dan history

### 2. **score.c** (233 baris)
- Implementasi JSON load/save tanpa library eksternal
- Simple JSON parser untuk membaca file scores.json
- Fungsi `record_game_result()` untuk update statistik setelah game
- Fungsi `show_top_scores()` untuk display top 5 leaderboard
- Fungsi `show_player_history()` untuk display all-time player record
- Penggunaan manual sorting untuk portability

### 3. **game.c** (113 baris)
- Implementasi game logic utama
- Fungsi `play_game_session()` untuk main game loop
- Fisher-Yates shuffle untuk membuat anagram petunjuk
- Evaluasi tebakan dengan sistem penanda (2=benar, 1=ada tapi posisi salah, 0=tidak ada)
- Integrasi dengan score recording

### 4. **main.c** (86 baris)
- Program entry point dengan main() function
- Menu loop dengan 5 opsi:
  1. Login / Set nama pemain
  2. Tampilkan Top Scores (per mode)
  3. Tampilkan Riwayat Pemain (all-time)
  4. Mainkan Game (dengan validasi login)
  5. Keluar
- Input handling dengan clear_stdin_line() untuk buffer management

### 5. **Makefile** (23 baris)
- Build configuration dengan GCC
- Flags: -O2 -Wall -std=c99 (C99 standard untuk portability)
- Target: all (compile), clean (remove objects dan executable)
- Dependency tracking: main.o, game.o, score.o

### 6. **README.md** (200+ baris)
- Dokumentasi lengkap
- Penjelasan fitur, struktur, cara penggunaan
- Contoh skenario penggunaan
- Troubleshooting guide

### 7. **wordle** (executable, 22K)
- Hasil compile dari semua source files
- Ready to run: `./wordle`

## Fitur-Fitur yang Diimplementasikan

### ✅ Menu Lengkap dengan Login
- Sistem login tanpa password (seperti arcade scoreboard)
- Nama pemain divalidasi dan disimpan untuk session
- Opsi ganti nama kapan saja

### ✅ Tiga Level Kesulitan
- **Easy (E)**: 15 percobaan
- **Medium (M)**: 10 percobaan  
- **Hard (H)**: 5 percobaan

### ✅ Statistik Lengkap Per Pemain Per Mode
- `games_played`: Total game dimainkan
- `wins`: Total kemenangan
- `best_attempts`: Score terbaik (semakin kecil semakin baik)
- `total_attempts`: Akumulasi percobaan (untuk rata-rata)
- `last_win`: Tanggal kemenangan terakhir (YYYY-MM-DD)

### ✅ Leaderboard / Top Scores
- Menampilkan Top 5 pemain per mode
- Sorted berdasarkan best_attempts
- Tambahan info: total wins, total games, rata-rata attempts, last_win date
- Otomatis update setelah setiap game

### ✅ Player History / All-Time Record
- Menampilkan statistik all-time pemain untuk ketiga mode (E, M, H)
- Per-mode breakdown dengan statistik lengkap
- Rata-rata attempts per mode

### ✅ Penyimpanan Data dengan Format JSON
- File `scores.json` menyimpan semua data pemain
- Format JSON array dengan object per entry
- Simple JSON parser (tanpa library eksternal)
- Auto-load saat program start, auto-save setelah setiap game

### ✅ Modular Code Structure
- 3 file source (.c) + 1 header (.h) + Makefile
- Separation of concerns:
  - `main.c`: UI dan menu loop
  - `game.c`: Game logic
  - `score.c`: Data persistence dan display
- Easy to extend dan maintain

### ✅ Struct & Pointer Usage
- ScoreEntry struct untuk menyimpan per-pemain per-mode data
- ScoreList struct dengan array + count untuk dynamic management
- Pointer usage di function parameter untuk efficient memory
- Array pointer di game.c untuk kata_bawaan

### ✅ File I/O Processing
- Load JSON dari scores.json (parsing, allocation)
- Save JSON ke scores.json (formatting, writing)
- Error handling untuk file not found, allocation failed

### ✅ Function Modularization
- 15+ functions dengan single responsibility
- Header file untuk public interface
- Static functions untuk internal implementation

## Pengecualian yang Diminta (Sesuai Request)

❌ **TIDAK diimplementasikan:**
1. Auto-login / Mode persisten session - sesuai pengecualian user
2. Validasi tebakan (force word harus ada di kata_bawaan) - sesuai pengecualian user

✅ **DIIMPLEMENTASIKAN semua yang lain:**
1. ✅ Simpan lebih banyak statistik
2. ✅ Tampilkan riwayat pemain (all-time best per mode)
3. ✅ Pisahkan kode ke beberapa file (main.c, game.c, score.c) + Makefile
4. ✅ Format file scoreboard ke JSON untuk fleksibilitas

## Teknologi & Tools

- **Bahasa**: C (C99 Standard)
- **Compiler**: GCC dengan flags `-O2 -Wall -std=c99`
- **Build System**: Makefile
- **Data Format**: JSON (custom parser, tanpa library eksternal)
- **Platform**: Linux (tested on Ubuntu 24.04.2 LTS)

## Compile & Run

```bash
# Di directory /workspaces/210705390

# Compile
make

# Run
./wordle

# Clean (remove objects, executable, score file)
make clean
```

## Kesimpulan

✅ **Semua requirement telah dipenuhi:**
- Menu system dengan login ✅
- Levelisasi game (Easy/Medium/Hard) ✅
- Penyimpanan skor ke file JSON ✅
- Statistik lengkap pemain ✅
- Leaderboard & Player History ✅
- Modular code structure ✅
- Proper struct/pointer/array usage ✅
- File I/O processing ✅
- Makefile untuk build management ✅

**Program siap untuk dikumpulkan sebagai tugas KP 2025.**

---

*Implementasi selesai pada: 9 Desember 2025*
*Total code: 489 baris (source files)*
*Executable size: 22K*
