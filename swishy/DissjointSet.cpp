//lib
struct DissjointSet{
    vector<int> p;
    int cnt = 0;
 
    DissjointSet(){}
    DissjointSet(int n){
        cnt = n;
        p = vector<int>(n, -1);
    }
 
    int find(int n){
        return p[n] < 0 ? n : p[n] = find(p[n]); 
    }
 
    void merge(int u, int v){
        if ((u = find(u)) == (v = find(v)))
            return;
 
        cnt--;
        if (p[v] < p[u])
            swap(u, v);
 
        p[u] += p[v];
        p[v] = u;
    }
};
//lib