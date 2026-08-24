#pragma GCC target("popcnt")
bitset<60> b = x; // 讀整數轉 bitset
cin >> b; // 讀 01 字串轉 bitset
b.to_ullong(); // bitset 轉整數
b.to_string(); // bitset 轉 01 字串
stoll(s, 0, 2); // 01 字串轉成 ll