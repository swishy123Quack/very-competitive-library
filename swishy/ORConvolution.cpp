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
// Đơn giản là dùng dp sos để tính cho A[i] và B[i]
// Sau đo C[i] = a[i] * b[i]
// Lúc này đảo ngược dp sos để có C[i] với mỗi i thay vi là toàn bộ subset của i
