#include<bits/stdc++.h>
using namespace std;

int n,q;
int par[100005][21];
int st[100005],fin[100005],dep[100005];
vector<int> adj[100005],euler;
int bould[100005],mn[100005];
int root,tim = 0;

void pre_dfs(int u){
    mn[u] = u;
    vector<pair<int,int> > gg;
    for(auto v:adj[u]){
        pre_dfs(v);
        gg.push_back({mn[v],v});
        mn[u] = min(mn[u],mn[v]);
    }
    sort(gg.begin(),gg.end());
    adj[u].clear();
    for(auto x:gg){
        adj[u].push_back(x.second);
    }
}

void dfs(int u,int p,int d){
    st[u] = tim;
    dep[u] = d;
    for(auto v:adj[u]){
        if(v != p){
            dfs(v,u,d+1);
        }
    }
    fin[u] = tim++;
    // cout << u << " " << st[u] << " " << fin[u] << endl;
    euler.push_back(u);
}

signed main(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++){
        cin >> par[i][0];
        if(!par[i][0]){
            par[i][0] = i;
            root = i;
        }
        else{
            adj[par[i][0]].push_back(i);
        }
    }
    for(int j = 1; j <= 20; j ++){
        for(int i = 1; i <= n; i ++){
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    pre_dfs(root);
    dfs(root,root,0);
    set<int> s;
    for(int i = 0; i < n; i ++) s.insert(i);
    for(int i = 0; i < q; i++){
        int t; cin >> t;
        if(t == 1){
            int x; cin >> x;
            for(int j = 0; j < x-1; j ++){
                bould[(*s.begin())] = 1;
                s.erase(s.begin());
            }
            bould[(*s.begin())] = 1;
            cout << euler[(*s.begin())] << "\n";
            s.erase(s.begin());
        }
        else{
            int u; cin >> u;
            int u0 = u;
            for(int j = 19; j >= 0; j --){
                if(bould[fin[par[u][j]]]){
                    u = par[u][j];
                }
            }
            bould[fin[u]] = 0;
            s.insert(fin[u]);
            cout << dep[u0]-dep[u] << "\n";
        }
    }
}