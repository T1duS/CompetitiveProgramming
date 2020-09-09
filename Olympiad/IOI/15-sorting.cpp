#include "sorting.h"

#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define vi vector<int>
#define pb push_back
#define SZ(v) (int)v.size()

const int MAXN = 200005;

int a[MAXN],b[MAXN];

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    int low = 0,high = M,mid,ans;
    while(low <= high){
    	mid = (low+high)/2;
    	vector<pii> v;

    	for(int i = 0; i < N; i ++) a[i] = S[i];
    	for(int i = 0; i < mid; i ++){
    		swap(a[X[i]],a[Y[i]]);
    	}
    	for(int i = 0; i < N; i ++) b[a[i]] = i;
    	for(int i = 0; i < N; i ++){
    		if(a[i] == i) continue;
    		int pos = b[i];
    		int val = a[i];
    		a[i] = i;
    		a[pos] = val;
    		b[i] = i;
    		b[val] = pos;
    		v.pb({i,val});
    	}

    	while(SZ(v) < mid) v.pb({0,0});

    	if(SZ(v) == mid){
    		ans = mid;
    		high = mid-1;

    		for(int i = 0; i < N; i ++){
    			a[i] = S[i];
    			b[a[i]] = i;
    		}

    		for(int i = 0; i < mid; i++){
    			swap(a[X[i]],a[Y[i]]);
    			b[a[X[i]]] = X[i];
    			b[a[Y[i]]] = Y[i];

    			P[i] = b[v[i].F];
    			Q[i] = b[v[i].S];

    			swap(a[P[i]],a[Q[i]]);
    			b[a[P[i]]] = P[i];
    			b[a[Q[i]]] = Q[i];
    		}

    	}
    	else low = mid+1;
    }
    return ans;
}


