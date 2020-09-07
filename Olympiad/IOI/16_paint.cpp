#include "paint.h"

#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)

const int MAXN = 400005;
const int MAXK = 205;

int n,k;
int dp[MAXN][MAXK];
int suf[MAXN][MAXK];
int a[MAXN];
int b[MAXN];
int sm[MAXN];
int cnt[MAXN];

string solve_puzzle(string s, vector<int> c) {
	n = s.length();
	k = c.size();

	FOR(i,1,n+1){
		if(s[i-1] == '.') a[i] = 1;
		else if(s[i-1] == '_') a[i] = 2;
		else a[i] = 0;

		sm[i] = sm[i-1]+(a[i] == 2);
	}
	sm[n+1] = sm[n];
	FOR(i,1,k+1) b[i] = c[i-1];

	dp[0][0] = 1;
	FOR(i,1,n+1){
		dp[i][0] = (dp[i-1][0] and a[i]);
		dp[i][1] = 0;
		if(a[i]) dp[i][1] = dp[i-1][1];
		
		dp[i][1] |= (sm[i] == sm[i-b[1]] and i >= b[1] and dp[i-b[1]][0]);

		FOR(j,2,k+1){
			if(a[i]) dp[i][j] = dp[i-1][j];
			if(i > b[j] and a[i-b[j]] and sm[i] == sm[i-b[j]]) dp[i][j] |= dp[i-b[j]-1][j-1];
		}
	}
	suf[n+1][k+1] = 1;
	FORD(i,n,1){
		suf[i][k+1] = (suf[i+1][k+1] and a[i]);
		suf[i][k] = 0;
		if(a[i]) suf[i][k] = suf[i+1][k];
		
		suf[i][k] |= (sm[i+b[k]-1] == sm[i-1] and i <= n+1-b[k] and suf[i+b[k]][k+1]);

		FOR(j,1,k){
			if(a[i]) suf[i][j] = suf[i+1][j];
			if(i <= n-b[j] and a[i+b[j]] and sm[i+b[j]-1] == sm[i-1]) suf[i][j] |= suf[i+b[j]+1][j+1];
		}
	}

	FOR(i,1,n+1){
		if(i > 1 and a[i-1] == 0) continue;

		FOR(j,1,min(k+1,i+1)){
			if(i > 1 and dp[i-2][j-1] == 0) continue;
			if(i+b[j] > n+1) continue;
			if(i+b[j] < n+1 and suf[i+b[j]+1][j+1] == 0) continue;
			if(i+b[j] == n+1 and j != k) continue;
			if(sm[i-1] != sm[i+b[j]-1]) continue;
			if(i+b[j] <= n and a[i+b[j]] == 0) continue;
			cnt[i]++;
			cnt[i+b[j]]--;
		}
	}

	FOR(i,2,n+1) cnt[i] += cnt[i-1];

	string ans = "";
	FOR(i,1,n+1){
		if(a[i] == 0){
			ans += 'X';
			continue;
		}
		if(a[i] == 2){
			ans += '_';
			continue;
		}
		bool flag1 = 0,flag2 = 0;
		flag1 |= cnt[i];
			
		REP(j,k+1) flag2 |= (dp[i-1][j] and suf[i+1][j+1]);

		if(flag1 and flag2) ans += '?';
		else if(flag1) ans += 'X';
		else ans += '_';
	}
	return ans;
}
