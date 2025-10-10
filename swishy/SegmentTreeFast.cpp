template<typename T>
struct SegmentTreeFast{
    vector<T> a;
    T defv;
    int n;

    SegmentTreeFast(int n, T defv) : n(n), defv(defv){
        a = vector<T>(2 * n, defv);
    }

    T cmb(T a, T b){ //change if needed
        return a + b;
    }

    void build(){ //array is at i + n index
        for (int i = n - 1; i > 0; --i) 
            a[i] = cmb(a[i << 1], a[i << 1 | 1]);
    } 

    void update(int i, T v){
        for (a[i += n] = v; i > 1; i >>= 1)
            a[i >> 1] = cmb(a[i], a[i ^ 1]);
    }

    T get(int l, int r){
        r++;
        T res = defv;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) res = cmb(res, a[l++]);
            if (r&1) res = cmb(res, a[--r]);
        }

        return res;
    }
};