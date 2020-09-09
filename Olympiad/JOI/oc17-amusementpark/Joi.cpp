/*
Soln:
https://ivaniscoding.wordpress.com/2018/08/29/communication-6-amusement-park/
*/

#include "Joi.h"
#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pb push_back
#define all(v) v.begin(),v.end()
#define mii map<int,int>
#define F first
#define S second

static const int MX = 10005;

static vi g[MX],adj[MX];
static int par[MX],dep[MX];

static bitset<MX> vis;
static int n,ind[MX];

static vi subgraph[MX];

static vi cc;

static void findtree(int u){
	if(cc.size() < 60){
		ind[u] = cc.size();
		cc.pb(u);
	}
	vis[u] = 1;
	for(auto v:g[u]){
		if(!vis[v]){
			adj[u].pb(v);
			par[v] = u;
			dep[v] = 1+dep[u];
			findtree(v);
		}
	}
}

static void dfs(int u){
	if(ind[u] == -1){
		mii deg;
		for(auto x:subgraph[par[u]]){
			for(auto y:subgraph[par[u]]){
				if(binary_search(all(adj[x]),y)){
					deg[x]++;
					deg[y]++;
				}
			}
		}
		for(auto x:deg){
			if(x.S == 1 and x.F != par[u]){
				ind[u] = ind[x.F];
				for(auto y:subgraph[par[u]]){
					if(x.F != y) subgraph[u].pb(y);
				}
				subgraph[u].pb(u);
				break;
			}
		}
	}
	for(auto v:adj[u]){
		dfs(v);
	}
}

void Joi(int N, int M, int A[], int B[], long long X, int T){
	n = N;
	REP(i,M){
		g[A[i]].pb(B[i]);
		g[B[i]].pb(A[i]);
	}
	REP(i,n+2) ind[i] = -1;
	par[0] = 0;
	dep[0] = 0;
	findtree(0);
	for(auto x:cc) subgraph[x] = cc;
	REP(i,n) sort(all(adj[i]));
	dfs(0);
	REP(i,n) MessageBoard(i,((X>>ind[i])&1));
}
