#include         <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
#define            TASK   "test"
#define              ll   long long
#define             ull   unsigned ll
#define              db   long double
#define             pLL   pair<ll, ll>
#define             pLI   pair<ll, int>
#define             pIL   pair<int, ll>
#define             pII   pair<int, int>
#define             vec   vector
#define              vL   vec<ll>
#define             vvL   vec<vL>
#define              vI   vec<int>
#define             vvI   vec<vI>
#define            vvvI   vec<vvI>
#define           vvvvI   vec<vvvI>
#define              vD   vec<db>
#define             vvD   vec<vD>
#define             vLL   vec<pLL>
#define             vLI   vec<pLI>
#define             vIL   vec<pIL>
#define             vII   vec<pII>
#define            vvII   vec<vII>
#define              vS   vec<string>
#define             vvS   vec<vS>
#define              vB   vec<bool>
#define             vvB   vec<vB>
#define            umap   unordered_map
#define          gphash   gp_hash_table
#define            mset   multiset
#define            pque   priority_queue
#define          all(a)   a.begin(), a.end()
#define         rall(a)   a.rbegin(), a.rend()
#define       stt(a, n)   a.begin(), a.begin() + n
#define       stf(a, n)   a.begin() + n, a.end()
#define              eb   emplace_back
#define              pb   push_back
#define              pf   push_front
#define            popb   pop_back
#define            popf   pop_front
#define             ins   insert
#define             asg   assign
#define             rev   reverse
#define              fi   first
#define              se   second
#define              th   third
#define              ub   upper_bound
#define              lb   lower_bound
#define             ite   iterator
#define           fs(n)   fixed << setprecision(n)
 
using         namespace   std;
using         namespace   __gnu_pbds;
 
const ll          llINF = 1e18;
const int        intINF = 1e9;
const ll            MOD = 1e9 + 7;
 
template<   class T   >   
using       ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define            oset   ordered_set
 
template<     class A, 
              class B, 
              class C >   struct triple {
    A fi; B se; C th;
 
    triple() {}
    triple(A a,B b,C c) : fi(a), se(b), th(c) {}
};
#define            tIII   triple<int, int, int>
#define            tLLL   triple<ll, ll, ll>
#define            vIII   vec<tIII>
#define           vvIII   vec<vIII>
#define            vLLL   vec<tLLL>
 
mt19937                   rd(chrono::high_resolution_clock::now().time_since_epoch().count());
ll     Rand(ll L, ll R)   { return uniform_int_distribution<ll>(L, R)(rd); }
 
inline int     read() { 
    char c;    while (c = getchar(), c < '0' || c > '9'); int n = c - '0';
    while            (c = getchar(), c >= '0' && c <= '9') n = 10 * n + c - '0';
    return         n; }
 
vI          prime, lpf;
void  primeSieve(int n)   { prime.asg(1, 2); lpf.asg(n + 1, 2); lpf[0] = lpf[1] = 1;
                            for (int i = 3; i <= n; i += 2) { if (lpf[i] == 2) { lpf[i] = i; prime.pb(i); } 
                            for (int j = 0; j < prime.size() && i * prime[j] <= n && prime[j] <= lpf[i]; ++ j) lpf[i * prime[j]] = prime[j]; 
                          } }
vvI                dvs;
void    dvsSieve(int n)   { dvs.asg(n + 1, vI());
                            for (int i = 1; i <= n; ++ i) {
                            for (int j = i; j <= n; j += i) 
                            dvs[j].pb(i);  
                          } }
 
template<   class T   >   bool maximize(T &a, T b) { if (b > a) return a = b, 1; return 0; }
template<   class T   >   bool minimize(T &a, T b) { if (b < a) return a = b, 1; return 0; }
 
ll      gcd(ll a, ll b)   { return b ? gcd(b, a % b) : a; }
ll      lcm(ll a, ll b)   { return a / gcd(a, b) * b; }
 
ll  fastPow(ll n, ll p,
            ll m = MOD)   { ll r = 1; for (n %= m; p; p >>= 1) { if (p & 1) (r *= n) %= m; (n *= n) %= m; } return r; }
ll         invMod(ll n, 
            ll m = MOD)   { return fastPow(n, m - 2, m); }
 
ll          mask(int i)   { return i < 0 ? 0 : 1LL << i; }
bool   bit(ll n, int i)   { return n >> i & 1LL; }
#define        popcount   __builtin_popcountll
#define             clz   __builtin_clzll
#define             ctz   __builtin_ctzll