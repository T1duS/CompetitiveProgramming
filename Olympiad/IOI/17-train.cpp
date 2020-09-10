/*
Soln:
http://ioi2017.org/tasks/editorial/train.pdf
*/

#include "train.h"
#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)

const int MAXN = 5005;

int n,m;
int outdeg[MAXN];
vi adj[MAXN],rev[MAXN];
vi U,V;
vi ans;

vi charging,own;

vi f(vi tot,vi sub,int type){
	for(auto x:tot){
		outdeg[x] = adj[x].size();
		if(own[x] == type) outdeg[x] = 1;
	}
	queue<int> q;
	for(auto x:sub){
		outdeg[x] = 0;
		q.push(x);
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(auto v:rev[u]){
			outdeg[v]--;
			if(!outdeg[v]){
				sub.pb(v);
				q.push(v);
			}
		}
	}
	return sub;
}

void solve(vi gg){
	bitset<MAXN> w;
	vi ch,win,lose,nwin,nlose;
	for(auto x:gg){
		w[x] = 1;
		if(charging[x]) ch.pb(x);
		rev[x].clear();
		adj[x].clear();
	}
	REP(i,m){
		if(w[U[i]] and w[V[i]]){
			adj[U[i]].pb(V[i]);
			rev[V[i]].pb(U[i]);
		}
	}
	win = f(gg,ch,1);

	if(win.size() == gg.size()){
		for(auto x:gg) ans[x] = 1;
		return;
	}
	w.reset();
	for(auto x:win) w[x] = 1;
	for(auto x:gg){
		if(!w[x]) nwin.pb(x);
	}
	lose = f(gg,nwin,0);
	w.reset();
	for(auto x:lose){
		w[x] = 1;
		ans[x] = 0;
	}
	for(auto x:gg){
		if(!w[x]) nlose.pb(x);
	}
	solve(nlose);
}

vi who_wins(vi a, vi r, vi u, vi v){
	U = u;
	V = v;
	charging = r;
	own = a;
	n = a.size();
	m = u.size();
	REP(i,m){
		adj[u[i]].pb(v[i]);
		rev[v[i]].pb(u[i]);
	}
	ans.resize(n);
	vi gg;
	REP(i,n) gg.pb(i);
	solve(gg);
	return ans;
}
