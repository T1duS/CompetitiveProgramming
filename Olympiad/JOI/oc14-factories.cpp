#include "factories.h"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pii pair<int,int>
#define F first
#define S second
#define vi vector<int>
#define pb push_back
#define runtime() ((double)(clock())/CLOCKS_PER_SEC)

int n,centroid;
const int MAXN = 500005;
const ll INF = 1e16;

int par[MAXN][21],cenpar[MAXN];
int dep[MAXN],sz[MAXN];
vector<pii> adj[MAXN];
bitset<MAXN> vis;

vi g[MAXN];

ll mnd[MAXN];
ll cendist[MAXN][21];
int cendep[MAXN];

void dfs0(int u){
	for(auto v:adj[u]){
		if(v.F != par[u][0]){
			par[v.F][0] = u;
			dep[v.F] = dep[u]+1;
			dfs0(v.F);
		}
	}
}

void dfs_sz(int u,int p){
	sz[u] = 1;
	for(auto v:adj[u]){
		if(v.F != p and vis[v.F] == 0){
			dfs_sz(v.F,u);
			sz[u] += sz[v.F];
		}
	}
}

int find_centroid(int u,int p,int tot){
	for(auto v:adj[u]){
		if(v.F == p or vis[v.F]) continue;
		if(sz[v.F] > tot/2) return find_centroid(v.F,u,tot); 
	}
	return u;
}

void dfs1(int u,int p,ll dd,int st){
	cendist[u][cendep[u]-cendep[st]] = dd;
	for(auto v:adj[u]){
		if(v.F != p and vis[v.F] == 0){
			dfs1(v.F,u,dd+v.S,st);
		}
	}
}

void centroid_decomposition(int u,int p){
	dfs_sz(u,u);
	int cen = find_centroid(u,p,sz[u]);
	if(p == -1){
		centroid = cen;
		cendep[cen] = 0;
	}
	else{
		g[p].pb(cen);
		cendep[cen] = cendep[p]+1;
	}
	cenpar[cen] = p;
	vis[cen] = 1;
	for(auto v:adj[cen]){
		if(!vis[v.F]) centroid_decomposition(v.F,cen);
	}
}

void calc_dist(int u){
	dfs1(u,u,0,u);
	vis[u] = 1;
	for(auto v:g[u]) calc_dist(v); 
}

void Init(int N, int A[], int B[], int D[]){
	n = N;
	REP(i,n-1){
		adj[A[i]].pb({B[i],D[i]});
		adj[B[i]].pb({A[i],D[i]});
	}
	par[0][0] = 0;
	dep[0] = 0;
	dfs0(0);
	FOR(j,1,21){
		REP(i,n){
			par[i][j] = par[par[i][j-1]][j-1];
		}
	}
	centroid_decomposition(0,-1);
	vis.reset();
	calc_dist(centroid);
	REP(i,n+1) mnd[i] = INF;
}

void upd(int u,int type){
	int cur = u;
	int cnt = 0;
	while(cur != -1){
		if(type == 0){
			mnd[cur] = min(mnd[cur],cendist[u][cnt]);
		}
		else mnd[cur] = INF;
		cur = cenpar[cur];
		cnt++;
	}
}

ll quer(int u){
	ll res = INF;
	int cur = u;
	int cnt = 0;
	while(cur != -1){
		res = min(res,cendist[u][cnt]+mnd[cur]);
		cur = cenpar[cur];
		cnt ++;
	}
	return res;
}

ll Query(int S, int X[], int T, int Y[]) {
	REP(i,S) upd(X[i],0);
	ll ans = INF;
	REP(i,T) ans = min(ans,quer(Y[i]));
	REP(i,S) upd(X[i],1);
	return ans;
}
