vector<int> pref_func(string s){
    int n = siz(s);
    vector<int> v(n);
 
    for (int i = 1; i < n; i++){
        ll j = v[i - 1];
        while (j > 0 && s[j] != s[i])
            j = v[j - 1];        
        if (s[j] == s[i])
            j++;
        v[i] = j;
    }
 
    return v;
}