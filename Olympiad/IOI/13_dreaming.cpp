#include "dreaming.h"
#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define all(v) v.begin(),v.end()

const int MAXN = 100005;

vector<pii> adj[MAXN];
int dp[MAXN],dp_par[MAXN];

bitset<MAXN> vis;
vector<int> cc;

void dfs(int u,int p){
	cc.pb(u);
	vis[u] = 1;
	dp[u] = 0;
	for(auto v:adj[u]){
		if(v.F != p){
			dfs(v.F,u);
			dp[u] = max(dp[u],v.S+dp[v.F]);
		}
	}
}

void dfs_par(int u,int p){
	int mx1 = dp_par[u],mx2 = 0;
	for(auto v:adj[u]){
		if(v.F != p){
			int val = dp[v.F]+v.S;
			if(val > mx1){
				mx2 = mx1;
				mx1 = val;
			}
			else if(val > mx2) mx2 = val;
		}
	}
	for(auto v:adj[u]){
		if(v.F == p) continue;
		
		if(dp[v.F]+v.S == mx1) dp_par[v.F] = mx2;
		else dp_par[v.F] = mx1;
		
		dp_par[v.F] += v.S;
		dfs_par(v.F,u);
	}
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]){
    for(int i = 0; i < M; i ++){
    	adj[A[i]].pb({B[i],T[i]});
    	adj[B[i]].pb({A[i],T[i]});
    }
    vector<int> gg;
    vis.reset();
    int diam = 0;
    for(int i = 0; i < N; i ++){
    	if(vis[i]) continue;
    	cc.clear();
    	dfs(i,i);
    	dfs_par(i,i);
    	int mn = max(dp[i],dp_par[i]);
    	for(auto x:cc){
    		mn = min(mn,max(dp[x],dp_par[x]));
    		diam = max(diam,max(dp[x],dp_par[x]));
    	}
    	gg.pb(mn);
    }
    // for(int i = 0; i < N; i++){
    // 	cout << i << " " << max(dp[i],dp_par[i]) <<  endl;
    // }
	// for(auto x:gg) cout << x << " "; cout << endl;
    sort(all(gg));
    for(int i = 0; i < (int)(gg.size())-1; i++) gg[i] += L;
    sort(all(gg));
	reverse(all(gg));
	if((int)gg.size() == 1) return max(diam,gg[0]);
	else return max(diam,gg[0]+gg[1]);
}
