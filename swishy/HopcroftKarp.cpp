struct HopcroftKarp{
    vector<vector<int>> edg;
    vector<int> U, V;
    vector<int> pu, pv;
    vector<int> dist;

    //NOTE: This graph is 1-indexed!!!
    HopcroftKarp(int n, int m){
        edg = vector<vector<int>>(n + 1);
        for (int i = 0; i < n; i++)
            U.push_back(i + 1);
        for (int i = 0; i < m; i++)
            V.push_back(i + 1);

        pu = vector<int>(n + 1, 0);
        pv = vector<int>(m + 1, 0);
        dist = vector<int>(n + 1, inf);
    }

    void add_edge(int u, int v){
        edg[u].push_back(v);
    }

    bool bfs(){
        queue<int> q;
        for (int u : U){
            if (!pu[u]){
                q.push(u);
                dist[u] = 0;
            }

            else
                dist[u] = inf;
        }

        dist[0] = inf;
        while (q.size() > 0){
            int u = q.front();
            q.pop();

            if (dist[u] < dist[0]){
                for (int v : edg[u]){
                    if (dist[pv[v]] == inf){
                        q.push(pv[v]);
                        dist[pv[v]] = dist[u] + 1;
                    }
                }
            }
        }

        if (dist[0] == inf)
            return 0;
        return 1;
    }

    bool dfs(ll u){
        if (u == 0) return 1;
        for (int v : edg[u]){
            if (dist[pv[v]] == (dist[u] + 1)){
                if (dfs(pv[v])){
                    pu[u] = v;
                    pv[v] = u;
                    return 1;
                }
            }
        }

        dist[u] = 0;
        return 0;
    }

    int solve(){
        int res = 0;
        while (bfs()){
            for (int u : U){
                if (!pu[u])
                    if (dfs(u))
                        res++;
            }
        }

        return res;
    }
};