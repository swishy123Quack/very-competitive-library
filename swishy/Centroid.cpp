vector<ll> edg[def];
bool dead[def]; 
ll cnt[def];
 
void dfs(ll u, ll pre){
	cnt[u] = 1;
	for (ll v : edg[u]){
		if (v == pre || dead[v])
			continue;	
		dfs(v, u);
		cnt[u] += cnt[v]; 
	}
}
 
ll centroid(ll u, ll pre, ll n){
	for (ll v : edg[u]){
		if (v == pre || dead[v])
			continue;
		if (cnt[v] > (n / 2))
			return centroid(v, u, n);
	}
	return u;
}
long long get(ll u){
	dfs(u, -1);
	ll root = centroid(u, -1, cnt[u]);
	dead[root] = 1;

	for (ll v : edg[root]){
		if (!dead[v])
			get(v);
	}
	return res;
}