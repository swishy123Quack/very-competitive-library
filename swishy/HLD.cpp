struct HLD{
    vector<int> head, par, h, pos, big;
    int n, indx = 0;
    Tree T;

    HLD(Tree &_T) : T(_T){
        n = T.n;
        head = par = h = pos = big = vector<int>(n, 0);
        dfs(0, -1);
        decompose(0, 0, -1);
    }
    int dfs(int u, int pre){
        ll res = 1; 
        big[u] = -1;
    
        int crr_size = 0;
        for (int v : T.edg[u]){
            if (v == pre)
                continue;
    
            par[v] = u; h[v] = h[u] + 1;
            int child_size = dfs(v, u);
    
            if (child_size > crr_size)
                big[u] = v, crr_size = child_size;
            res += child_size;
        }
    
        return res;
    }
    void decompose(int u, int root, int pre){
        head[u] = root, pos[u] = indx++;
        if (big[u] != -1)
            decompose(big[u], root, u);
        for (int v : T.edg[u]){
            if (v == pre || v == big[u])
                continue;
            decompose(v, v, u);
        }
    }
    ll query(int u, int v){
        ll res = -inf;
        while (head[u] != head[v]){
            if (h[head[u]] < h[head[v]])
                swap(u, v);
            maxi(res, st.get(pos[head[u]], pos[u]));
            u = par[head[u]];
        }
    
        if (h[u] < h[v])
            swap(u, v);
        maxi(res, st.get(pos[v], pos[u]));
    
        return res;
    }
};