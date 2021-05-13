#include<bits/stdc++.h>
#include "books.h"
using namespace std;

#define vi vector<int>
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)

const int MX = 1000005;

int n,S;
int lft,rgt,cur = 0;
int C[MX],L[MX],R[MX];

int solve(int l,int r){
	int ll = L[C[l]];
	int rr = R[C[r]];
	while(ll < l or rr > r){
		if(ll < l){
			l--;
			ll = min(ll,L[C[l]]);
			rr = max(rr,R[C[l]]);
		}
		else{
			r++;
			rr = max(rr,R[C[r]]);
			ll = min(ll,L[C[r]]);
		}
	}
	int costleft = 0,costright = 0;
	int indleft = -1,indright = -1;
	int mn = l,mx = r;
	for(int i = l-1; i >= lft; i --){
		if(R[C[i]] > S){
			indleft = i;
			break;
		}
	}
	for(int i = r+1; i <= rgt; i ++){
		if(L[C[i]] < S){
			indright = i;
			break;
		}
	}
	if(indleft == -1){
		for(int i = l-1; i >= lft; i --){
			mn = min(mn,L[C[i]]);
			if(mn == i) costleft += 2;
		}
		for(int i = r+1; i <= rgt; i ++){
			mx = max(mx,R[C[i]]);
			if(mx == i) costright += 2;
		}
		return costleft+costright;
	}
	int lcur = l,rcur = r;
	while(ll > indleft){
		costleft += 2;
		ll--;
		while(ll < l){
			l--;
			ll = min(ll,L[C[l]]);
			rcur = max(rcur,R[C[l]]);
		}
	}
	while(rr < indright){
		costright += 2;
		rr++;
		while(rr > r){
			r++;
			rr = max(rr,R[C[r]]);
			lcur = min(lcur,L[C[l]]);
		}
	}
	ll = min(lcur,ll);
	rr = max(rcur,rr);
	while(ll < l or rr > r){
		if(ll < l){
			l--;
			ll = min(ll,L[C[l]]);
			rr = max(rr,R[C[l]]);
		}
		else{
			r++;
			rr = max(rr,R[C[r]]);
			ll = min(ll,L[C[r]]);
		}
	}
	return min(costleft,costright)+solve(ll,rr);
}

long long minimum_walk(vi p, int s) {
	S = s;
	long long ans = 0;
	n = p.size();
	lft = s;
	rgt = s;
	REP(i,n) C[i] = -1;
	REP(i,n){
		ans += abs(p[i]-i);
		if(C[i] == -1){
			C[i] = cur;
			L[cur] = R[cur] = i;
			int j = i;
			while(true){
				j = p[j];
				C[j] = cur;
				R[cur] = max(R[cur],j);
				if(i == j) break;
			}
			cur++;
		}
		if(i != p[i]){
			lft = min(lft,i);
			rgt = max(rgt,i);
		}
	}
	return ans+solve(s,s);
}
