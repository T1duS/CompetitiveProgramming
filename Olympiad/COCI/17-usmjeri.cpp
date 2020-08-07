#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define all(v) v.begin(),v.end()
#define remax(a,b) a = max(a,(int)(b))
#define pii pair<int,int>
#define F first
#define S second

const int MX = 300005;

int n,m;
vi adj[MX];
int par[MX][21],dep[MX];
bool flag = 1;


int sz[MX],root[MX],dist[MX],nxt[MX];

pii find(int u){
    if(root[u] == u) return {root[u],dist[u]};
    pii v = find(root[u]);
    root[u] = v.F;
    dist[u] = (dist[u]+v.S)%2;
    return {root[u],dist[u]};
}

void merge(int u,int v,int w){
    pii u1 = find(u);
    pii v1 = find(v);
    if(u1.F == v1.F){
        if((u1.S+v1.S+w)%2) flag = 0;
        return;
    }
    if(sz[u1.F] < sz[v1.F]) swap(u1,v1);
    root[v1.F] = u1.F;
    dist[v1.F] = (u1.S+v1.S+w)%2;
    sz[u1.F] += sz[v1.F];
}

void dfs(int u,int p,int d){
    par[u][0] = p;
    dep[u] = d;
    for(auto v:adj[u]){
        if(v != p) dfs(v,u,d+1);
    }
}

int lca(int u,int v){
    if(dep[u] > dep[v]) swap(u,v);
    for(int j = 20; j >= 0; j --){
        if(dep[v]-(1<<j) >= dep[u]) v = par[v][j];
    }
    if(u == v) return u;
    for(int j = 20; j >= 0; j --){
        if(par[u][j] != par[v][j]){
            u = par[u][j];
            v = par[v][j];
        }
    }
    return par[u][0];
}

signed main(){
    cin >> n >> m;
    REP(i,n-1){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,1,0);
    FOR(j,1,21){
        FOR(i,1,n+1) par[i][j] = par[par[i][j-1]][j-1];
    }
    FOR(i,1,n+1){
        sz[i] = 1;
        root[i] = i;
        dist[i] = 0;
        nxt[i] = par[i][0];
    }
    REP(i,m){
        int u,v; cin >> u >> v;
        if(u == v) continue;
        if(dep[u] > dep[v]) swap(u,v);
        int l = lca(u,v);
        if(l != u) merge(u,v,1);
        vi gg;
        gg.clear();
        while(dep[u] > dep[l]+1){
            gg.pb(u);
            merge(u,par[u][0],0);
            u = nxt[u];
        }
        for(auto x:gg){
            if(dep[nxt[x]] > dep[u]) nxt[x] = u;
        }
        swap(u,v);
        gg.clear();
        while(dep[u] > dep[l]+1){
            gg.pb(u);
            merge(u,par[u][0],0);
            u = nxt[u];
        }
        for(auto x:gg){
            if(dep[nxt[x]] > dep[u]) nxt[x] = u;
        }
        if(!flag){
            cout << "0\n";
            return 0;
        }
    }
    set<int> s;
    FOR(i,2,n+1) s.insert(find(i).F);
    int ans = 1;
    REP(i,(int)s.size()){
        ans = (ans*2)%1000000007;
    }
    cout << ans << "\n";
}