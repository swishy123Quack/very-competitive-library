modu fact[def], invf[def];
modu nCk(ll n, ll k){
    if (k == 0 || n == k) return 1;
    if (n < k) return 0;
    
    modu res = fact[n] * invf[k];
    res *= invf[n - k];
 
    return res;
}
 
void initalize(){
    fact[0] = 1;
    for (int i = 1; i < def; i++)
        fact[i] = fact[i - 1] * modu(i) % mod;
 
    invf[def - 1] = fact[def - 1].inv();
    for (int i = def - 2; i >= 0; i--)
        invf[i] = invf[i + 1] * modu(i + 1);
}