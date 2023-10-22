/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

#include "timer.hpp"

int N, D, Q;
int query_count = 0;

std::vector<std::set<int>> relations;


template<std::ranges::range R0, std::ranges::range R1>
int query(const R0& r0, const R1& r1) noexcept {
    cout << std::ranges::size(r0) << " " << std::ranges::size(r1) << " ";
    print << r0 << " " << r1;
    cout << std::endl;

    char res; cin >> res;

    ++query_count;
    debug(query_count, r0, r1, res);

    if(res == '<') return -1;
    if(res == '=') return 0;
    if(res == '>') return 1;

    assert(false);
}

std::map<spair<std::vector<int>>,int> memo;
template<std::ranges::range R0, std::ranges::range R1>
int compare(const R0& r0, const R1& r1) noexcept {
    std::vector<int> v0(std::ranges::begin(r0), std::ranges::end(r0));
    std::vector<int> v1(std::ranges::begin(r1), std::ranges::end(r1));

    int rev = 1;

    std::ranges::sort(v0), std::ranges::sort(v1);
    if(v0 > v1) std::swap(v0, v1), rev = -1;

    if(memo.contains({ v0, v1 })) return memo[{ v0, v1 }] * rev;

    const auto res = query(v0, v1);
    return (memo[{ v0, v1 }] = res) * rev;

    assert(false);
}

valarray<int> inds, rank;

signed main() {
    lib::timer timer(1500);

    cin >> N >> D >> Q;
    debug(N, D, Q);

    inds.resize(N);
    std::iota(ALL(inds), 0);

    int sorted_successfully = true;
    {
        auto comp = [&](int i, int j) -> bool {
            if(query_count >= Q) {
                sorted_successfully = false;
                return lib::rand() % 2;
            }
            const int res = compare(std::array<int,1>{ i }, std::array<int,1>{ j });
            return res < 0;
        };

        inds.stable_sort(comp);
        debug(inds);
    }

    if(rank.size() == 0) {
        rank.resize(N);
        REP(i, N) rank[inds[i]] = i;
    }

    struct comp_by_order {
        inline bool operator()(const int i, const int j) const noexcept {
            return rank[i] < rank[j];
        }
    };

    valarray<lib::set<int,comp_by_order>> divide(D);
    {
        int i = N;
        while(true) {
            REP(j, D) {
                divide[j].insert(inds[--i]);
                if(i <= 0) break;
            }
            if(i <= 0) break;
            std::ranges::reverse(divide);
        }
    }

    while(
        (Q - query_count > 3 * (D - 1) / 2) and
        not timer.expired()
    ) {
        debug(query_count, Q);
        valarray<int> p(D); std::iota(ALL(p), 0);
        const auto [ min, max ] = std::minmax_element(
            ALL(p),
            [&](int i, int j) {
                if(divide[i].empty()) return true;
                if(divide[j].empty()) return false;
                return compare(divide[i], divide[j]) < 0;
            }
        );
        divide[*min].insert(divide[*max].min());
        divide[*max].erase(divide[*max].begin());
        debug(divide);
    }
    debug(query_count);

    REP(Q - query_count) {
        cout << "1 1 0 1" << std::endl;
        char _; cin >> _;
    }

    valarray<int> ans(N);
    REP(d, D) ITR(v, divide[d]) ans[v] = d;
    print(ans);
}
