/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve() {
    int n; cin >> n;
    vector<i64> a(n), b(n);
    REP(i, n) cin >> a[i] >> b[i];

    i64 cur = 0;

    REPD(i, n) {
        a[i] += cur;
        i64 c = b[i] - a[i];
        i64 d = lib::mod(c, b[i]);
        debug(i, c, d);
        cur += d;
    }

    print(cur);
}

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
