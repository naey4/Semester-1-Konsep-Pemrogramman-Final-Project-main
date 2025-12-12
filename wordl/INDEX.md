# 📁 WORDLE C - KP 2025 PROJECT FOLDER

## Struktur Folder

```
wordle_kp2025/
├── 📄 Core Source Files
│   ├── score.h           (Header file untuk score management)
│   ├── score.c           (Implementasi JSON & leaderboard)
│   ├── game.c            (Game logic & word evaluation)
│   └── main.c            (Menu system & entry point)
│
├── 🔨 Build System
│   └── Makefile          (Compilation configuration)
│
├── ⚙️ Executable
│   └── wordle            (Compiled binary, ready to run)
│
└── 📚 Documentation
    ├── README.md                      (Comprehensive guide)
    ├── QUICKSTART.md                  (Quick start guide)
    ├── IMPLEMENTATION_SUMMARY.md      (Technical summary)
    ├── SUBMISSION_CHECKLIST.md        (Checklist & status)
    └── INDEX.md                       (This file)
```

## File Descriptions

### Source Code Files (Required for Submission)

| File | Size | Purpose |
|------|------|---------|
| score.h | 991 B | Header dengan struct ScoreEntry, ScoreList dan function prototypes |
| score.c | 8.0 KB | JSON load/save, leaderboard display, player history |
| game.c | 4.1 KB | Game loop, word evaluation, hint generation |
| main.c | 3.3 KB | Menu system dengan 5 opsi utama |
| **TOTAL** | **16.4 KB** | **Complete working source code** |

### Build & Executable

| File | Size | Purpose |
|------|------|---------|
| Makefile | 345 B | GCC compilation flags: -O2 -Wall -std=c99 |
| wordle | 22 KB | Ready-to-run executable binary |

### Documentation Files

| File | Size | Purpose |
|------|------|---------|
| README.md | 8.1 KB | Full documentation with all details |
| QUICKSTART.md | 6.0 KB | Quick reference & usage guide |
| IMPLEMENTATION_SUMMARY.md | 5.4 KB | Feature list & implementation status |
| SUBMISSION_CHECKLIST.md | 6.1 KB | Checklist & project completion status |
| INDEX.md | This | Folder structure overview |

## Quick Start

### 1. Navigate to Folder
```bash
cd wordle_kp2025
```

### 2. Compile (Optional - executable sudah ada)
```bash
make
```

### 3. Run Program
```bash
./wordle
```

### 4. Clean (Remove old builds)
```bash
make clean
```

## Features Summary

✅ Menu system dengan login
✅ 3 difficulty levels (Easy/Medium/Hard)
✅ Persistent score storage (JSON format)
✅ Leaderboard & player history
✅ Extended statistics per player per mode
✅ Modular code structure
✅ Makefile build system
✅ Comprehensive documentation

## How to Use This Folder

### For Development
1. Edit `.c` files sesuai kebutuhan
2. Run `make clean && make` untuk rebuild
3. Test dengan `./wordle`

### For Submission
1. Copy entire folder `wordle_kp2025/` ke tempat pengumpulan
2. Atau compress: `zip -r wordle_kp2025.zip wordle_kp2025/`
3. Include dokumentasi README.md jika diminta

### For Reference
- Lihat README.md untuk dokumentasi lengkap
- Lihat QUICKSTART.md untuk quick reference
- Lihat IMPLEMENTATION_SUMMARY.md untuk technical details

## File Statistics

```
Total files in folder:    9 items
├─ Source code:          4 files (.c/.h)
├─ Build system:         1 file (Makefile)
├─ Executable:           1 file (wordle)
└─ Documentation:        4 files (.md)

Total code size:         16.4 KB (source)
Executable size:         22 KB
Documentation size:      25.6 KB
Total folder size:       ~70 KB
```

## Compilation Details

```bash
GCC Flags:
  -O2        (Optimization level 2)
  -Wall      (All warnings enabled)
  -std=c99   (C99 standard compliance)

Target dependencies:
  main.o → score.h
  game.o → score.h
  score.o → score.h
  wordle → main.o game.o score.o
```

## Platform & Requirements

- **OS**: Linux (Ubuntu 24.04.2 LTS or compatible)
- **Compiler**: GCC (any modern version)
- **Build System**: GNU Make
- **Dependencies**: Only C standard library (no external deps)
- **C Standard**: C99

## Checklist untuk Submission

- [x] Source files (.c, .h) - lengkap
- [x] Makefile - functional
- [x] Executable - compiled & tested
- [x] Documentation - comprehensive
- [x] All features implemented
- [x] Code quality - high
- [x] Ready for grading

## Support Files

Jika ada file tambahan yang ingin ditambahkan ke folder:
- Letakkan di dalam `wordle_kp2025/`
- Update file ini (INDEX.md) dengan deskripsi file baru

## Next Steps

1. **Immediate**: Folder sudah siap untuk digunakan/dikumpulkan
2. **Testing**: Jalankan `./wordle` untuk test program
3. **Customization**: Modifikasi daftar kata di `game.c` jika diperlukan
4. **Submission**: Copy folder ke tempat pengumpulan tugas

---

**Created**: December 9, 2025  
**Status**: ✅ COMPLETE & READY  
**Version**: 1.0
