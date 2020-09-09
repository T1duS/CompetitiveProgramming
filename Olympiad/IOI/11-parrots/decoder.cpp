#include "decoder.h"
#include "decoderlib.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define F first
#define S second

void decode(int N, int L, int X[]){
	int ans[105];
	REP(i,N) ans[i] = 0;

	map<int,int> m;
	REP(i,L) m[X[i]]++;

	bool flag = 0;
	for(auto x:m){
		if(x.S >= 4){
			flag = 1;
			m[x.F] -= 1;
			if(m[x.F] >= 4) m[x.F] -= 4;
			break;
		}
	}

	for(auto x:m){
		int ind = x.F/8;
		if(x.S&2) ans[ind+32] += (1<<(x.F%8));
		if(x.S&1) ans[ind] += (1<<(x.F%8));
	}
	if(!flag){
		REP(i,N) output(ans[i]);
	}
	else{
		REP(i,N) output(255-ans[i]);
	}
}
