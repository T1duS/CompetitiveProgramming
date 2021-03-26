#include "biscuits.h"
#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define vi vector<int>
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define SZ(v) (int)v.size()

int b[65],s[65];
map<int,int> dp;

int solve(int n,int x){
	if(n <= 0) return 0;
	if(n == 1) return 1;
	if(dp.find(n) != dp.end()) return dp[n];
	int i = 0,cur = 1;
	while(cur < n){
		cur *= 2;
		i++;
	}
	i--;
	cur /= 2;
	return dp[n] = solve(cur,x)+solve(min(n,1+s[i]/x)-cur,x);
}

int count_tastiness(int x, vi a) {
	REP(i,SZ(a)){
		b[i] = a[i];
		if(!i) s[i] = a[i];
		else s[i] = s[i-1]+(1LL<<i)*a[i];
	}
	FOR(i,SZ(a),61) s[i] = s[i-1];
	dp.clear();
	return solve(1LL<<60,x);
}

