//find solution of ax = b (mod prime m)
vector<modu> gay(vector<vector<modu>> &a, vector<modu> &b){    
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++)
        a[i].push_back(b[i]);
    auto pos = vec(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++){
        int epic = -1;
        for (int i = row; i < n; i++){
            if (a[i][col])
                epic = i;
        }
        if (epic == -1)
            continue;
        pos[col] = row;
        for (int i = col; i <= m; i++)
            swap(a[row][i], a[epic][i]);
        for (int i = 0; i < n; i++){
            if (i != row){
                modu val = a[i][col] * a[row][col].inv();
                for (int j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * val;
            }
        }
        row++;
    }
    vector<modu> res(m, 0);
    for (int i = 0; i < m; i++){
        if (pos[i] != -1)
            res[i] = a[pos[i]][m] * a[pos[i]][i].inv();
    }
    for (int i = 0; i < n; i++){
        modu sum = 0;
        for (int j = 0; j < m; j++)
            sum += res[j] * a[i][j];
        if (sum != a[i][m])
            return {};
    }
    return res;
}