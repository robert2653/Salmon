// 如何安裝 vscode
// 1. 下載 vscode & msys2
// 2. 在跳出的 terminal 中 / 或打開 ucrt64，打上 "pacman -S --needed base-devel mingw-w64-x86_64-toolchain"
// 3. 環境變數加上 C:\\msys64\\ucrt64\\bin
// 4. 重開 vscode, 載 C/C++, 運行, 編譯器選擇 g++
// 5. 打開 settings -> compiler -> add compilerPath -> 在 "" 裡打上 C:\\msys64\\ucrt64\\bin\\g++.exe