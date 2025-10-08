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
const ll def = 7e6+1;
const ll mod = 1e9+7;

using namespace std;

typedef __int128_t i128;
i128 exeuclid(i128 a, i128 b, i128& x, i128& y){
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 d = exeuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

struct CBT{
    i128 A = 0, M = 0;
    void add(i128 a, i128 m){
        a = ((a % m) + m) % m;
        i128 _M = M;
        if (M == 0){
            A = a, M = m;
            return;
        }
        if (A == -1) return;
        i128 p, q;
        i128 g = exeuclid(M, m, p, q);
        if ((a - A) % g != 0){
            A = -1, M = -1;
            return;
        }
        i128 mul = (a - A) / g;
        M = m * M / g;
        A = (((_M * p * mul + A) % M) + M) % M;
    }
};

void solve(){
    ll n, x, y, vx, vy;
    read(n, x, y, vx, vy);

    ll g = gcd(vx, vy);
    vx /= g; vy /= g;

    CBT crt;
    crt.add(-x * vy, n * vy);
    crt.add(-y * vx, n * vx);

    if (crt.A == -1){
        print(-1);
        return;
    }
    ll t = crt.A / vx / vy;
    ll disx = x + vx * t, disy = y + vy * t;

    ll res = (disx + disy) / n - 2;
    res += ((disx + disy) / n) / 2;
    res += (abs(disy - disx) / n) / 2;

    print(res);
}   

/*
-x * vy
x + vx * t = 0 mod n
y + vy * t = 0 mod n 

vx * vy * t = -x * vy mod (n * vy)
vx * vy * t = -y * vx mod (n * vx)


*/

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);    

    if (ifstream("input.txt").good()){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int t = 1;
    read(t);

    while (t--){
        solve();
        nl;
    }
    return 0;
}