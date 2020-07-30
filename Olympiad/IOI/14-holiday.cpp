/*
n^2logn soln
Range over all l,r and pick best D-2*min(start-l,r-start)-max(start-l,r-start) elements
Its easy to prove why this works

nlog^2n soln
Let opt[i] denote the optimal r to choose for a fixed l. We can see that opt[i] is non-decreasing
So, we can use DnC to solve this
When checking for range l,r all elements in this range should be inserted inside a segment tree
for easy query handling
We can do this using rollback inside DnC so that when we changing ranges we also add/delete segtree nodes
*/

#include"holiday.h"
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pb push_back

const int MX = 100005;
int ans = 0,N,D,S;
pii a[MX];

struct node{
	int cnt,sum;
} seg[4*MX];

void upd(int ind,int l,int r,int pos,int val,int type){
	if(pos < l or pos > r) return;
	if(l == r){
		seg[ind].cnt = type;
		seg[ind].sum = val*type;
		return;
	}
	int m = (l+r)/2;
	upd(2*ind,l,m,pos,val,type);
	upd(2*ind+1,m+1,r,pos,val,type);
	seg[ind].cnt = seg[2*ind].cnt+seg[2*ind+1].cnt;
	seg[ind].sum = seg[2*ind].sum+seg[2*ind+1].sum;
}

int quer(int ind,int l,int r,int rem){
	if(l == r){
		if(rem) return seg[ind].sum;
		else return 0;
	}
	int m = (l+r)/2;
	if(seg[2*ind+1].cnt >= rem) return quer(2*ind+1,m+1,r,rem);
	else return seg[2*ind+1].sum+quer(2*ind,l,m,rem-seg[2*ind+1].cnt);
}

void solve(int l,int r,int optl,int optr){
	// assumes r+1...optl-1 are already activated in segtree
	int mid = (l+r)/2;
	if(S-mid >= D){
		if(mid != r) solve(mid+1,r,optl,optr);
		return;
	}
	int cur = -1,opt = optl;
	FOR(i,mid,r+1) upd(1,0,N-1,a[i].S,a[i].F,1);
	FOR(i,optl,optr+1){
		upd(1,0,N-1,a[i].S,a[i].F,1);
		int rem = D-2*min(S-mid,i-S)-max(S-mid,i-S);
		if(rem <= 0) break;
		int gg = quer(1,0,N-1,rem);
		if(gg > cur){
			cur = gg;
			opt = i;
		}
	}
	if(cur > ans) ans = cur;
	FOR(i,mid,r+1) upd(1,0,N-1,a[i].S,a[i].F,0);
	FOR(i,optl,optr+1) upd(1,0,N-1,a[i].S,a[i].F,0);

	if(l != mid){
		FOR(i,mid,r+1) upd(1,0,N-1,a[i].S,a[i].F,1);
		solve(l,mid-1,optl,opt);
		FOR(i,mid,r+1) upd(1,0,N-1,a[i].S,a[i].F,0);
	}
	if(r != mid){
		FOR(i,optl,opt) upd(1,0,N-1,a[i].S,a[i].F,1);
		solve(mid+1,r,opt,optr);
		FOR(i,optl,opt) upd(1,0,N-1,a[i].S,a[i].F,0);
	}
}

int findMaxAttraction(signed n, signed start, signed d, signed attraction[]) {
	vector<pii> v;
	D = d;
	N = n;
	S = start;
	REP(i,n) v.pb({attraction[i],i});
	sort(v.begin(),v.end());
	REP(i,n) a[v[i].S] = {v[i].F,i};
	solve(0,start,start,n-1);
	return ans;
}
