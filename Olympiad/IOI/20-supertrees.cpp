#include "supertrees.h"
#include <bits/stdc++.h>
using namespace std;
 
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
 
const int MX = 1005;
 
int n;
int par[MX];
int sz[MX];
 
int find(int x){
	if(par[x] == x) return x;
	return par[x] = find(par[x]);
}
 
void merge(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x,y);
	par[y] = x;
	sz[x] += sz[y];
}
 
bitset<MX> vis;
 
int construct(vvi p) {
	n = p.size();
	vvi ans(n,vi(n,0));
	REP(i,n){
		par[i] = i;
		sz[i] = 1;
	}
	REP(i,n){
		REP(j,n){
			if(p[i][j] == 3) return 0;
			if(p[i][j]) merge(i,j);
		}
	}
	REP(i,n){
		REP(j,n){
			if(!p[i][j]){
				if(find(i) == find(j)) return 0;
			}
		}
	}
	REP(i,n) par[i] = find(i);
	REP(i,n){
		if(vis[i]) continue;
		vi cc;
		REP(j,n){
			if((!vis[j]) and par[i] == par[j]){
				vis[j] = 1;
				cc.pb(j);
			}
		}
		for(auto x:cc){
			vis[x] = 0;
			par[x] = x;
			sz[x] = 1;
		}
		vi corners;
		for(auto x:cc){
			for(auto y:cc){
				if(p[x][y] == 1){
					merge(x,y);
				}
			}
		}
		for(auto x:cc) par[x] = find(x);
		for(auto x:cc){
			if(vis[x]) continue;
			vi cc2;
			corners.pb(x);
			for(auto y:cc){
				if((!vis[y]) and par[x] == par[y]){
					vis[y] = 1;
					cc2.pb(y);
				}
			}
			REP(j,(int)cc2.size()-1){
				ans[cc2[j]][cc2[j+1]] = 1;
				ans[cc2[j+1]][cc2[j]] = 1;
			}
		}
		REP(j,(int)corners.size()-1){
			ans[corners[j]][corners[j+1]] = 1;
			ans[corners[j+1]][corners[j]] = 1;
		}
		if(corners.size() == 1) continue;
		if(corners.size() == 2) return 0;
		ans[corners[0]][corners.back()] = 1;
		ans[corners.back()][corners[0]] = 1;
	}
	build(ans);
	return 1;
}