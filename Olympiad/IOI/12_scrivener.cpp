#include<bits/stdc++.h>
using namespace std;

int SZ = 0,commands = 0;

const int LIM = 40000005;
const int MAXN = 1000005;

char seg[LIM];
int lft[LIM];
int rgt[LIM];

int root[MAXN],len[MAXN];

int build(int l,int r){
	int ind = ++SZ;
	if(l == r){
		seg[ind] = '.';
		return ind;
	}
	int mid = (l+r)/2;
	lft[ind] = build(l,mid);
	rgt[ind] = build(mid+1,r);
	return ind;
}

int update(int prev,int l,int r,int pos,char val){
	int ind = ++SZ;
	lft[ind] = lft[prev];
	rgt[ind] = rgt[prev];
	if(l == r){
		seg[ind] = val;
		return ind;
	}
	int mid = (l+r)/2;
	if(pos <= mid) lft[ind] = update(lft[prev],l,mid,pos,val);
	else rgt[ind] = update(rgt[prev],mid+1,r,pos,val);
	return ind;
}

char query(int ind,int l,int r,int pos){
	if(l == r) return seg[ind];
	int mid = (l+r)/2;
	if(pos <= mid) return query(lft[ind],l,mid,pos);
	else return query(rgt[ind],mid+1,r,pos);
}

void Init(){
	root[0] = build(0,1e6-1);
	len[0] = 0;
}

void TypeLetter(char L){
	commands++;
	len[commands] = len[commands-1]+1;
	root[commands] = update(root[commands-1],0,1e6-1,len[commands-1],L);
}

void UndoCommands(int U) {
	commands++;
	root[commands] = root[commands-U-1];
	len[commands] = len[commands-U-1];
}

char GetLetter(int P) {
	return query(root[commands],0,1e6-1,P);

}
