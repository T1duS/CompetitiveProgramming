#include "artclass.h"
#include<bits/stdc++.h>
using namespace std;

int freq[10000005];

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
    long long sm = 0;
    int tot = 0;
    
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            for(int k = i; k < min(i+10,H); k++){
                for(int l = j; l < min(j+10,W); l++){
                    if(i == k and j == l) continue;
                    int val = (R[i][j]-R[k][l])*(R[i][j]-R[k][l]);
                    val += (G[i][j]-G[k][l])*(G[i][j]-G[k][l]);
                    val += (B[i][j]-B[k][l])*(B[i][j]-B[k][l]);
                    sm += val;
                    tot++;
                    freq[val]++;
                }
            }
        }
    }
    int avg = (sm)/(tot);
    int med;
    int cur = 0;

    for(int i = 0; i < 10000000; i ++){
    	cur += freq[i];
    	if(cur*2 > tot){
    		med = i;
    		break;
    	}
    }

    long long prod = ((long long)med*avg);
    double div = ((double)avg/med);

    if(div > 10 and avg > 2000) return 1;
    if(med < 150) return 4;
    if(med < 2500) return 2;
    return 3;
}
