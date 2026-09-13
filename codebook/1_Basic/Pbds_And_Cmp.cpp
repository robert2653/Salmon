// pbds_multiset:
//	必須 = , 其他 STL 都不能
//	lower_bound, upper_bound 交換用法
//	不要用 find(x), erase(x), 用 upper_bound 拿到 it 再判斷
// order_of_key(x) 幾個元素嚴格小於 x
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T, class F = less<T>>
using pbds_set = tree<T, null_type, F, rb_tree_tag, tree_order_statistics_node_update>;
template<class T, class F = less_equal<T>>
using pbds_multiset = tree<T, null_type, F, rb_tree_tag, tree_order_statistics_node_update>;

// priority queue 小到大是 >, set 是 <
auto cmp = [](int i, int j) { return i > j; };
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

vector<int> a {1, 2, 5, 4, 3}; // 小心不要改到 a
auto cmp = [&a](int i, int j) { return a[i] > a[j]; };
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

vector<int> v {1, 2, 3, 4, 5};
upper_bound(v.begin(), v.end(), 2, [](int a, int b)
{ return a < b; }); // find first b that a < b, a is 2
lower_bound(v.begin(), v.end(), 2, [](int a, int b)
{ return a < b; }); // find first a that a < b fail, b is 2