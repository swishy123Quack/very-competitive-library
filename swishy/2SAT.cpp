struct TwoSAT{
    vector<vector<int>> edg1, edg2;
    vector<int> scc, res;
    vector<bool> b;
    stack<int> topo;
    int n;

    TwoSAT(int n) : n(n){
        edg1 = edg2 = vector<vector<int>>(2 * n);
        scc = res = vector<int>(2 * n, 0);
        b = vector<bool>(2 * n, 0);
    }

    void dfs1(ll u){
        b[u] = 1;
        for (ll v : edg1[u]){
            if (!b[v])
                dfs1(v);
        }

        topo.push(u);
    }

    void dfs2(ll u, ll root){
        scc[u] = root;
        for (ll v : edg2[u]){
            if (scc[v] == -1)
                dfs2(v, root);
        }
    }

    bool solve(){
        for (int i = 0; i < 2 * n; i++){
            scc[i] = -1;
            if (!b[i])
                dfs1(i);
        }

        int j = 0;
        while (siz(topo)){
            ll u = topo.top();
            topo.pop();

            if (scc[u] == -1)
                dfs2(u, j++);
        }

        for (int i = 0; i < n; i++){
            if (scc[i * 2] == scc[i * 2 + 1])
                return 0;
            res[i] = scc[i * 2] > scc[i * 2 + 1];
        }

        return 1;
    }

    void add(int x, bool a, int y, bool b){
        int X = x * 2 + (a & 1), Y = y * 2 + (b & 1);
        int _X = x * 2 + 1 - (a & 1), _Y = y * 2 + 1 - (b & 1);

        edg1[_X].push_back(Y);
        edg1[_Y].push_back(X);
        edg2[Y].push_back(_X);
        edg2[X].push_back(_Y);
    }
};