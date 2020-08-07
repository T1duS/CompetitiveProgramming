/*
Soln:
Compress SCCs to form dag
Now we have to find 2 nodes u,v
such that there is an edge v->u
So we go from comp[1] to comp[u] to comp[v] to comp[1]
Do dp precomputation
*/

#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define all(v) v.begin(),v.end()
#define remax(a,b) a = max(a,(int)(b))

const int MX = 100005;
const int INF = 1e7;

int n,m;
vi g[MX],r[MX];
vi gg[MX];
bitset<MX> vis;
vi vv;

vi adj[MX],rev[MX];

int cmp = 0;
int comp[MX];
int dp1[MX],dp2[MX];

void dfs1(int u){
	vis[u] = 1;
	for(auto v:g[u]){
		if(!vis[v]) dfs1(v);
	}
	vv.pb(u);
}

void dfs2(int u){
	vis[u] = 1;
	comp[u] = cmp;
	gg[cmp].pb(u);
	for(auto v:r[u]){
		if(!vis[v]) dfs2(v);
	}
}

int dfs3(int u){
	if(dp1[u] != -1) return dp1[u];
	int mx = -INF;
	for(auto v:rev[u]){
		remax(mx,dfs3(v));
	}
	// cout << u << " -- " << mx << endl;
	mx += gg[u].size();
	return dp1[u] = mx;
}

int dfs4(int u){
	if(dp2[u] != -1) return dp2[u];
	int mx = -INF;
	for(auto v:adj[u]){
		remax(mx,dfs4(v));
	}
	// cout << u << " -- " << mx << endl;
	mx += gg[u].size();
	return dp2[u] = mx;
}

signed main(){
	freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);
	cin >> n >> m;
	REP(i,m){
		int u,v; cin >> u >> v;
		g[u].pb(v);
		r[v].pb(u);
	}
	FOR(i,1,n+1){
		if(!vis[i]){
			dfs1(i);
		}
	}
	reverse(all(vv));
	vis.reset();
	for(auto i:vv){
		// cout << i << " " << vis[i] << endl;
		if(!vis[i]){
			dfs2(i);
			cmp++;
		}
	}
	FOR(i,1,n+1){
		for(auto u:g[i]){
			if(comp[i] != comp[u]){
				adj[comp[i]].pb(comp[u]);
				rev[comp[u]].pb(comp[i]);
			}
		}
		// cout << i << " " << comp[i] << endl;
	}
	// REP(i,cmp){
	// 	for(auto j:rev[i]) cout << j << "->" << i << "\n";
	// }
	REP(i,n+1){
		dp1[i] = -1;
		dp2[i] = -1;
	}
	dp1[comp[1]] = gg[comp[1]].size();
	dp2[comp[1]] = 0;
	int ans = dp1[comp[1]];
	REP(i,cmp){
		dfs3(i);
		dfs4(i);
	}
	REP(i,cmp){	
		for(auto u:rev[i]){
			remax(ans,dp1[i]+dp2[u]);
		}
	}
	// REP(i,cmp){
	// 	cout << i << ": " << dp1[i] << endl;
	// }
	cout << ans << "\n";
}