struct Node{
    ll sum, tl, tr;
    Node *l = nullptr, *r = nullptr;

    Node (ll _tl, ll _tr){
        tl = _tl; 
        tr = _tr; 
        sum = 0;
    }

    void extend(){
        if (tl == tr) return;
        ll mid = (tl + tr) / 2;

        if (!l)
            l = new Node(tl, mid);
        if (!r)
            r = new Node(mid + 1, tr);
    }
};

class funkysegtree{
    void _upd(Node *node, ll x, ll val){
        node->sum += val;
        if (node->tl > x || node->tr < x)
            return;
        if (node->tl == node->tr)
            return;

        ll mid = (node->tl + node->tr) / 2;
        node->extend();

        if (x <= mid)
            _upd(node->l, x, val);
        else
            _upd(node->r, x, val);
    }

    ll _get(Node *node, ll ql, ll qr){
        if (qr < node->tl || ql > node->tr)
            return 0;

        else if (ql <= node->tl && qr >= node->tr)
            return node->sum;

        ll mid = (node->tl + node->tr) / 2;
        node->extend();

        if (ql > mid)
            return _get(node->r, ql, qr);
        else if (qr <= mid)
            return _get(node->l, ql, qr);
        else
            return _get(node->l, ql, mid) + _get(node->r, mid + 1, qr);
    }

public:
    Node *root = nullptr;
    ll _size;

    funkysegtree(ll __size){
        root = new Node(0, __size);
        _size = __size;
    };

    void upd(ll x, ll val){
        _upd(root, x, val);
    }

    ll get(ll l, ll r){
        return _get(root, l, r);
    }
};