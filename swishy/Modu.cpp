#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iomanip>
#include <queue>
#include <cassert>

using namespace std;

#ifndef template
#ifndef define
 
#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define pb push_back
#define nl cout << '\n';
#define x first
#define y second 
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
 
#endif
 
#ifndef print
void print(size_t x) {cout << x << ' ';}
void print(int x) {cout << x << ' ';}
void print(long long x) {cout << x << ' ';}
void print(float x) {cout << x << ' ';}
void print(long double x) {cout << x << ' ';}
void print(char x) {cout << x << ' ';}
void print(const char* x) {cout << x << ' ';}
void print(bool x) {cout << x << ' ';}
void print(string &x) {cout << x << ' ';}
 
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
template <typename T, typename... V>
void print(T t, V&&... v) {print(t); print(v...);}
 
#endif

#ifndef read
void read(int &x) {cin >> x;}
void read(long long &x) {cin >> x;}
void read(unsigned &x) {cin >> x;}
void read(unsigned long long &x) {cin >> x;}
void read(float &x) {cin >> x;}
void read(long double &x) {cin >> x;}
void read(char &x) {cin >> x;}
void read(string &x) {cin >> x;}
void read(bool &x) {cin >> x;}

template<typename T> 
void read(vector<T> &v) {
    for (int i = 0; i < v.size(); i++)
        read(v[i]);
}
template <typename T, typename... V>
void read(T &t, V&... v) {read(t); read(v...);}
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
 
const long long inf = 1e9;
const long long mod = 1e9+7;
const int def = 1e6+1;

//lib
template<ll mod = 1000000007>
struct modu{
    ll val;
    modu(ll x){
        val = x;
        val %= mod;
        if (val < 0) val += mod;    
    }
    modu(){ val = 0; }
 
    operator ll() const { return val; }
    modu operator+(modu const& other){ return val + other.val; }
    modu operator-(modu const& other){ return val - other.val; }
    modu operator*(modu const& other){ return val * other.val; }
    modu operator/(modu const& other){ return *this * other.inv(); }
    modu operator+=(modu const& other) { *this = *this + other; return *this; }
    modu operator-=(modu const& other) { *this = *this - other; return *this; }
    modu operator*=(modu const& other) { *this = *this * other; return *this; }
    modu operator/=(modu const& other) { *this = *this / other; return *this; }
    modu operator++(int) {modu tmp = *this; *this += 1; return tmp;}
    modu operator++() {*this += 1; return *this;}
    modu operator--(int) {modu tmp = *this; *this -= 1; return tmp;}
    modu operator--() {*this -= 1; return *this;}
    modu operator-() {return modu(-val);}
    friend ostream& operator<<(ostream& os, modu const& m) { return os << m.val; }
    friend istream& operator>>(istream& is, modu & m) { return is >> m.val; }
 
    modu pow(ll x) const{
        if (x == 0) 
            return 1;
        if (x % 2 == 0){
            modu tmp = pow(x / 2);
            return tmp * tmp;
        }
        else
            return pow(x - 1) * *this;
    }
 
    modu inv() const{ return pow(mod - 2); }
};
//lib

template <typename T>
struct Matrix{
    vector<vector<T>> m;
    Matrix (vector<vector<T>> &m) : T(m){}
    Matrix (int r, int c) {
        m = vector<vector<T>>(r, vector<T>(c));
    }

    int row() const {return m.size();}
    int col() const {return m[0].size();}

    static Matrix identity(int n){
        Matrix res = Matrix(n, n);
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        return res;
    }

    auto & operator [] (int i) { return m[i]; }
    const auto & operator[] (int i) const { return m[i]; }

    Matrix operator * (const Matrix &b){
        Matrix a = *this;
        assert(a.col() == b.row());

        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); i++)
            for (int j = 0; j < b.col(); j++)
                for (int k = 0; k < a.col(); k++)
                    c[i][j] += a[i][k] * b[k][j];
        return c;
    }

    Matrix pow(ll x){
        assert(row() == col());
        Matrix crr = *this, res = identity(row());
        while (x > 0){
            if (x % 2 == 1) 
                res = res * crr;
            crr = crr * crr;
            x /= 2;
        }
        return res;
    }
};

void solve(){
    ll r, n, k;
    read(r, n, k);

    vector<int> nxt[1 << r];
    for (int i = 0; i < (1 << r); i++){
        for (int j = 0; j < (1 << r); j++){
            bool ok = 1;
            for (int u = 0; u < r; u++){
                bool flag1 = (i & (1 << u)) != 0, flag2 = (j & (1 << u)) != 0;
                if (flag1 && flag2) 
                    ok = 0;
            }
            
            int x = i | j;
            int last = -1;

            for (int u = 0; u < r + 1; u++){
                if (u == r || (x & (1 << u)) != 0){
                    if ((u - last) % 2 == 0) 
                        ok = 0;
                    last = u;
                }
            }
            if (ok)
                nxt[i].push_back(j);
        }
    }

    Matrix<modu<>> c(1 << r, 1 << r);
    for (int u = 0; u < (1 << r); u++){
        for (int v : nxt[u])
            c[v][u] = 1;
    }

    Matrix<modu<>> res(1, 1 << r);
    res[0][(1 << r) - 1] = 1;

    map<ll, int> mp;
    for (int i = 0; i < k; i++){
        ll x, y;
        read(x, y);
        mp[y] |= (1 << (x - 1));
    }

    vector<pair<ll, int>> dead;
    for (auto it : mp)
        dead.push_back(it);

    sort(dead.begin(), dead.end());
    ll last = 0;

    for (int i = 0; i < dead.size(); i++){
        res = res * c.pow(dead[i].x - last);
        last = dead[i].x;

        Matrix<modu<>> _res(1, 1 << r);
        for (int j = 0; j < (1 << r); j++){
            if ((j & dead[i].y) != 0) continue;
            _res[0][j | dead[i].y] = res[0][j];
        }

        res = _res;
    }

    res = res * c.pow(n - last);
    modu<> val;

    for (int i = 0; i < (1 << r); i++){
        bool ok = 1;
        last = -1;
        for (int u = 0; u < r + 1; u++){
            if (u == r || (i & (1 << u)) != 0){
                if ((u - last) % 2 == 0) 
                    ok = 0;
                last = u;
            }
        }
        if (ok)
            val += res[0][i];
    }

    cout << val << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    int t;
    t = 1;
    
    while (t--){
        solve();
    }
}
