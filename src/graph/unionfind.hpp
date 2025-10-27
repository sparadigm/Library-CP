#pragma once

#include <vector>
#include <numeric>
#include <algorithm>

class UnionFind {
public:
    std::vector<int> par;
    std::vector<int> siz;

    UnionFind(int N) : par(N + 1), siz(N + 1, 1) {
        // 全ての頂点が自分自身を親とする（par[i] = i）
        std::iota(par.begin(), par.end(), 0);
        // iota() : 指定した値から始まる整数列を生成
        // 今回の場合、par[i] = i
    }

    int root(int x) {
        // par[x]がx自身でないなら、親をたどって根を探す
        if (par[x] == x) return x;
        // 親をたどる過程で、自分の親を根に直接つなぎ替える（経路圧縮）
        return par[x] = root(par[x]);
    }

    void unite(int u, int v) {
        int rootU = root(u);
        int rootV = root(v);
        if (rootU == rootV) return; // すでに同じグループ

        // サイズが小さい方を大きい方につなぐ（Union by Size）
        if (siz[rootU] < siz[rootV]) std::swap(rootU, rootV);
        
        par[rootV] = rootU; // rootVの親をrootUにする
        siz[rootU] += siz[rootV]; // rootUのグループサイズを更新
    }

    bool same(int u, int v) {
        return root(u) == root(v);
    }

    int size(int x) {
        return siz[root(x)];
    }
};
