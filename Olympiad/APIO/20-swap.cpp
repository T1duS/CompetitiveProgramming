/*
Soln:
Basically we need to find some 3-degree vertex or a cycle
and we want the minimum value of 
-> max(path from (x,y), path from x to the vertex,(3rd shortest edge or cycle edge))
First compute mst then use dp on tree
dp[u] = best such vertex in subtree of u
dp_par[u] = best such vertex outside subtree of u
*/
#include "swap.h"
#include <bits/stdc++.h>
using namespace std;
 
typedef long double LD;
typedef long long ll;
// #define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

const int MAXN = 100005;
const int SQRTN = 1003;
const int LOGN = 22;
const double PI=acos(-1);
 
#ifdef int
const int INF=1e16;
#else
const int INF=1e9+5;
#endif
 
const int MOD = 1000000007;
const int FMOD = 998244353;
const double eps = 1e-9;


int n,m;
vpii adj[MAXN];
vpii extra[MAXN];
vector<pair<int,pii> > edges;

int dsusz[MAXN],dsupar[MAXN];

int find(int x){
	if(dsupar[x] == x) return x;
	return dsupar[x] = find(dsupar[x]);
}

void merge(int x,int y,int w){
	int x0 = find(x);
	int y0 = find(y);
	if(x0 == y0){
		extra[x].pb({y,w});
		extra[y].pb({x,w});
		return;
	}
	adj[x].pb({y,w});
	adj[y].pb({x,w});

	if(dsusz[x0] > dsusz[y0]) swap(x0,y0);
	dsupar[x0] = y0;
	dsusz[y0] += dsusz[x0]; 
}

pii par[MAXN][21];
int dep[MAXN],st[MAXN],fin[MAXN];
int dp[MAXN],dp_par[MAXN],val[MAXN];
int tim = 0;

void dfs0(int u,int p,int w,int d){
	val[u] = INF;
	if(extra[u].size()) remin(val[u],extra[u][0].S);
	if(adj[u].size() >= 3) remin(val[u],adj[u][2].S);
	dp[u] = val[u];
	dp_par[u] = val[u];
	st[u] = tim++;
	par[u][0] = {p,w};
	dep[u] = d;
	for(auto v:adj[u]){
		if(v.F != p){
			dfs0(v.F,u,v.S,d+1);
			remin(dp[u],max(v.S,dp[v.F]));
		}
	}
	fin[u] = tim;
}

void dfs_par(int u){
	vpii gg;
	for(auto v:adj[u]){
		if(v.F == par[u][0].F) continue;
		remin(dp_par[v.F],max(v.S,dp_par[u]));
		gg.pb({max(v.S,dp[v.F]),v.S});
	}
	sort(all(gg));
	for(auto v:adj[u]){
		if(v.F == par[u][0].F) continue;
		if(v.F == gg[0].S){
			if(gg.size() != 1){
				remin(dp_par[v.F],max(v.S,gg[1].F));
			}
		}
		else{
			remin(dp_par[v.F],max(v.S,gg[0].F));
		}
		dfs_par(v.F);
	}
}

void init(int N, int M,vi U, vi V, vi W) {
	n = N;
	m = M;
	REP(i,m) edges.pb({W[i],{U[i],V[i]}});
	REP(i,N){
		dsusz[i] = 1;
		dsupar[i] = i;
	}
	sort(all(edges));
	REP(i,m) merge(edges[i].S.F,edges[i].S.S,edges[i].F);
	tim = 0;
	dfs0(1,1,0,0);
	dfs_par(1);
	FOR(j,1,21){
		REP(i,n){
			par[i][j].F = par[par[i][j-1].F][j-1].F;
			par[i][j].S = max(par[i][j-1].S,par[par[i][j-1].F][j-1].S);
		}
	}
}

int lca(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	int res = 0;
	FORD(j,20,0){
		if(dep[u]-(1<<j) >= dep[v]){
			remax(res,par[u][j].S);
			u = par[u][j].F;
		}
	}
	if(u == v) return res;
	FORD(j,20,0){
		if(par[u][j].F != par[v][j].F){
			remax(res,par[u][j].S);
			remax(res,par[v][j].S);
			u = par[u][j].F;
			v = par[v][j].F;
		}
	}
	remax(res,par[u][0].S);
	remax(res,par[v][0].S);
	return res;
}

int getMinimumFuelCapacity(int x, int y){
	int ans = lca(x,y);
	remax(ans,min(dp[x],dp_par[x]));
	if(ans >= INF) return -1;
	return ans;	
}
