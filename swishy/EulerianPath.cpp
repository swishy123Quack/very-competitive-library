vector<pl> edg[def];
vector<ll> path;
bool b[def];
 
void dfs(ll u){
    while (siz(edg[u])){
        auto [v, indx] = edg[u].back();
        edg[u].pop_back();
 
        if (b[indx])
            continue;
        b[indx] = 1;
        dfs(v);
    }
    path.push_back(u);
}