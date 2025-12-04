typedef Point<ll> P;
void reorder_polygon(vector<P> & p){
    size_t pos = 0;
    for(size_t i = 1; i < p.size(); i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski(vector<P> p, vector<P> Q){
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while(i < p.size() - 2 || j < Q.size() - 2){
        result.push_back(p[i] + Q[j]);
        auto cross = (p[i + 1] - p[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < p.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}
