#include<bits/stdc++.h>
#include "simurgh.h"
using namespace std;

#define vi vector<int>
#define pii pair<int,int>
#define vpii vector<pii>
#define F first
#define S second
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)

const int MX = 505;

int N;
vpii adj[MX];
vpii edges;
vi T;
vi ans;
int status[MX*MX];
bitset<MX> vis;
int dep[MX];
pii low[MX],par[MX];

void dfs(int u,int d){
	vis[u] = 1;
	dep[u] = d;
	for(auto v:adj[u]){
		if(vis[v.F] and dep[v.F] > d){
			low[u] = min(low[u],low[v.F]);
		}
		else if(vis[v.F]){
			low[u] = min(low[u],{dep[v.F],v.S});
		}
		else{
			T.pb(v.S);
			par[v.F] = {u,v.S};
			low[v.F] = {d,v.S};
			dfs(v.F,d+1);
		}
	}
}

int dsu_par[MX],dsu_rank[MX];

int find(int x){
	if(dsu_par[x] == x) return dsu_par[x];
	return dsu_par[x] = find(dsu_par[x]);
}

void merge(int u,int v){
	u = find(u);
	v = find(v);
	if(dsu_rank[u] < dsu_rank[v]) swap(u,v);
	dsu_par[v] = u;
	dsu_rank[u]++;
}

int count(vi gg){
	FOR(i,1,N+1){
		dsu_par[i] = i;
		dsu_rank[i] = 1;
	}
	for(auto x:gg) merge(edges[x].F,edges[x].S);
	int precount = 0;
	for(auto x:T){
		if(find(edges[x].F) != find(edges[x].S)){
			merge(edges[x].F,edges[x].S);
			gg.pb(x);
			precount += status[x];
		}
	}
	return count_common_roads(gg)-precount;
}

void solve(vi gg,int k){
	if(k == 0) return;
	if(gg.size() == k){
		for(auto x:gg){
			status[x] = 1;
		}
		return;
	}
	vi gg1,gg2;
	REP(i,gg.size()){
		if(i < gg.size()/2) gg1.pb(gg[i]);
		else gg2.pb(gg[i]);
	}
	int c = count(gg1);
	solve(gg1,c);
	solve(gg2,k-c);
}

vi find_roads(int n, vi u, vi v) {
	N = n;
	int m = u.size();
	REP(i,m){
		u[i]++;
		v[i]++;
		adj[u[i]].pb({v[i],i});
		adj[v[i]].pb({u[i],i});
		edges.pb({u[i],v[i]});
	}
	vis.reset();
	par[1] = {1,-1};
	low[1] = {0,-1};
	dfs(1,0);
	sort(T.begin(),T.end());
	REP(i,m) status[i] = -1;
	int basic = count_common_roads(T);
	FOR(i,1,n+1){
		if(low[i].S != -1 and (!binary_search(T.begin(),T.end(),low[i].S))){
			int u = edges[low[i].S].F;
			int v = edges[low[i].S].S; 
			if(dep[u] < dep[v]) swap(u,v);
			int cur = u;
			vi known;
			vi unknown;
			while(cur != v){
				if(status[par[cur].S] == -1) unknown.pb(par[cur].S);
				else known.pb(par[cur].S);
				cur = par[cur].F;
			}
			if(unknown.empty()) continue;
			if(known.empty()){
				vpii bruh;
				int mn = basic,mx = basic;
				for(auto y:unknown){
					vi gg;
					gg.pb(low[i].S);
					for(auto x:T){
						if(x != y) gg.pb(x);
					}
					bruh.pb({y,count_common_roads(gg)});
					mn = min(mn,bruh.back().S);
					mx = max(mx,bruh.back().S);
				}
				if(mn == mx){
					for(auto y:unknown) status[y] = 0;
				}
				else{
					for(auto y:bruh){
						if(y.S == mn) status[y.F] = 1;
						else status[y.F] = 0;
					}
				}
			}
			else{
				vi gg;
				gg.pb(low[i].S);
				for(auto x:T){
					if(x != known[0]) gg.pb(x);
				}
				int roy = count_common_roads(gg)-(basic-status[known[0]]);
				for(auto y:unknown){
					gg.clear();
					gg.pb(low[i].S);
					for(auto x:T){
						if(x != y) gg.pb(x);
					}
					status[y] = basic-count_common_roads(gg)+roy;
				}
			}
		}
	}
	for(auto x:T){
		if(status[x] == -1) status[x] = 1;
	}
	FOR(i,1,n+1){
		vi gg;
		for(auto x:adj[i]){
			if(x.F > i) gg.pb(x.S);
		}
		solve(gg,count(gg));
	}
	REP(i,m){
		if(status[i] == 1){
			ans.pb(i);
		}
	}
	return ans;
}

