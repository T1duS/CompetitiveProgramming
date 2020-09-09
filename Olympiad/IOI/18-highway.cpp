/*
Soln:
https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/IOI/IOI%2018-highway.cpp
*/

#include "highway.h"
#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pii pair<int,int>
#define F first
#define S second

const int MAXN = 200005;

int n,m,S,T;
long long path;

vector<pii> adj[MAXN];

int vis[MAXN];

void find_pair(int N, vi U, vi V, int A, int B) {
	n = N;
	m = U.size();

	REP(i,m){
		adj[U[i]].pb({V[i],i});
		adj[V[i]].pb({U[i],i});
	}

	vi w(m,0);
	path = ask(w);

	int l = 0,r = m-1,mid;
	while(l < r){
		mid = (l+r)/2;
		FOR(i,l,mid+1) w[i] = 1;
		if(ask(w) == path) l = mid+1;
		else{
			FOR(i,l,mid+1) w[i] = 0;
			r = mid;
		}
	}

	vector<pii> v1,v2;

	queue<pii> q;
	q.push({U[l],-1});
	vis[U[l]] = 1;
	q.push({V[l],-1});
	vis[V[l]] = 2;

	while(!q.empty()){
		pii u = q.front();
		q.pop();
		if(vis[u.F] == 1) v1.pb(u);
		else v2.pb(u);

		for(auto v:adj[u.F]){
			if(!vis[v.F]){
				vis[v.F] = vis[u.F];
				q.push(v);
			}
		}
	}

	int low = 0,high = v1.size()-1;
	while(low < high){
		mid = (low+high)/2;
		REP(i,m) w[i] = 1;
		w[l] = 0;
		FOR(i,1,(int)v2.size()) w[v2[i].S] = 0;
		FOR(i,1,mid+1) w[v1[i].S] = 0;
		if(ask(w) == path) high = mid;
		else low = mid+1;
	}
	S = v1[low].F;

	low = 0,high = v2.size()-1;
	while(low < high){
		mid = (low+high)/2;
		REP(i,m) w[i] = 1;
		w[l] = 0;
		FOR(i,1,(int)v1.size()) w[v1[i].S] = 0;
		FOR(i,1,mid+1) w[v2[i].S] = 0;
		if(ask(w) == path) high = mid;
		else low = mid+1;
	}
	T = v2[low].F;

	answer(S,T);
}
