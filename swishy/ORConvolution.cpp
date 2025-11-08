vector<int> convolute_or(vector<int> &a, vector<int> &b){
    int n = a.size();
    for (int i = 0; i < n; i++) for (int j = 0; j < (1 << n); j++){
        if ((j >> i) & 1){
            a[j] += a[j - (1 << i)];
            b[j] += b[j - (1 << i)];
        }
    }
    for (int i = n - 1; i >= 0; i--){
        for (int j = (1 << n) - 1; j >= 0; j--){
            if ((j >> i) & 1)
                a[j] -= a[j - (1 << i)];
        }
    }
    auto c = vector<int>(n, 0);
    for (int i = n - 1; i < (1 << n); i++)  
        c[i] = a[i] * b[i];
    for (int i = n - 1; i >= 0; i--){
        for (int j = (1 << n) - 1; j >= 0; j--){
            if ((j >> i) & 1)
                c[j] -= c[j - (1 << i)];
        }
    }
}
// Don gian la dung dp sos de tinh cho A[i] va B[i]
// Sau do C[i] = a[i] * b[i]
// Luc nay dao nguoc dp sos de co C[i] voi moi i thay vi la toan bo subset cua i
