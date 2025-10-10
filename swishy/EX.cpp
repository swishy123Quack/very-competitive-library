ll MOD = 999999893;
ll sq = 2;
 
class EX {
  int re, im;
  static int trim(int a) {
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
    return a;
  }
  static int inv(const int a) {
    int ans = 1;
    for (int cur = a, p = MOD - 2; p; p >>= 1, cur = 1ll * cur * cur % MOD) {
      if (p&1) ans = 1ll * ans * cur % MOD;
    }
    return ans;
  };
public:
  EX(int re = 0, int im = 0) : re(re), im(im) {}
  EX& operator=(EX oth) { return re = oth.re, im = oth.im, *this; }
  int norm() const { 
    return trim((1ll * re * re - 1ll * sq * im % MOD * im) % MOD);
  }
  EX conj() const { 
    return EX(re, trim(MOD - im)); 
  }
  EX operator*(EX oth) const {
    return EX((1ll * re * oth.re + 1ll * sq * im % MOD * oth.im) % MOD,
              (1ll * re * oth.im + 1ll * im * oth.re) % MOD);
  };
  EX operator/(int n) const { 
    return EX(1ll * re * inv(n) % MOD, 1ll * im * inv(n) % MOD);
  }
  EX operator/(EX oth) const { return *this * oth.conj() / oth.norm(); }
  EX operator+(EX oth) const { return EX(trim(re + oth.re), trim(im + oth.im)); }
  EX operator-(EX oth) const {
    return EX(trim(re - oth.re), trim(im - oth.im));
  }
  EX pow(long long n) const {
    EX ans(1);
    for (EX a = *this; n; n >>= 1, a = a * a) {
      if (n&1) ans = a * ans;
    }
    return ans;
  }
  bool operator==(EX oth) const { return re == oth.re and im == oth.im; }
  bool operator!=(EX oth) const { return not (*this == oth); }
  int real() const& { return re; }
  int imag() const& { return im; }
};