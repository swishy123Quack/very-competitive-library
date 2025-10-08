vector<int> z_func(string s){
	int n = s.size();
	vector<int> v(n);
 
	int l = 0, r = 0;
	for (int i = 1; i < n; i++){
		if (i < r)
			v[i] = min(r - i, v[i - l]);
		while ((v[i] + i) < n && s[v[i]] == s[v[i] + i])
			v[i]++;
		if ((v[i] + i) > r)
			l = i, r = v[i] + i;	
	}
 
	return v;
}