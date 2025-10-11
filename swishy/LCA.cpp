struct LCA{
    vector<vector<int>> f;
    Tree T;
    int n, k;

    LCA(Tree &_T) : T(_T){
        n = T.n; k = log2(n) + 2;
        for (int i = 0; i < n; i++)
            f.push_back(vector<int>(k, -1));
        T.get_info();
        
        for (int i = 0; i < n; i++)
            f[i][0] = T.par[i];
        for (int j = 1; j < k; j++) for (int i = 0; i < n; i++){
            int p = f[i][j - 1];
            if (p != -1)
                f[i][j] = f[p][j - 1];
        }
    }

    int get(int u, int v){
        if (T.depth[u] < T.depth[v])
            swap(u, v);
        for (int i = k - 1; i >= 0; i--){
            if (f[u][i] != -1 && T.depth[f[u][i]] >= T.depth[v])
                u = f[u][i];
        }
        if (u == v) return u;
        for (int i = k - 1; i >= 0; i--){
            if (f[u][i] != -1 && f[u][i] != f[v][i])
                u = f[u][i], v = f[v][i];
        }
        return T.par[u];
    }
};