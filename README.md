## Codebook of Salmon

### Hash 規則

hash 用來在比賽時確認抄的 code 沒有打錯。計算方式是去掉註解與所有空白後取 md5 的前 6 碼：

```bash
cpp file.cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
```

因為空白和註解都被拿掉，所以縮排、換行、註解怎麼改都不影響 hash。

1. **標題的 hash** 是整個檔案的 hash，由 `codebook.tex` 編譯時自動算，不用手寫。
2. **寫在全域的 hash**：從上一個 hash 的下一行，算到這個 hash 所在的那一行（檔案開頭的第一個 hash 則從第 1 行開始）。
    ```cpp
    const double eps = 1E-9;      // ┐
    ...                           // │ 第 1 行到這裡
    using P = Pt<double>; // xxxxxx  ┘
    istream &operator>>(...) ...  // ┐ 上一個 hash 的下一行到這裡
    } // yyyyyy                      ┘
    ```
3. **struct 內第一個 hash**：從 `struct` 那行算到這個 hash 所在的那一行，**最後再補上一個 `};`**，讓它是完整的 struct（包含 struct 名稱、成員變數、前面的 function）。
    ```bash
    { sed -n '1,36p' Polynomial.cpp; echo '};'; } | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
    ```
4. **struct 內之後的 hash**：只算那個 function 本身（從 function 開頭到 hash 所在的 `}`）。
5. 整個 struct 結尾的 `}; // xxxxxx` 視為全域 hash，照第 2 點算。
6. 同一段有多種寫法時，hash 標成 `// 1: xxxxxx, 2: yyyyyy`，分別是只保留其中一種寫法時的 hash。

改 code 後記得重算受影響的 hash。重算前可以先用 `git show HEAD:<file>` 拿舊版，用同樣的方法算出原本的 hash，確認範圍取對了。
