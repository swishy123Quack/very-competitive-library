#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e10;
const long long mod = 2023;
const int def = 1e3+1;

struct Graph{
    vector<vector<int>> edg;
    int n;

    Graph(int n) : n(n){
        edg = vector<vector<int>>(n, vector<int>());
    }
    void add(int u, int v){
        edg[u].push_back(v);
    }
    void bi_add(int u, int v){
        edg[u].push_back(v);
        edg[v].push_back(u);
    }
    void clear(){
        for (int u = 0; u < n; u++)
            edg[u].clear();
    }
    void remove_dup(){
        for (int u = 0; u < n; u++){
            sort(edg[u].begin(), edg[u].end());
            edg[u].erase(unique(edg[u].begin(), edg[u].end()), edg[u].end());
        }
    }
};

//lib
struct BridgeArt{
    Graph &G;
    vector<int> low, num, arts;
    vector<bool> isart;
    vector<pair<int, int>> bridges;
    int indx, n;

    BridgeArt(Graph &G) : G(G), n(G.n){
        indx = 0;
        low = num = vector<int>(n, 0);
        isart = vector<bool>(n, 0);

        for (int i = 0; i < n; i++){
            if (!num[i])
                dfs(i, i);
        }
        for (int i = 0; i < n; i++){
            if (isart[i])
                arts.push_back(i);
        }
    }

    void dfs(int u, int pre){
        low[u] = num[u] = ++indx;
        int cnt = 0;

        for (int v : G.edg[u]){
            if (v == pre) continue;
            if (!num[v]){
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                cnt++;
                if (u == pre){
                    if (cnt > 1) 
                        isart[u] = 1;
                }
                else{
                    if (num[u] <= low[v])
                        isart[u] = 1;
                }
                if (num[v] == low[v])
                    bridges.push_back({u, v});
            }
            else
                low[u] = min(low[u], num[v]);
        }
    }
};
//lib

void solve(){
    int n, m;
    cin >> n >> m;

    Graph G(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        G.bi_add(--u, --v);
    }

    BridgeArt bruh(G);
    cout << bruh.arts.size() << ' ' << bruh.bridges.size();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    t = 1;  

    while (t--)
        solve();
}
