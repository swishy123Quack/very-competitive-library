#define uid(a, b) uniform_int_distribution<long long>(a, b)(rng) 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());