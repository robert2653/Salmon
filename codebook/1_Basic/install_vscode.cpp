// 如何安裝 vscode
// 1. 下載 vscode & msys2
// 2. 打開 mingw64，打上 "pacman -S --needed base-devel mingw-w64-x86_64-toolchain"
//    或是打 "pacman -S mingw-w64-x86_64-gcc"、"pacman -S mingw-w64-x86_64-gdb"
// 3. 環境變數加上 "C:\msys64\mingw64\bin"
// 4. 重開 vscode, 載 C/C++, 運行, 編譯器選擇 g++
// 5. settings -> compiler -> add compilerPath -> 在 "" 裡打上 "C:\\msys64\\mingw64\\bin\\g++.exe"