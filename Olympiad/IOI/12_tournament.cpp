#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)

const int MAXN = 100005;

int n;
int lft[MAXN],rgt[MAXN];
int seg[MAXN*4];

void build(int ind,int l,int r){
	if(l == r){
		seg[ind] = 1;
		return;
	}
	int mid = (l+r)/2;
	build(2*ind,l,mid);
	build(2*ind+1,mid+1,r);
	seg[ind] = seg[2*ind]+seg[2*ind+1];
}

int quer(int ind,int l,int r,int val){ // returns first index such that pref[0..ind] >= val;
	if(l == r){
		if(seg[ind] == val) return l;
		else return l+1;
	}
	int mid = (l+r)/2;
	if(seg[2*ind] >= val) return quer(2*ind,l,mid,val);
	else return quer(2*ind+1,mid+1,r,val-seg[2*ind]);
}

void upd(int ind,int l,int r,int pos,int val){
	if(r < pos or l > pos) return;
	if(l == r){
		seg[ind] = val;
		return;
	}
	int mid = (l+r)/2;
	upd(2*ind,l,mid,pos,val);
	upd(2*ind+1,mid+1,r,pos,val);
	seg[ind] = seg[2*ind]+seg[2*ind+1];	
}

vector<int> endings[MAXN];

stack<int> st;

int fen[MAXN];

void bitupd(int pos,int val){
	pos++;
	while(pos <= n){
		fen[pos] += val;
		pos += (pos&-pos);
	}
}

int bitquer(int pos){
	pos++;
	int res = 0;
	while(pos){
		res += fen[pos];
		pos -= (pos&-pos);
	}
	return res;
}


int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
	build(1,0,N-1);
	n = N;
	REP(i,C){
		vector<int> positions;
		FOR(j,S[i]+1,E[i]+3) positions.push_back(quer(1,0,N-1,j));
		positions.back()--;
		S[i] = positions[0];
		E[i] = positions.back();
		FOR(i,1,((int)positions.size())-1){
			// cout << "updating: " << positions[i] << endl;
			upd(1,0,N-1,positions[i],0);
		}
		// cout << S[i] << " " << E[i] << endl;
	}
	lft[0] = -1;
	rgt[n-1] = n-1;
	FOR(i,1,n) lft[i] = (K[i-1] > R)?(i-1):(lft[i-1]);
	for(int i = n-2; i >= 0; i--) rgt[i] = (K[i] > R)?(i):(rgt[i+1]);

	REP(i,C){
		endings[S[i]].push_back(E[i]);
	}
	REP(i,N) sort(endings[i].begin(),endings[i].end());

	// REP(j,C){
	// 	if(i >= S[j] and S[j] > lft[i] and i <= E[j] and E[j] <= rgt[i]) cnt++;
	// }

	int pos = -1,mx = -1;
	REP(i,n){
		if(i and lft[i] != lft[i-1]){
			while(!st.empty()){
				bitupd(st.top(),-1);
				st.pop();
			}
		}
		for(auto x:endings[i]){
			st.push(x);
			bitupd(x,1);
		}
		int cnt = bitquer(rgt[i])-bitquer(i-1);
		if(cnt > mx){
			mx = cnt;
			pos = i;
		}
	}
	return pos;
}
