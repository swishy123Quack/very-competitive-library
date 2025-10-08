struct node{
    int p[26];
    int link;
 
    node(){
        for (int i = 0; i < 26; i++)
            p[i] = -1;
    }
};
 
struct Trie{
    int indx = 1;
    int dp[def][26];
    vector<node> p;
 
    Trie(){
        p.push_back(node());
    }
 
    int add(string s){
        ll crr = 0;
        for (int i = 0; i < s.size(); i++){
            int c = s[i] - 'a';
            if (p[crr].p[c] == -1){
                p[crr].p[c] = indx++;
                p.push_back(node());
            }
 
            crr = p[crr].p[c];
        }      
 
        return crr;  
    }
 
    void buildsuffix(){
        int n = p.size();
 
        queue<int> q;
        q.push(0);
 
        p[0].link = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < 26; j++)
                dp[i][j] = 0;
 
        while (q.size()){
            int u = q.front();
            q.pop();
 
            for (int i = 0; i < 26; i++){
                int v = p[u].p[i];
                if (v != -1){
                    dp[u][i] = v;
                    p[v].link = (u == 0)? 0 : dp[p[u].link][i];
                    q.push(v);
                }
 
                else    
                    dp[u][i] = dp[p[u].link][i];
            }
        }
    }
};