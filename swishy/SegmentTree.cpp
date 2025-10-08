#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e10;
const int def = 2001;

//lib
template <typename T>
class SegmentTree{
public:
    int n;
    T defv;
    vector<T> st;

    SegmentTree(int n, T defv) : n(n), defv(defv){
        st = vector<T>(4 * n, defv);
    }
    
    void update(int i, T v){
        _update(0, n - 1, 0, i, v);
    }

    T get(int l, int r){
        return _get(0, n - 1, l, r, 0);
    }

private:
    T cmb(T l, T r){
        return l + r;
    }

    void _update(int l, int r, int crr, int i, T v){
        if (r < i || l > i)
            return;
    
        if (l == r){
            st[crr] = v;
            return;
        }
    
        int mid = (l + r) / 2;
        _update(l, mid, crr * 2 + 1, i, v);
        _update(mid + 1, r, crr * 2 + 2, i, v);
    
        st[crr] = cmb(st[crr * 2 + 1], st[crr * 2 + 2]);
    }
    
    T _get(int l, int r, int ql, int qr, int crr){
        if (qr < l || ql > r)
            return defv;
        if (l >= ql && r <= qr)
            return st[crr];
    
        int mid = (l + r) / 2;
        return cmb(_get(l, mid, ql, qr, crr * 2 + 1), _get(mid + 1, r, ql, qr, crr * 2 + 2));  
    }
};
//lib

void solve(){
    int n, q;
    cin >> n >> q;

    long long a[n];
    SegmentTree<long long> st(n, 0);

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