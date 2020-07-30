/*
Soln:
http://blog.brucemerry.org.za/2014/07/
*/

#include "friend.h"
#include<bits/stdc++.h>
using namespace std;

int findSample(int n,int confidence[],int host[],int protocol[]){
	int ans = 0;
	for(int i = n-1; i > 0; i --){
		if(!protocol[i]){
			ans += confidence[i];
			confidence[host[i]] = max(0,confidence[host[i]]-confidence[i]);
		}
		else if(protocol[i] == 1){
			confidence[host[i]] += confidence[i];
		}
		else confidence[host[i]] = max(confidence[host[i]],confidence[i]);
	}
	return ans+confidence[0];
}
