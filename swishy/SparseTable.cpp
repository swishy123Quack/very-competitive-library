#include <bits/stdc++.h>
using namespace std;
 
#ifndef template
#ifndef define
 
#define ll long long
#define nl cout << endl;
#define x first
#define y second 
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
 
#endif
 
#ifndef print
void print(int x) {cout << x << ' ';}
void print(long long x) {cout << x << ' ';}
void print(unsigned x) {cout << x << ' ';}
void print(unsigned long long x) {cout << x << ' ';}
void print(float x) {cout << x << ' ';}
void print(long double x) {cout << x << ' ';}
void print(char x) {cout << x << ' ';}
void print(const string &x) {cout << x << ' ';}
void print(bool x) {cout << x << ' ';}
 
template<typename T, typename V>
void print(pair<T, V> &p) {print(p.x); print(p.y);}
template<typename T>
void print(vector<T> v) {for (int i = 0; i < v.size(); i++) print(v[i]);}
template<typename T>
void print(vector<vector<T>> v) {
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v[i].size(); j++)
            print(v[i][j]);
        nl;
    }
}
 
#endif
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> bool maxi(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool mini(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
template<class... Args>
auto vec(size_t n, Args&&... args) {
	if constexpr(sizeof...(args) == 1)
		return vector(n, args...);
	else
		return vector(n, vec(args...));
}
 
#endif
 
const long long inf = 1e10;
const long long mod = 2023;
const int def = 1e3+1;

//lib
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
//lib
 
void solve(){
    int n, q;
    cin >> n >> q;
 
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];
 
    SparseTable<int> rmq(a, [](int a, int b){
        return min(a, b);
    });
 
    while (q--){
        int l, r;
        cin >> l >> r;
 
        int res = rmq.get(--l, --r);
        cout << res << endl;
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    int t;
    t = 1;  
 
    while (t--){
        solve();
        nl;
    }
}