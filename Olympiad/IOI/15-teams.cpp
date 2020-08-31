#include "teams.h"
#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define pb push_back

const int MAXN = 500005;
const int LIM = 120;
const int LG = 40;

int n;
pii a[MAXN];
int dp[MAXN];

int root[MAXN];

int SZ = 0;

int seg[MAXN*LG],lft[MAXN*LG],rgt[MAXN*LG];
int lb[MAXN];

int build(int l,int r){
	int ind = ++SZ;
	if(l == r) return ind;

	int mid = (l+r)/2;
	lft[ind] = build(l,mid);
	rgt[ind] = build(mid+1,r);

	return ind;
}

int update(int prev,int l,int r,int pos){
	int ind = ++SZ;
	if(l == r){
		seg[ind] = seg[prev]+1;
		return ind;
	}

	int mid = (l+r)/2;
	seg[ind] = seg[prev]+1;
	lft[ind] = lft[prev];
	rgt[ind] = rgt[prev];
	if(pos <= mid) lft[ind] = update(lft[prev],l,mid,pos);
	else rgt[ind] = update(rgt[prev],mid+1,r,pos);

	return ind;
}

int query(int ind1,int ind2,int l,int r,int pos){
	if(r < pos) return 0;
	if(l >= pos) return seg[ind2]-seg[ind1];

	int mid = (l+r)/2;
	return query(lft[ind1],lft[ind2],l,mid,pos)+query(rgt[ind1],rgt[ind2],mid+1,r,pos);
}

void init(int N, int A[], int B[]){
	n = N;
	for(int i = 0; i < n; i ++){
		a[i] = {A[i],B[i]};
	}
	sort(a,a+n);
	root[0] = build(1,n);
	for(int i = 1; i <= n; i++){
		root[i] = update(root[i-1],1,n,a[i-1].S);
	}
}

int can(int M, int K[]) {
	sort(K,K+M);
	if(M > 900){
		priority_queue<int,vector<int>,greater<int> > pq;
		int cur = 0;
		for(int i = 0; i < M; i ++){
			while(cur < n and a[cur].F <= K[i]){
				pq.push(a[cur].S);
				cur++;
			}
			int cnt = 0;
			while(cnt < K[i] and (!pq.empty())){
				int x = pq.top();
				pq.pop();
				if(x >= K[i]) cnt++;
			}
			if(cnt < K[i]) return 0;
		}
		return 1;
	}
	else{
		for(int i = 0; i <= M; i ++) lb[i] = (i?(lower_bound(a,a+n,make_pair(K[i-1]+1,-1))-a):0);
		dp[0] = 0;
		for(int i = 1; i <= M; i ++){
			dp[i] = n+1;
			for(int j = 0; j < i; j ++){
				int ind1 = lb[j];
				int ind2 = lb[i];
				
				dp[i] = min(dp[i],dp[j]-K[i-1]+query(root[ind1],root[ind2],1,n,K[i-1]));
			}
			if(dp[i] < 0) return 0;
		}
		return 1;
	}
}
