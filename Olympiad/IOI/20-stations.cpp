#include<bits/stdc++.h>
#include "stations.h"

using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)

const int MAXN = 1005;

int st[MAXN],fin[MAXN],dep[MAXN],tim = 0;
vi adj[MAXN];

void dfs(int u,int p,int d){
	if(d%2 == 0) st[u] = tim++;
	dep[u] = d;
	for(auto v:adj[u]){
		if(v != p) dfs(v,u,d+1);
	}
	if(d%2 == 1) fin[u] = tim++;
}

vi label(int n, int k, vi u, vi v){
	tim = 0;
	REP(i,n) adj[i].clear();
	vi labels(n);
	REP(i,n-1){
		adj[u[i]].pb(v[i]);
		adj[v[i]].pb(u[i]);
	}
	dfs(0,0,0);
	for (int i = 0; i < n; i++){
		if(dep[i]%2 == 0) labels[i] = st[i];
		else labels[i] = fin[i];
	}
	return labels;
}

int find_next_station(int s, int t, vi c){
	if(c.size() == 1) return c[0];
	for(auto x:c){
		if(x == t) return x;
	}
	sort(c.begin(),c.end());
	if(s < c[0]){
		if(t < s) return c.back();
		for(auto x:c){
			if(t < x) return x;
		}
		return c.back();
	}
	else{
		reverse(c.begin(),c.end());
		if(t > s) return c.back();
		for(auto x:c){
			if(t > x) return x;
		}
		return c.back();
	}
}
