ll bit[1001][1001];
ll n, m;

void update(ll x, ll y, ll val){
	for (; y <= n; y += (y & (-y))){
		for (ll i = x; i <= m; i += (i & (-i)))
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