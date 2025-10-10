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