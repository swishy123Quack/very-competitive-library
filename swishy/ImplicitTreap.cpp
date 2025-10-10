typedef node* pnode;
struct ImplicitTreap{
public:
    pnode root;
    ImplicitTreap(){
        root = new node(-1, 0);
    }
    void insert(int i, ll val){
        pnode t1, t2;
        split(root, i + 1, 0, t1, t2);
        merge(t1, t1, new node(val));
        merge(root, t1, t2);
    }
    void erase(int i){
        _erase(root, i + 1, 0);
    }
    ll query(int l, int r){
        pnode t1, t2, t3;
        split(root, r + 2, 0, t2, t3);
        split(t2, l + 1, 0, t1, t2);

        ll res = t2->sum;
        merge(root, t1, t2);
        merge(root, root, t3);

        return res;
    }
    void update(int l, int r, ll val){
        pnode t1, t2, t3;
        split(root, r + 2, 0, t2, t3);
        split(t2, l + 1, 0, t1, t2);

        t2->add += val;
        merge(root, t1, t2);
        merge(root, root, t3);
    }
    void split(pnode t, int key, int add, pnode &l, pnode &r){
        if (!t){
            l = r = nullptr;
            return;
        }
        push(t);
        int impl_key = add + _cnt(t->l);
        if (key <= impl_key)
            split(t->l, key, add, l, t->l), r = t;
        else
            split(t->r, key, add + _cnt(t->l) + 1, t->r, r), l = t;
        upd(t);
    }
    
    void merge(pnode &t, pnode l, pnode r){
        push(l); push(r);
        if (!l || !r)
            t = l? l : r; 
        else if (l->prior > r->prior)
            merge(r->l, l, r->l), t = r;
        else
            merge(l->r, l->r, r), t = l;
        upd(t);
    }
private:
    void _erase(pnode &t, int key, int add){
        push(t);
        int impl_key = add + _cnt(t->l);
        if (impl_key == key){
            pnode it = t;
            merge(t, t->l, t->r);
            delete it;
        }
        else if (key < impl_key)
            _erase(t->l, key, add);
        else
            _erase(t->r, key, add + _cnt(t->l) + 1);
        upd(t);
    }
    void push(pnode t){
        if (!t) return;
        t->sum += t->add * (ll)_cnt(t);
        t->val += t->add;
        if (t->l) t->l->add += t->add;
        if (t->r) t->r->add += t->add;

        t->add = 0;
    }
    int _cnt(pnode t){
        if (!t) return 0;
        return t->cnt;
    }
    ll _sum(pnode t){
        if (!t) return 0;
        push(t);
        return t->sum;
    }
    void upd(pnode t){
        if (!t) return;
        t->sum = t->val + _sum(t->l) + _sum(t->r);
        t->cnt = _cnt(t->l) + _cnt(t->r) + 1;
    }
}; 