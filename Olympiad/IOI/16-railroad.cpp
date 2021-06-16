#include "railroad.h"
#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define mii unordered_map<int,int>
#define SZ(v) (int)v.size()
 
const int MX = 200005;
 
int n;
mii flux;
mii par;
 
int find(int u){
	if(par[u] == u) return u;
	return par[u] = find(par[u]);
}
 
void merge(int u,int v){
	u = find(u);
	v = find(v);
	if(rand()%2) swap(u,v);
	par[u] = v;
}
 
ll plan_roller_coaster(vi s, vi t){
	s.pb(1000000000);
	t.pb(1);
    n = SZ(s);
    REP(i,n){
    	par[s[i]] = s[i];
    	par[t[i]] = t[i];
    }
    REP(i,n){
    	flux[s[i]]++;
    	flux[t[i]]--;
    	merge(s[i],t[i]);
    }
    vector<pii> gg;
    for(auto x:flux){
    	gg.pb(x);
    }
    sort(gg.begin(),gg.end());
    ll ans = 0,cur = 0;
    vector<pair<int,pii> > edges;
    REP(i,SZ(gg)-1){
    	cur += gg[i].S;
    	if(cur < 0){
    		merge(gg[i].F,gg[i+1].F);
    	}
    	else if(cur == 0){
    		edges.pb({gg[i+1].F-gg[i].F,{gg[i].F,gg[i+1].F}});
    	}
    	else{
    		ans += cur*(gg[i+1].F-gg[i].F);
    		merge(gg[i].F,gg[i+1].F);
    	}
    }
    sort(edges.begin(),edges.end());
    for(auto x:edges){
    	if(find(x.S.F) != find(x.S.S)){
    		ans += x.F;
    		merge(x.S.F,x.S.S);
    	}
    }
    return ans;
}