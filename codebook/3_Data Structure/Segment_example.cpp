// Segment

// ---pizza_queries---
// 左邊的店(s < t): dis_l = (pizza[s] - s) + t;
// 右邊的店(t < s): dis_r = (pizza[s] + s) - t;
// 實作: 建左查詢線段樹跟右查詢線段樹，用最小值pull
// 答案是 min(left_query(1, s) + t, right_query(s, end) + t);
// ---List Removals---
// 維護區間內有幾個數字被選過
// 用二分搜找右區間最小位，使得 ans - query == 1 ~ ans 被選過的數量
// ---CSES subarray queries:---
// tree[now].prefix = max(tree[lc].sum + tree[rc].prefix, tree[lc].prefix);
// tree[now].suffix = max(tree[lc].suffix+tree[rc].sum, tree[rc].suffix);
// tree[now].middle_max = max(lc 中, rc 中, lc 後 + rc 前, now 前, now 後)

// LazySegment

// polynomial queries
// 設置梯形的底跟加了幾次，apply_tag 時底為 l 的合，d 為加給次
// 所以 sum += (底 * 2 + 次 * 區間) * 區間 / 2;