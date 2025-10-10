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