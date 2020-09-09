#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define pb push_back
#define F first
#define S second

void encode(int N, int M[]){
	int n = N;
	int a[105];
	REP(i,n) a[i] = M[i];

	vi v1,v2;

	REP(i,n){
		int times = 1;
		if(i >= 32) times++;

		int cur = (i%32)*8;
		REP(j,8){
			if(a[i]&(1<<j)){
				REP(k,times){
					v1.pb(cur+j);
				}
			}
			else{
				REP(k,times){
					v2.pb(cur+j);
				}
			}
		}
	}
	if(v1.size() <= 6*n){
		for(auto x:v1) send(x);
	}
	else{
		map<int,int> m;
		for(auto x:v2) m[x]++;
		bool f = 0;
		for(auto x:m){
			if(x.S >= 3){
				m[x.F] += 1;
				f = 1;
				break;
			}
		}
		if(!f){
			send(0);
			send(0);
			send(0);
			send(0);
			send(0);
		}
		for(auto x:m){
			REP(y,x.S) send(x.F);
		}
	}
}
