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
struct StronglyConnected{
    Graph &G;
    vector<vector<int>> components;
    vector<int> low, num, new_num;
    vector<bool> deleted;
    stack<int> st;
    int indx, scc, n;

    StronglyConnected(Graph &G) : G(G), n(G.n){
        low = num = new_num = vector<int>(n, 0);
        indx = scc = 0;
        deleted = vector<bool>(n, 0);
        
        for (int i = 0; i < n; i++){
            if (!num[i])
                dfs(i);
        }
    }

    void dfs(int u){
        low[u] = num[u] = ++indx;
        st.push(u);

        for (int v : G.edg[u]){
            if (deleted[v]) continue;
            if (!num[v]){
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else
                low[u] = min(low[u], num[v]);
        }

        if (low[u] == num[u]){
            int crr = -1;
            vector<int> cmp;

            while (crr != u){
                crr = st.top();
                cmp.push_back(crr);
                st.pop();

                new_num[crr] = scc; 
                deleted[crr] = 1;
            }

            components.push_back(cmp);
            scc++;
        }   
    }
    
    void compress(){
        Graph _G(scc);
        for (int u = 0; u < n; u++){
            for (int v : G.edg[u]){
                int _u = new_num[u], _v = new_num[v];
                if (_u != _v)
                    _G.add(_u, _v);
            }
        }
        G = _G;
    }
};
//lib

void solve(){
    int n, m;
    cin >> n >> m;

    Graph G(n);
    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        G.add(--u, --v);
    }

    StronglyConnected scc(G);
    cout << scc.scc << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    t = 1;  

    while (t--)
        solve();
}