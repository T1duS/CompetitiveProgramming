#include<bits/stdc++.h>
using namespace std;
#include "assistant.h"

#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define all(v) v.begin(),v.end()

const int MAXN = 200005;

void Assist(unsigned char *A, int N, int K, int R) {

	set<int> x,y;
	REP(i,K){
		if(A[i]) x.insert(i);
		else y.insert(i);
	}
	REP(i,N){
		int c = GetRequest();
		if(x.find(c) == x.end()){
			int tbr = *y.begin();
			PutBack(tbr);
			y.erase(tbr);
		}
		else{
			x.erase(c);
		}
		if(A[i+K]) x.insert(c);
		else y.insert(c);
	}
}
