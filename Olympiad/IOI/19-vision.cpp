/*
Soln: 
https://www.youtube.com/watch?v=sPeGdReqQLs&t=4900s
*/
#include "vision.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define vi vector<int>
#define pb push_back

vi d1[405],d2[405];
int diag1[405],diag2[405];
int pref1[405],pref2[405];

void construct_network(int H, int W, int K){
	REP(i,H){
		REP(j,W){
			d1[i+j].pb(i*W+j);
			d2[i-j+W-1].pb(i*W+j);
		}
	}
	diag1[0] = add_or(d1[0]);
	diag2[0] = add_or(d2[0]);
	pref1[0] = diag1[0];
	pref2[0] = diag2[0];
	FOR(i,1,H+W-1){
		diag1[i] = add_or(d1[i]);
		diag2[i] = add_or(d2[i]);
		pref1[i] = add_or({pref1[i-1],diag1[i]});
		pref2[i] = add_or({pref2[i-1],diag2[i]});
	}
	vi ans1,ans2;
	int res1,res2;
	FOR(i,K,H+W-1){
		ans1.pb(add_and({pref1[i-K],diag1[i]}));
		ans1.pb(add_and({pref2[i-K],diag2[i]}));
		if(i != K){
			ans2.pb(add_and({pref1[i-K-1],diag1[i]}));
			ans2.pb(add_and({pref2[i-K-1],diag2[i]}));
		}
	}
	res1 = add_or(ans1);
	if(K != H+W-2){
		res2 = add_or(ans2);
		add_xor({res1,res2});
	}
}