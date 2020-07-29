/*
Soln:
Same as IOI official soln
*/

#include "wall.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pii pair<int,int>
#define F first
#define S second
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)

const int MX = 2000005;
const int INF = 100000000;

struct node{
	int vadd,vsub;
	node(){
		vadd = -INF;
		vsub = INF;
	}
};

node seg[4*MX];
int ans[MX];

void change(int ind,int type,int val){
	if(type == 1){
		remax(seg[ind].vadd,val);
		remax(seg[ind].vsub,val);
	}
	else remin(seg[ind].vsub,val);
}


void push(int ind,int l,int r){
	if(l == r) return;

	change(2*ind,1,seg[ind].vadd);
	change(2*ind,2,seg[ind].vsub);

	change(2*ind+1,1,seg[ind].vadd);
	change(2*ind+1,2,seg[ind].vsub);
	
	seg[ind].vadd = -INF;
	seg[ind].vsub = INF;
}

void upd(int ind, int l, int r, int x, int y, int type,int val){
	push(ind,l,r);
	if(l > y or r < x) return;
	if(l >= x and r <= y){
		change(ind,type,val);
		push(ind,l,r);
		return;
	}
	int m = (l+r)/2;
	upd(2*ind,l,m,x,y,type,val);
	upd(2*ind+1,m+1,r,x,y,type,val);
}

void calc(int ind,int l,int r){
	push(ind,l,r);
	if(l == r){
		ans[l] = min(seg[ind].vadd,seg[ind].vsub);
		return;
	}
	int m = (l+r)/2;
	calc(2*ind,l,m);
	calc(2*ind+1,m+1,r);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	upd(1,0,n-1,0,n-1,1,0);
	upd(1,0,n-1,0,n-1,2,0);
	REP(i,k) upd(1,0,n-1,left[i],right[i],op[i],height[i]);
	calc(1,0,n-1);
	REP(i,n) finalHeight[i] = ans[i];
}

