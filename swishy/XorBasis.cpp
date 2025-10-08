struct Basis{
    vector<pi> d;
    int siz = 0;

    Basis(){
        d = vector<pi>(21, {-1, -1});
    }
    void add(int x, int pos){
        for (int i = 20; i >= 0; i--){
            if ((x & (1 << i)) != 0){
                if (d[i].x != -1)
                    x ^= d[i].x;
                else{
                    siz++;
                    d[i] = {x, pos};
                    break;
                }
            }
        }
    }
    //count numbers in set larger than x
    int count(int x){
        int res = 0, val = 0, left = siz;
        for (int i = 20; i >= 0; i--){
            if (d[i].x == -1){
                if ((val & (1 << i)) != (x & (1 << i)))
                    break;
                continue;
            }
            left--;
            if ((x & (1 << i)) != 0){
                res += 1 << left;
                if ((val & (1 << i)) == 0)
                    val ^= d[i].x;
            }
            else{
                if ((val & (1 << i)) != 0)
                    val ^= d[i].x;
            }
        }
        res = (1 << siz) - res;
        if (x == val)
            res--;
        return res;
    }
    //find k-th largest number in set
    int getk(int k){
        k = (1 << siz) - k;
        int res = 0, left = siz;
        for (int i = 20; i >= 0; i--){
            if (d[i].x == -1)
                continue;
            left--;
            if ((k & (1 << left)) != 0){
                if ((res & (1 << i)) == 0)
                    res ^= d[i].x;
            }
            else{
                if ((res & (1 << i)) != 0)
                    res ^= d[i].x;
            }
        }
        return res;
    }
    vector<int> total(){
        vector<int> res;
        
        for (int i = 0; i < (1 << siz); i++){
            int crr = 0, val = 0;
            for (int j = 0; j <= 20; j++){
                if (d[j].x == -1)
                    continue;
                if ((i & (1 << crr)) != 0)
                    val ^= d[j].x;
                crr++;
            }
            res.push_back(val);
        }
        sort(all(res));
        return res;
    }
};
