ll powMod(ll x, ll p, ll md);
ll gcd(ll x, ll y);
// danh sách các ước nguyên tố của x (có thể trùng nhau)
vector<ll> factorize(ll x);
// hàm phi Euler
ll phi(ll n) {
    auto ps = factorize(n);
    ll res = n;
    ll last = -1;
    for (auto p : ps) {
        if (p != last) {
            res = res / p * (p - 1);
            last = p;
        }
    }
    return res;
}
// Cấp của a mod m
ll ord(ll a, ll m) { // primitive root
    if (gcd(a, m) != 1)
        return -1;
    ll res = phi(m);
    auto ps = factorize(res);
    for (auto p : ps)
        if (powMod(a, res / p, m) == 1)
            res /= p;
    return res;
}


ll DiscreteLog(ll a, ll b, ll m) { // a^x = b (mod m)
  const int B = 35000;
  ll k = 1 % m, ans = 0, g;
  while ((g = gcd(a, m)) > 1) {
    if (b == k) return ans;
    if (b % g) return -1;
    b /= g, m /= g, ans++, k = (k * a / g) % m;
  }
  if (b == k) return ans;
  unordered_map <ll, int> m1;
  ll tot = 1;
  for (int i = 0; i < B; ++i)
    m1[tot * b % m] = i, tot = tot * a % m;
  ll cur = k * tot % m;
  for (int i = 1; i <= B; ++i, cur = cur * tot % m)
    if (m1.count(cur))
      return 1ll * i * B - m1[cur] + ans;
  return -1;
}
