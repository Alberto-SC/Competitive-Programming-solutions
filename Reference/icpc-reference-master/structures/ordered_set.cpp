#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds; // or pb_ds;

template<typename T, typename B = null_type>
using oset = tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Usage: oset<int> s | s.find_by_order | s.order_of_key
// Obs: Multiset -> replace less<T> by less_equal<T>
// Note that you are changing the comparator & lower_bound change a little
