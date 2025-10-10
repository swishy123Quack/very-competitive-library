template<typename T>
class SegmentTreeLazy{
public:
    vector<T> st, lazy;
    T defv;
    int n; 

    SegmentTreeLazy(int n, T defv) : n(n), defv(defv){
        st = vector<T>(n * 4, defv);
        lazy = vector<T>(n * 4, defv);
    }

    void update(int l, int r, T v){
        _update(0, n - 1, 0, l, r, v);
    }

    T get(int l, int r){
        return _get(0, n - 1, l, r, 0);   
    }

private:
    T cmb(T l, T r){
        return l + r;
    }

    void push(int i, int l, int r){
        int mid = (l + r) / 2;
        lazy[i * 2 + 1] += lazy[i];
        lazy[i * 2 + 2] += lazy[i];
        
        st[i * 2 + 1] += (mid - l + 1) * lazy[i];
        st[i * 2 + 2] += (r - mid) * lazy[i];
    
        lazy[i] = 0; 
    }
    
    void _update(int l, int r, int crr, int ql, int qr, T v){
        if (qr < l || ql > r)
            return;
    
        if (l >= ql && r <= qr){
            st[crr] += (r - l + 1) * v;
            lazy[crr] += v;
            return;
        }
    
        push(crr, l, r);
        int mid = (l + r) / 2;
        _update(l, mid, crr * 2 + 1, ql, qr, v);
        _update(mid + 1, r, crr * 2 + 2, ql, qr, v);
    
        st[crr] = cmb(st[crr * 2 + 1], st[crr * 2 + 2]);
    }
    
    T _get(int l, int r, int ql, int qr, int crr){
        if (qr < l || ql > r)
            return defv;
        if (l >= ql && r <= qr)
            return st[crr];
    
        push(crr, l, r);
        int mid = (l + r) / 2;
        return cmb(_get(l, mid, ql, qr, crr * 2 + 1), _get(mid + 1, r, ql, qr, crr * 2 + 2));  
    }
};