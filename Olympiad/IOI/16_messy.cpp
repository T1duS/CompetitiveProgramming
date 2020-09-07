#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i< b; i ++)

void build(int n,int l,int r){
	if(l == r) return;
	string s;
	REP(i,n) s += '1';
	FOR(i,l,r+1) s[i] = '0';

	int mid = (l+r)/2;
	FOR(i,l,mid+1){
		s[i] = '1';
		add_element(s);
		s[i] = '0';
	}
	build(n,l,mid);
	build(n,mid+1,r);
}

vi ans;

void solve(int n,int l,int r,vi v){ // v = possible indices for values l..r
	if(l == r){
		ans[v[0]] = l;
		return;
	}
	string s;
	REP(i,n) s += '1';
	for(auto i:v) s[i] = '0';

	vi lft,rgt;
	for(auto i:v){
		s[i] = '1';
		if(check_element(s)) lft.pb(i);
		else rgt.pb(i);
		s[i] = '0';
	}
	int mid = (l+r)/2;
	solve(n,l,mid,lft);
	solve(n,mid+1,r,rgt);
}

vi restore_permutation(int n, int w, int r) {
    build(n,0,n-1);
	compile_set();
    
    ans.resize(n);
    vi v;
    REP(i,n) v.pb(i);

    solve(n,0,n-1,v);
    return ans;
}