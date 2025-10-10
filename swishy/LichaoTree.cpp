struct LichaoTree{
    struct Line{
        ll a, b;
        Line() : a(0), b(-inf) {}
        Line(ll a, ll b): a(a), b(b) {}
        ll get(ll x){   
            return a * x + b;
        }
    };
public:
    vector<Line> st;
    int n;
    LichaoTree(int n) : n(n){
        st.resize(4 * n);
    }
    void add_line(Line line, int indx = 1, int l = 0, int r = -1){
        if (r == -1) r = n;
        int m = (l + r) / 2;
        bool left = line.get(l) > st[indx].get(l);
        bool mid = line.get(m) > st[indx].get(m);

        if (mid)
            swap(line, st[indx]);
        if (r - l == 1) return;
        else if (left != mid)
            add_line(line, 2 * indx, l, m);
        else
            add_line(line, 2 * indx + 1, m, r);
    }   
    ll query(ll x, int indx = 1, int l = 0, int r = -1){
        if (r == -1) r = n;
        if (r - l == 1) return st[indx].get(x);
        int mid = (l + r) / 2;
        if (x < mid)
            return max(st[indx].get(x), query(x, 2 * indx, l, mid));
        else
            return max(st[indx].get(x), query(x, 2 * indx + 1, mid, r));
    }
};