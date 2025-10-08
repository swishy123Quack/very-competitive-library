#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <map>

using namespace std;

#ifndef template
#ifndef define
 
#define ll long long
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
const int def = 25000;
const int M = 4000;

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
 
template<ll mod1 = 1000000007, ll mod2 = 1000000009>
struct dmodu{
    modu<mod1> m1;
    modu<mod2> m2;
    
    dmodu(){m1 = 0; m2 = 0;}
    dmodu(modu<mod1> _m1, modu<mod2> _m2){
        m1 = _m1; m2 = _m2;
    }
    bool operator==(dmodu const& other) { return (m1 == other.m1 && m2 == other.m2); }
    dmodu operator+(dmodu const& other){ return dmodu(m1 + other.m1, m2 + other.m2); }
    dmodu operator-(dmodu const& other){ return dmodu(m1 - other.m1, m2 - other.m2); }
    dmodu operator*(dmodu const& other){ return dmodu(m1 * other.m1, m2 * other.m2); }
    dmodu operator/(dmodu const& other){ return dmodu(m1 / other.m1, m2 / other.m2); }
    dmodu operator+(ll const& other){ return dmodu(m1 + modu<mod1>(other), m2 + modu<mod2>(other)); }
    dmodu operator-(ll const& other){ return dmodu(m1 - modu<mod1>(other), m2 - modu<mod2>(other)); }
    dmodu operator*(ll const& other){ return dmodu(m1 * modu<mod1>(other), m2 * modu<mod2>(other)); }
    dmodu operator/(ll const& other){ return dmodu(m1 / modu<mod1>(other), m2 / modu<mod2>(other)); }
    dmodu operator+=(dmodu const& other){ m1 = m1 + other.m1; m2 = m2 + other.m2; return *this; }
    dmodu operator-=(dmodu const& other){ m1 = m1 - other.m1; m2 = m2 - other.m2; return *this; }
    dmodu operator*=(dmodu const& other){ m1 = m1 * other.m1; m2 = m2 * other.m2; return *this; }
    dmodu operator/=(dmodu const& other){ m1 = m1 / other.m1; m2 = m2 / other.m2; return *this; }
    dmodu operator++(int) {dmodu tmp = *this; m1++; m2++; return tmp;}
    dmodu operator++() {m1++; m2++; return *this;}
    dmodu operator--(int) {dmodu tmp = *this; m1--; m2--; return tmp;}
    dmodu operator--() {m1--; m2--; return *this;}
    dmodu operator-() {return dmodu(-m1, -m2);}
};
 
const ll base = 2;
typedef dmodu<878089999, 388701809> dd;

struct hashu{
	ll n;
	vector<dd> p, h;
 
	hashu(string s){
		n = s.size();
		p = vector<dd>(n + 1);
		h = vector<dd>(n + 1);
 
		p[0] = {1, 1};
		for (int i = 1; i <= n; i++)
			p[i] = p[i - 1] * base;
		for (int i = 1; i <= n; i++)
			h[i] = (h[i - 1] * base) + (s[i - 1] - '0');
	}
 
	dd get(ll l, ll r){
		return h[r + 1] - (h[l] * p[r - l + 1]);
	}
};

void solve(){
    int n, m;
    read(n, m);
    
    vector<string> s(n);
    for (int i = 0; i < n; i++) 
        cin >> s[i];

    map<pair<ll, ll>, int> mp;
    for (int i = 0; i < m; i++){
        string t = "";
        for (int j = 0; j < n; j++)
            t += s[j][i];

        hashu h(t);
        for (int j = 0; j < t.size(); j++){
            dd val;
            if (j > 0)
                val += h.h[j] * base;

            val += dd(1, 1) - (t[j] - '0');
            val *= h.p[t.size() - j - 1];
            if (j < t.size() - 1)
                val += h.get(j + 1, t.size() - 1);

            mp[{val.m1, val.m2}]++;
        }
    }

    int good = 0;
    for (auto it : mp)
        good = max(good, it.y);

    for (int i = 0; i < m; i++){
        string t = "";
        for (int j = 0; j < n; j++)
            t += s[j][i];

        hashu h(t);
        for (int j = 0; j < t.size(); j++){
            dd val;
            if (j > 0)
                val += h.h[j] * base;

            val += dd(1, 1) - (t[j] - '0');
            val *= h.p[t.size() - j - 1];
            if (j < t.size() - 1)
                val += h.get(j + 1, t.size() - 1);

            if (mp[{val.m1, val.m2}] == good){
                if (t[j] == '1')
                    t[j] = '0';
                else
                    t[j] = '1';
                cout << good << endl;
                cout << t << endl;
                return;
            }
        }
    }
    cout << "skibidi";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    int t;
    read(t);

    while (t--){
        solve();
        nl;
    }
}