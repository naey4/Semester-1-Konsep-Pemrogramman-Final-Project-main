# 🚀 SETUP & BUILD GUIDE

## Prerequisites

Sebelum menjalankan program, pastikan Anda memiliki:
- **GCC** (GNU C Compiler)
- **Make** (GNU Make)
- **Linux/Unix** environment

### Check if installed:
```bash
gcc --version
make --version
```

### Install (if not installed):
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
brew install gcc make
```

## Quick Setup

### Option 1: Using Pre-compiled Binary (Fastest)
```bash
cd wordle_kp2025
./wordle
```

### Option 2: Compile from Source
```bash
cd wordle_kp2025
make
./wordle
```

## Detailed Build Instructions

### Step 1: Navigate to Folder
```bash
cd wordle_kp2025
```

### Step 2: Clean Old Builds (Optional)
```bash
make clean
```
This removes: `*.o` (object files), `wordle` (executable), `scores.json` (score data)

### Step 3: Compile
```bash
make
```

**Output:**
```
gcc -O2 -Wall -std=c99 -c main.c
gcc -O2 -Wall -std=c99 -c game.c
gcc -O2 -Wall -std=c99 -c score.c
gcc -O2 -Wall -std=c99 -o wordle main.o game.o score.o
```

### Step 4: Verify Compilation
```bash
ls -lh wordle
```

You should see: `-rwxr-xr-x 1 ... wordle` (executable with x permission)

### Step 5: Run Program
```bash
./wordle
```

## Makefile Targets

| Command | Effect |
|---------|--------|
| `make` atau `make all` | Compile project (default) |
| `make clean` | Remove object files, executable, scores.json |
| `make wordle` | Build executable only |
| `make main.o` | Build main.o only |
| `make game.o` | Build game.o only |
| `make score.o` | Build score.o only |

## Compilation Flags Explained

```
-O2        = Optimization level 2 (good speed + small size)
-Wall      = Enable all compiler warnings
-std=c99   = Use C99 standard (for portability)
```

## If Compilation Fails

### Common Issues & Solutions

| Issue | Solution |
|-------|----------|
| `gcc: command not found` | Install GCC: `sudo apt-get install gcc` |
| `make: command not found` | Install Make: `sudo apt-get install make` |
| Error in `score.c` line X | Check for missing headers or corrupted file |
| `permission denied` | Run: `chmod +x wordle` then try again |

### Debug Mode
```bash
make clean
make CFLAGS="-g -O0 -Wall"
gdb ./wordle
```

## File Size After Build

```
-rw-r--r-- score.o          (3-4 KB)
-rw-r--r-- game.o           (2-3 KB)
-rw-r--r-- main.o           (2-3 KB)
-rwxr-xr-x wordle           (22 KB) ← Executable
```

## Testing After Compilation

### Quick Test
```bash
echo -e "1\nTestUser\n5" | ./wordle
```

Expected output: Menu appears, login succeeds, program exits

### Full Test
```bash
./wordle
# Manually:
# 1. Press 1 → Enter name → Try different options
# 2. Press 4 → Try playing a game
# 3. Press 5 → Exit
```

## Troubleshooting

### Program tidak merespons input
- Tekan `Ctrl+C` untuk force exit
- Pastikan input diikuti dengan Enter

### Compile warning muncul
- Warning yang muncul adalah minor (format truncation)
- Program tetap berfungsi normal
- Bukan error, aman untuk submission

### scores.json tidak terbuat
- Normal - dibuat saat pertama kali ada pemain menang
- Untuk testing: mainkan game sampai menang

### Cannot find executable
```bash
# Pastikan Anda di directory yang benar
pwd
# Seharusnya: /path/to/wordle_kp2025

# Cek file ada
ls wordle

# Cek permission
ls -l wordle
# Seharusnya ada 'x' di permission
```

## Rebuild Instructions

Jika Anda mengubah source code:

```bash
# Option 1: Clean rebuild
make clean && make

# Option 2: Incremental rebuild
make
# (make akan detect perubahan dan re-compile otomatis)

# Option 3: Force rebuild semua file
touch *.c && make
```

## Version Control (if using Git)

```bash
# Optional: Setup .gitignore
cat > .gitignore << EOF
*.o
wordle
scores.json
EOF

# Ignore compiled files
git add -A :!wordle :!*.o :!scores.json
```

## Next Steps After Build

1. ✅ Compile successful
2. ✅ Run `./wordle`
3. ✅ Test semua menu options
4. ✅ Mainkan game untuk generate scores.json
5. ✅ Lihat leaderboard & history
6. ✅ Ready for submission

## Support

Jika ada masalah:

1. **Read**: Check README.md atau QUICKSTART.md
2. **Debug**: Run `./wordle` secara manual dan test
3. **Clean**: Run `make clean && make` untuk fresh rebuild
4. **Check**: Verify `gcc` dan `make` terinstall dengan benar

## Submission Checklist

Sebelum submit, pastikan:

- [ ] Program compile tanpa error (`make` berjalan sukses)
- [ ] Warning yang muncul adalah minor (OK untuk submit)
- [ ] Executable ada: `ls wordle` shows file
- [ ] Program berjalan: `./wordle` launches menu
- [ ] All files present dalam folder
- [ ] Documentation lengkap (README, QUICKSTART, etc)

---

**Created**: December 9, 2025  
**Last Updated**: December 9, 2025  
**Status**: ✅ Ready to Use
