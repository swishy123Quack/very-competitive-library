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
#include <complex>
#include <cstring>
#include <memory>
#include <bitset>
#include <sstream>
#include <cmath>
#include <numeric>
#include <numbers>
#include <fstream>

using namespace std;

#ifndef template
#ifndef define

#define ll long long
#define ld long double
#define pl pair<ll, ll>
#define pi pair<int, int>
#define nl cout << '\n';
#define x first
#define y second 
#define cbit(x) __builtin_popcountll(x)
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
#define siz(x) (int)x.size()
#define all(x) (x).begin(), (x).end() 

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

using namespace std;
const ll inf = 1e18;
const ll def = 1e6+1;
const ll mod = 1e9+7;

using namespace std;

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

void solve(){
    int n, m;
    read(n, m);
    
    auto a = vec(n, m, modu(0));
    auto b = vec(n, modu(0));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int val; read(val);
            a[i][j] = val;
        }
        int val; read(val);
        b[i] = val;
    }
    auto res = gay(a, b);
    if (res == vector<modu>()){
        print(-1);
        return;
    }
    for (int i = 0; i < m; i++)
        cout << res[i] << ' ';
}   

/*
*/

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);    

    if (ifstream("input.txt").good()){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int t = 1;
    while (t--){
        solve();
        nl;
    }
    return 0;
}