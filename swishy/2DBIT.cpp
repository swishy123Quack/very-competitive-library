#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define ll int
#define ld long double
#define fu(i, a, b) for(ll i = a; i < b; i++)
#define fd(i, a, b) for(ll i = a - 1; i >= b; i--)
#define fastifier ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
#define x first
#define y second
#define nl '\n'
#define pl pair<ll, ll>
#define pd pair<ld, ld>
#define siz(x) (ll)x.size()
#define bit(i, k) (i & (1ll << k))
#define cbit(i) __builtin_popcountll(i)
#define fileInput freopen("lichsu-thptqg.inp", "r", stdin);
#define fileOutput freopen("lichsu-thptqg.out", "w", stdout);
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng) 
#define all(v) v.begin(), v.end()
 
template<class T> using ordset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template<class T> bool maxi(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; 
}
 
template<class T> bool mini(T& a, const T& b) {
	return a > b ? a = b, 1 : 0;
}
 
const ll inf = 1e16+1;
const ll mod = 1e9+7;
const ll def = 1e5+1;
const ld eps = 0.0000000001;
const ll base = 28837;

ll bit[1001][1001];
ll n;
 
void update(ll x, ll y, ll val){
	for (; y <= n; y += (y & (-y))){
		for (ll i = x; i <= n; i += (i & (-i)))
			bit[y][i] += val;
	}
}
 
ll query(ll x, ll y){
	ll res = 0;
	for (ll i = y; i; i -= (i & (-i)))
		for (ll j = x; j; j -= (j & (-j)))
			res += bit[i][j];
	return res;
}
 
ll query(ll x1, ll y1, ll x2, ll y2){
	ll res = query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
	return res;
}
 
void solve(){
	cin >> n;
	ll q;
	cin >> q;
 
	string s[n];
	fu(i, 0, n)
		cin >> s[i];
 
	fu(i, 0, n) fu(j, 0, n){
		if (s[i][j] == '*')
			update(i + 1, j + 1, 1);
	}
 
	while (q--){
		ll t; cin >> t;
		if (t == 1){
			ll x, y;
			cin >> x >> y;
 
			if (s[x - 1][y - 1] == '*'){
				update(x, y, -1);
				s[x - 1][y - 1] = '.';
			} 
			else
			{
				update(x, y, 1);
				s[x - 1][y - 1] = '*';
			}
		}
 
		else{
			ll x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
 
			cout << query(x1, y1, x2, y2) << nl;
		}
	}
}       
       
int main(){
	fastifier;
    ll t = 1;
    
	while (t--)
		solve();
}