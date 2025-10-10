template <typename T, class Combine = function<T(const T &, const T &)>> 
struct SparseTable{
    vector<vector<T>> f;
    vector<int> lg;
    Combine cmb;
    int n;
 
    SparseTable(vector<T> &init, const Combine &cmb) : n(init.size()), cmb(cmb){
        lg = vector<int>(n + 1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; i++){
            f.push_back(vector<int>(lg[n] + 1, -1));
            f[i][0] = init[i];
        }
        for (int j = 1; (1 << j) <= n; j++){
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
                f[i][j] = cmb(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
 
    T get(int l, int r){
        int k = lg[r - l + 1];
        return cmb(f[l][k], f[r - (1 << k) + 1][k]);
    }
};