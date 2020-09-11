#include "gift.h"
#include<bits/stdc++.h>
using namespace std;
 
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
 
#define vi vector<int>
#define remin(a,b) a = min(a,b)
#define remax(a,b) a = max(a,b)
 
const int MX = 500005;
 
int lft[MX][3];
int dp[MX];
int pref[MX];
int breakable[MX];
 
int construct(int n, int r, vi a, vi b, vi x) {
    REP(i,n+1){
    	lft[i][1] = i;
    	lft[i][2] = 0;
    }
    REP(i,r){
    	a[i]++;
    	b[i]++;
    	if(x[i] == 1){
    		remin(lft[b[i]][1],a[i]);
    		pref[a[i]]++;
    		pref[b[i]]--;
    	}
    	else remax(lft[b[i]][2],a[i]);
    }
    FOR(i,2,n+1) pref[i] += pref[i-1];
    REP(i,n+1) breakable[i] = (pref[i] == 0);
 
    FORD(i,n-1,1){
    	remin(lft[i][1],lft[i+1][1]);
    }
    FOR(i,2,n+1){
    	remax(lft[i][2],lft[i-1][2]);
    }
    dp[0] = 0;
    int last = 0;
    FOR(i,1,n+1){
    	dp[i] = -1;
    	if(last >= lft[i][2]){
    		dp[i] = last;
    		if(breakable[i]) last = i;
    	}
    }
    if(dp[n] == -1) return 0;
    string s = "";
    REP(i,n) s += 'R';
    int cur = 0;
    int ind = n;
    while(ind){
    	if(cur){
	    	FOR(i,dp[ind],ind) s[i] = 'B';
    	}
    	cur = 1-cur;
    	ind = dp[ind];
    }
    craft(s);
    return 1;
}