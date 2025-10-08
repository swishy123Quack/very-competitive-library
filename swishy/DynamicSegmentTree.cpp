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
#define cbit(i) __builtin_popcountll(i)
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
const ll def = 3e1;    

struct Node{
    ll sum, tl, tr;
    Node *l = nullptr, *r = nullptr;

    Node (ll _tl, ll _tr){
        tl = _tl; 
        tr = _tr; 
        sum = 0;
    }

    void extend(){
        if (tl == tr) return;
        ll mid = (tl + tr) / 2;

        if (!l)
            l = new Node(tl, mid);
        if (!r)
            r = new Node(mid + 1, tr);
    }
};

class funkysegtree{
    void _upd(Node *node, ll x, ll val){
        node->sum += val;
        if (node->tl > x || node->tr < x)
            return;
        if (node->tl == node->tr)
            return;

        ll mid = (node->tl + node->tr) / 2;
        node->extend();

        if (x <= mid)
            _upd(node->l, x, val);
        else
            _upd(node->r, x, val);
    }

    ll _get(Node *node, ll ql, ll qr){
        if (qr < node->tl || ql > node->tr)
            return 0;

        else if (ql <= node->tl && qr >= node->tr)
            return node->sum;

        ll mid = (node->tl + node->tr) / 2;
        node->extend();

        if (ql > mid)
            return _get(node->r, ql, qr);
        else if (qr <= mid)
            return _get(node->l, ql, qr);
        else
            return _get(node->l, ql, mid) + _get(node->r, mid + 1, qr);
    }

public:
    Node *root = nullptr;
    ll _size;

    funkysegtree(ll __size){
        root = new Node(0, __size);
        _size = __size;
    };

    void upd(ll x, ll val){
        _upd(root, x, val);
    }

    ll get(ll l, ll r){
        return _get(root, l, r);
    }
};

int main(){
    ll n, q;
    cin >> n >> q;

    funkysegtree st(1e9);
    while (q--){
        ll t, x, y;
        cin >> t >> x >> y;

        if (t == 1){
            x--;
            ll val = st.get(x, x);

            st.upd(x, y - val);
        }

        else
        {
            x--; y--;
            ll res = st.get(x, y);

            cout << res << nl;
        }
    }
}
