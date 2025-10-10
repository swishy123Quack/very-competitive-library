struct edge{
    int v;
    ll cost, capacity;
    edge* rv; 
    edge(int v, ll cost, ll capacity) : v(v), cost(cost), capacity(capacity){}
};
 
struct MCMF{
    vector<vector<edge*>> edg;
    vector<pair<int, edge*>> par;
    vector<ll> dis;
 
    MCMF(int n){
        edg = vector<vector<edge*>>(n);
    }
    void add_edge(int u, int v, ll capacity, ll cost){
        edge* e = new edge(v, cost, capacity);
        edge* re = new edge(u, -cost, 0);
 
        e->rv = re;
        re->rv = e;
 
        edg[u].push_back(e);
        edg[v].push_back(re);
    }
    void spfa(int start){
        int n = edg.size();
        auto inq = vec(n, 0);   
        dis = vec(n, inf);
        par = vector<pair<int, edge*>>(n, {-1, nullptr});
 
        queue<int> q;
        q.push(start);
        dis[start] = 0;
        
        while (q.size()){
            int u = q.front(); q.pop();
            inq[u] = 0;
 
            for (auto e : edg[u]){
                if (e->capacity > 0 && dis[e->v] > dis[u] + e->cost){
                    dis[e->v] = dis[u] + e->cost;
                    par[e->v] = {u, e};
 
                    if (!inq[e->v]){
                        inq[e->v] = 1;
                        q.push(e->v);
                    }
                }
            }
        }
    }   
    pl get(int start, int end, ll max_flow = inf){
        ll flow = 0, cost = 0;
        while (flow < max_flow){
            spfa(start);
            if (dis[end] == inf) break;
 
            ll f = max_flow - flow;
            int u = end;
 
            while (u != start){
                f = min(f, par[u].y->capacity);
                u = par[u].x;
            }
 
            flow += f;
            cost += f * dis[end];
 
            u = end;
            while (u != start){
                par[u].y->capacity -= f;
                par[u].y->rv->capacity += f;
                u = par[u].x;
            }
        }   
        if (flow == max_flow || max_flow == inf)
            return {flow, cost};
        else
            return {-1, -1}; 
    }
};