/**
 * Author: Bjorn Martinsson
 * Date: 2024-01-23
 * License: 
 * Source: https://codeforces.com/blog/pajenegod
 * Description: Creates a centroid decomposition.
 * Usage:
 * 	auto treeAndRoot = centroid(graph);
 * Time: O(N)
 * Status: unkown
 */

#pragma once

#define remover(vec, v) vec.erase(find(all(vec), v))
 
struct ctd {
    vector<vi> children;
    int root;
};
 
ctd centroid(vector<vi> graph) {
    int n = sz(graph);
    vi subsize(n);
    auto dfs = [&](int u, auto&& self) -> int {
        for (auto v: graph[u]) {
            remover(graph[v], u);
            subsize[u] += self(v, self);
        }
        return ++subsize[u];
    };
    dfs(0, dfs);
    
    vector<vi> dec_tree(n);
    auto reroot = [&](int u, auto&& self) -> int {
        int N = subsize[u];
        for (bool found = 0; !found;) {
            found = 1;
            for (auto v: graph[u]) {
                if (subsize[v] > N / 2) {
                    found = 0;
                    subsize[u] = N - subsize[v];
                    remover(graph[u], v);
                    graph[v].push_back(u);
                    u = v;
                    break;
                }
            }
        }
        for (auto v: graph[u]) {
            dec_tree[u].push_back(self(v, self));
        }
        return u;
    };
    int dec_root = reroot(0, reroot);
    return {move(dec_tree), dec_root};
}

