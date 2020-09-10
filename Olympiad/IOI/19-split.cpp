/*
Soln:
https://www.youtube.com/watch?v=5lBGTEbD9io&t=5940s
*/

#include "split.h"
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define pii pair<int,int>
#define F first
#define S second
using namespace std;
 
const int MX = 200005;
 
vi g[MX],adj[MX];
int n,m,par[MX],dep[MX],sz[MX],root;
pii A[MX];
 
bitset<MX> vis;
 
vi ans;

int comp;
int dsusz[2*MX],dsupar[2*MX];
 
void dfs(int u,int p,int d = 0){
	par[u] = p;
	vis[u] = 1;
	dep[u] = d;
	sz[u] = 1;
	for(auto v:g[u]){
		if(vis[v]) continue;
		adj[u].pb(v);
		adj[v].pb(u);
		dfs(v,u,d-1);
		sz[u] += sz[v];
	}
}

void assign(int u,int val){
	vis[u] = 1;
	if(A[val].F){
		ans[u] = A[val].S;
		A[val].F--;
	}
	else ans[u] = A[2].S;
	for(auto v:adj[u]){
		if(!vis[v]) assign(v,val);
	}
}

void assign_graph(int u,int val){
	vis[u] = 1;
	if(A[val].F){
		ans[u] = A[val].S;
		A[val].F--;
	}
	else ans[u] = A[2].S;
	for(auto v:g[u]){
		if(!vis[v]) assign_graph(v,val);
	}
}
 
void dsubuild(int u,int c){
	dsupar[u] = c;
	vis[u] = 1;
	for(auto v:adj[u]){
		if(!vis[v]) dsubuild(v,c);
	}
}

int findpar(int x){
	if(dsupar[x] == x) return x;
	return dsupar[x] = findpar(dsupar[x]);
}

vi find_split(int n, int a, int b, int c, vi p, vi q) {
	::n = n;
	m = p.size();
	A[0] = {a,1};
	A[1] = {b,2};
	A[2] = {c,3};
	sort(A,A+3);
	ans.resize(n);
	REP(i,m){
		g[p[i]].pb(q[i]);
		g[q[i]].pb(p[i]);
	}
	REP(i,2*n) dsupar[i] = i;

	REP(i,n) adj[i].clear();
	vis.reset();
	root = 0;
	dfs(root,root);

	vis.reset();
	REP(i,n){
		if(sz[i] >= A[0].F and n-sz[i] >= A[0].F){
			vis[i] = 1;
			if(sz[i] < n-sz[i]){
				assign(par[i],1);
				assign(i,0);
			}
			else{
				assign(par[i],0);
				assign(i,1);
			}
			return ans;
		}
	}
	REP(i,n){
		int mx = n-sz[i];
		for(auto v:adj[i]){
			if(v != par[i]){
				mx = max(mx,sz[v]);
			}
		}
		if(mx >= A[0].F) continue;
		comp = n;
		vis.reset();
		vis[i] = 1;
		for(auto v:adj[i]){
			if(v == par[i]) dsusz[comp] = n-sz[i];
			else dsusz[comp] = sz[v];
			dsubuild(v,comp);
			comp++;
		}
		vis.reset();
		int head = -1;
		REP(j,m){
			if(p[j] == i or q[j] == i) continue;
			int u = findpar(p[j]);
			int v = findpar(q[j]);
			if(u == v) continue;
			if(dsusz[u] > dsusz[v]) swap(u,v);
			dsusz[v] += dsusz[u];
			dsupar[u] = v;
			if(dsusz[v] >= A[0].F){
				head = v;
				break;
			}
		}
		if(head == -1) return vi(n,0);
		vi v1,v2;
		REP(j,n){
			if(j == i or findpar(j) != head) v2.pb(j);
			else v1.pb(j);
		}
		if(dsusz[head] >= A[1].F){
			vis.reset();
			for(auto x:v2) vis[x] = 1;
			assign_graph(v1[0],1);
			vis.reset();
			for(auto x:v1) vis[x] = 1;
			assign_graph(v2[0],0);
		}
		else{
			vis.reset();
			for(auto x:v2) vis[x] = 1;
			assign_graph(v1[0],0);
			vis.reset();
			for(auto x:v1) vis[x] = 1;
			assign_graph(v2[0],1);
		}
		return ans;
	}
}