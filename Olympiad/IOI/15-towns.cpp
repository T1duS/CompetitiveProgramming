/*
Soln:
https://www.quora.com/What-is-the-solution-of-the-IOI-2015-task-Towns
https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/IOI/IOI%2015-towns.cpp
*/

#include "towns.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define pb push_back
#define F first
#define S second

int d0[1005],dA[1005];
int n,A,B,hub,quer;

int dist[1005][1005];

int getD(int i,int j){
	if(dist[i][j] == -1){
		quer++;
		dist[i][j] = getDistance(i,j);
		dist[j][i] = dist[i][j];
	} 
	return dist[i][j];
}

bool samecomp(int i,int j){
	return getD(i,j) != (dA[i]+dA[j]-2*hub);
}

int hubDistance(int N, int sub){
	quer = 0;
	n = N;
	REP(i,n){
		dist[i][i] = 0;
		FOR(j,i+1,n){
			dist[i][j] = -1;
			dist[j][i] = -1;
		}
	}
	A = B = 0;
	d0[0] = 0;
	FOR(i,1,n){
		d0[i] = getD(0,i);
		if(d0[i] > d0[A]) A = i;
	}
	dA[0] = d0[A];
	dA[A] = 0;
	FOR(i,1,n){
		if(i == A) continue;
		dA[i] = getD(A,i);
		if(dA[i] > dA[B]) B = i;
	}
	int R = 1000000000;
	map<int,int> gg; // dist from A from path A-0
	REP(i,n){
		int lol = (dA[0]+dA[i]-d0[i])/2;
		gg[lol]++;
		R = min(R,max(dA[B]-lol,lol));
	}
	int cur = 0;
	hub = -1;
	for(auto x:gg){
		if(cur > n/2) break;
		if(max(dA[B]-x.F,x.F) != R){
			cur += x.S;
			continue;
		}
		int p1 = x.S,p2 = n-cur-x.S;
		cur += p1;
		if(p2 > n/2) continue;
		if(p1 <= n/2) return R;
		hub = x.F;
	}
	if(hub == -1) return -R;
	vi elig;
	REP(i,n){
		if((dA[0]+dA[i]-d0[i])/2 == hub) elig.pb(i);
	}
	vi v1,v2;
	v1.pb(elig[0]);
	FOR(i,1,(int)elig.size()){
		if(samecomp(elig[i],v1.back())){
			v2.pb(elig[i]);
		}
		else{
			v1.pb(elig[i]);
			if(v2.size()){
				v1.pb(v2.back());
				v2.pop_back();
			}
		}
	}
	if(v2.empty()) return R;
	int cnt = (int)v2.size();
	int c = v2[0];
	while(!v1.empty()){
		if(cnt+(int)v1.size() <= n/2) return R;
		if(cnt > n/2) return -R;
		if(samecomp(v1.back(),c)){
			cnt++;
			v1.pop_back();
			if(!v1.empty()) v1.pop_back();
		}
		else v1.pop_back();
	}
	assert(quer <= (7*n)/2-8);
	if(cnt > n/2) return -R;
	return R;
}
