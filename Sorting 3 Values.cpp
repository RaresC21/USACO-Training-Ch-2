/*
 ID: RaresC
 LANG: C++
 TASK: sort3
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX 1000
int N;
int values[MAX], goal[MAX];

void switch_val (int i, int k) {
    int temp = values[i];
    values[i] = values[k];
    values[k] = temp;
}

int main() {
    
    ifstream fin ("sort3.in");
    ofstream fout ("sort3.out");
    
    fin >> N;
    for (int i = 0; i < N; i++) {
        int a; fin >> a;
        values[i] = a; goal[i] = a;
    }
    sort(goal, goal+N);
    
    int ans = 0, s_value = -1;
    for (int i = 0; i < N; i++) {
        if (goal[i] == values[i]) continue;
        for (int k = 0; k < N; k++) {
            // look first for switches that makes both in the correct place
            if (goal[k] != values[i]) continue;
            if (goal[i] == values[k]) {
                switch_val(i, k);
                ans++; s_value = -1;
                break;
            }
            else if (goal[k] != values[k])
                s_value = k;
        }
        if (s_value != -1) {
            switch_val(i, s_value);
            s_value = -1; ans++;
        }
    }
    
    fout << ans << "\n";
    
    return 0;
}