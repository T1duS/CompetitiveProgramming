#include "cave.h"
#include<bits/stdc++.h>
using namespace std;

int n;

void exploreCave(int N) {
    n = N;
    int S[N],D[N],a[N];
    for(int i = 0; i < n; i ++){
    	S[i] = -1;
    	D[i] = -1;
    }

    for(int i = 0; i < n; i ++){
    	for(int j = 0; j < n; j++){
    		if(S[j] == -1) a[j] = 0;
    		else a[j] = S[j];
    	}
    	int res = tryCombination(a);
    	int low = 0,high = n-1,mid;
    	if(res == -1 or res > i){ 
    		while(low < high){
    			mid = (low+high)/2;
    			for(int j = 0; j < n; j ++){
    				if(S[j] != -1) a[j] = S[j];
    				else if(low <= j and j <= mid) a[j] = 0;
    				else a[j] = 1; 
    			}
    			res = tryCombination(a);
    			if(res == -1 or res > i){
    				high = mid;
    			}
    			else low = mid+1;
    		}
    		D[low] = i;
    		S[low] = 0;
    	}
    	else{
    		while(low < high){
    			mid = (low+high)/2;
    			for(int j = 0; j < n; j ++){
    				if(S[j] != -1) a[j] = S[j];
    				else if(low <= j and j <= mid) a[j] = 1;
    				else a[j] = 0; 
    			}
    			res = tryCombination(a);
    			if(res == -1 or res > i){
    				high = mid;
    			}
    			else low = mid+1;
    		}
    		D[low] = i;
    		S[low] = 1;
    	}
    }
    answer(S,D);
}
