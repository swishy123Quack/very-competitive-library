#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e10;
const int def = 2001;

//lib
template<typename T>
struct SegmentTreeFast{
    vector<T> a;
    T defv;
    int n;

    SegmentTreeFast(int n, T defv) : n(n), defv(defv){
        a = vector<T>(2 * n, defv);
    }

    T cmb(T a, T b){ //change if needed
        return a + b;
    }

    void build(){ //array is at i + n index
        for (int i = n - 1; i > 0; --i) 
            a[i] = cmb(a[i << 1], a[i << 1 | 1]);
    } 

    void update(int i, T v){
        for (a[i += n] = v; i > 1; i >>= 1)
            a[i >> 1] = cmb(a[i], a[i ^ 1]);
    }

    T get(int l, int r){
        r++;
        T res = defv;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) res = cmb(res, a[l++]);
            if (r&1) res = cmb(res, a[--r]);
        }

        return res;
    }
};
//lib

void solve(){
    int n, q;
    cin >> n >> q;

    long long a[n];
    SegmentTreeFast<long long> st(n, 0);

    for (int i = 0; i < n; i++){
        cin >> a[i];
        st.update(i, a[i]);
    }
    
    while (q--){
        int l, r;
        cin >> l >> r;

        long long val = st.get(l - 1, r - 1);   
        cout << val << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    t = 1;

    while (t--)
        solve();
}