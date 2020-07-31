/*
Soln:
Find position of 1 using binary search query(i,N) == N-1
After that solve left and right parts individually

For left part for example,
A[i-1] can be easily found by 1 query
For A[j], j <= i-2, you may require 1 or 2 queries
Check abs(A[j+1]-A[j]).
You get 2 possible values of A[j]
If one of the values has already been put somewhere then we don't need any more queries
Otherwise query(j,j+2) for finding exact value.

This is <= 2n+log(n) queries for sure
but not sure why it takes <= 2n queries(or maybe it doesn't and test cases are weak)
Logically thinking it is intuitive it should take much less steps but Idk formal proof.
*/

#include "xylophone.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)

static int A[5005];

int pos[5005];

void solve(int N) {
	REP(i,N+2) pos[i] = 0;
	int low = 1,high = N-1,mid,start;
	while(low <= high){
		mid = (low+high)/2;
		if(query(mid,N) == N-1){
			start = mid;
			low = mid+1;
		}
		else high = mid-1;
	}
	A[start] = 1;
	pos[1] = start;
	if(start-1){
		A[start-1] = 1+query(start-1,start);
		pos[A[start-1]] = start-1;
	}
	A[start+1] = 1+query(start,start+1);
	pos[A[start+1]] = start+1;
	for(int i = start-2; i >= 1; i --){
		int gg = query(i,i+1);
		bool f1 = (pos[min(A[i+1]+gg,N+1)]==0),f2 = (pos[max(A[i+1]-gg,0)]==0);
		if(f1 and f2){
			int gg2 = query(i,i+2);
			if(max({A[i+1]+gg,A[i+1],A[i+2]})-min({A[i+1]+gg,A[i+1],A[i+2]}) == gg2){
				A[i] = A[i+1]+gg;
			}
			else A[i] = A[i+1]-gg;
		}
		else if(f1) A[i] = A[i+1]+gg;
		else A[i] = A[i+1]-gg;
		pos[A[i]] = i;
	}
	for(int i = start+2; i <= N; i ++){
		int gg = query(i-1,i);
		bool f1 = (pos[min(A[i-1]+gg,N+1)]==0),f2 = (pos[max(A[i-1]-gg,0)]==0);
		if(f1 and f2){
			int gg2 = query(i-2,i);
			if(max({A[i-1]+gg,A[i-1],A[i-2]})-min({A[i-1]+gg,A[i-1],A[i-2]}) == gg2){
				A[i] = A[i-1]+gg;
			}
			else A[i] = A[i-1]-gg;
		}
		else if(f1) A[i] = A[i-1]+gg;
		else A[i] = A[i-1]-gg;
		pos[A[i]] = i;
	}
	REP(i,N) answer(i+1,A[i+1]);
}
 
