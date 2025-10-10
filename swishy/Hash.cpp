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