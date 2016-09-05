/*
 ID: RaresC
 LANG: C++
 TASK: holstein
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX_V 25
#define MAX_F 15
int Vitamins, n_feed;
int need[MAX_V];
int feeds[MAX_F][MAX_V];

int best_feed[MAX_V], best_types[MAX_F];
int cur_feed[MAX_V], which_feed[MAX_F];
int best_amnt = 30;

bool enough_feed () {
    for (int i = 0; i < Vitamins; i++)
        if (cur_feed[i] < need[i])
            return false;
    return true;
}

void change_feed(int f, int dir) {
    for (int i = 0; i < Vitamins; i++)
        cur_feed[i] += dir * feeds[f][i];
}

void find_feed (int fid) { // feed i.d.
    
    int f_amnt = 0;
    for (int i = 0; i < n_feed; i++)
        if (which_feed[i]) f_amnt ++;
    
    if (f_amnt < best_amnt && enough_feed()) {
        best_amnt = f_amnt;
        for (int i = 0; i < n_feed; i++) {
            best_feed[i] = cur_feed[i];
            best_types[i] = which_feed[i];
        }
        
        return;
    }
    while (fid < n_feed && f_amnt <= best_amnt) {
        change_feed(fid, 1);
        which_feed[fid] = true;
        
        find_feed(fid+1);
        
        which_feed[fid] = false;
        change_feed(fid, -1);
        
        fid++;
    }
}

int main() {
    
    ifstream fin ("holstein.in");
    ofstream fout ("holstein.out");
    
    fin >> Vitamins;
    for (int i = 0; i < Vitamins; i++)
        fin >> need[i];
    fin >> n_feed;
    for (int i = 0; i < n_feed; i++)
        for (int k = 0; k < Vitamins; k++)
            fin >> feeds[i][k];
    find_feed(0);
    int types[MAX_F], cnt = 0;
    for (int i = 0; i < n_feed; i++)
        if (best_types[i]) types[cnt] = i+1, cnt++;
    
    fout << best_amnt << " ";
    if (cnt != 1)
        for (int i = 0; i < cnt-1; i++)
            fout << types[i] << " ";
    fout << types[cnt-1] << "\n";
    
    return 0;
}