## Codebook of Salmon
- Hash 規則
    1. 標題的 hash 就是整個檔案的 hash
    2. struct 內第一次出現的 hash 有包含 struct 名稱、變數等等，接下來的 hash 都只有 function 本身
    3. 寫在全域的 hash 都是上個 hash 到這個 hash 的部分