#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define ll long long
#define fu(i, a, b) for(ll i = a; i < b; i++)
#define fd(i, a, b) for(ll i = a - 1; i >= b; i--)
#define fastifier ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
#define x first
#define y second
#define nl '\n'
#define pl pair<ll, ll>
#define siz(x) (ll)x.size()
#define bit(i, k) (i & (1 << k))
#define cbit(i) __builtin_popcount(i)
#define fileInput freopen("in.inp", "r", stdin);
#define fileOutput freopen("dominating.out", "w", stdout);
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
template<class T> using ordset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template<class T> bool maxi(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}
 
template<class T> bool mini(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}
 
const ll inf = 1e9;
const ll mod = 1e9+7;
const ll def = 2e5+1;    

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(ll a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}

void solve(){
    ll n, m;
    cin >> n >> m;

    ll a[n];
    fu(i, 0, n)
        a[i] = 0;

    vector<Vertex*> roots2;
    roots2.push_back(build(a, 0, n - 1));

    pl sm[m];
    fu(i, 0, m){
        cin >> sm[i].x >> sm[i].y;
        sm[i].x--; sm[i].y--;
    }

    ll q;
    cin >> q;

    fu(i, 0, q){
        ll x;
        cin >> x;

        x--;
        roots2.push_back(update(roots2.back(), 0, n - 1, x, 1));
    }

    ll res = -1;
    fu(i, 0, m){
        ll l = 0, r = q, mid = (l + r) / 2;
        ll good = (sm[i].y - sm[i].x + 1) / 2;
        good++;

        while (l < r){
            ll cnt = get_sum(roots2[mid], 0, n - 1, sm[i].x, sm[i].y);
            if (cnt >= good)
                r = mid;
            else
                l = mid + 1;

            mid = (l + r) / 2;
        }

        ll cnt = get_sum(roots2[r], 0, n - 1, sm[i].x, sm[i].y);
        if (cnt >= good){
            if (res == -1)
                res = r;
            else
                mini(res, r);
        }
    }

    cout << res << nl;
}           

int main(){
    fastifier; 
    ll t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    
    return 0;

}