/*
Soln:
http://blog.brucemerry.org.za/2012/09/ioi-2012-day-2-analysis.html
*/

#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define pb push_back

const int MAXN = 100005;
const int MOD = 1000000000;

long long ans = 0;

int n;
pii a[MAXN];
set<int> adj[MAXN];
long long sz[MAXN],dist[MAXN],dp[MAXN];

int comp;

map<pair<int,int>,int> C;

void dfs(int u,int p){
	for(auto v:adj[u]){
		if(v != p){
			dfs(v,u);
			dp[v] += sz[v];
			sz[u] += sz[v];
			dp[u] += dp[v];
		}
	}
	for(auto v:adj[u]){
		if(v != p){
			ans += dp[v]*(sz[u]-sz[v]);
		}
	}
}

void solve(){
	C.clear();
	for(int i = 0; i < MAXN; i ++){
		adj[i].clear();
		sz[i] = 0;
		dp[i] = 0;
	}
	comp = 0;
	sort(a,a+n);
	C[a[0]] = 0;
	int last = 0;
	for(int i = 1; i < n; i++){
		if(a[i].F == a[i-1].F and a[i].S == a[i-1].S+1){
			C[a[i]] = comp;
		}
		else{
			sz[comp] = i-last;

			comp++;
			last = i;
			C[a[i]] = comp;
		}
	}
	sz[comp] = n-last;

	for(int i = 0; i < n; i++){
		if(C.find({a[i].F-1,a[i].S}) != C.end()){
			adj[C[{a[i].F-1,a[i].S}]].insert(C[{a[i].F,a[i].S}]);
			adj[C[{a[i].F,a[i].S}]].insert(C[{a[i].F-1,a[i].S}]);
		}
	}
	dfs(0,0);
}

int DistanceSum(int N, int *X, int *Y) {
	n = N;
	for(int i = 0; i < n; i ++){
		a[i] = {X[i],Y[i]};
	}
	solve();
	for(int i = 0; i < n; i ++){
		a[i] = {Y[i],X[i]};
	}
	solve();
	return ans%MOD;
}
