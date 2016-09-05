/*
 ID: RaresC
 LANG: C++
 TASK: subset
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

#define MAX 1000
int N, s;
int sets[MAX][MAX];

int main() {
    
    ifstream fin ("subset.in");
    ofstream fout ("subset.out");
    
    fin >> N;
    s = N*(N+1);
    if (s % 4!= 0) {
        fout << 0 << "\n"; return 0;
    }
    s /= 4;
    
    memset(sets, 0, sizeof(sets[0]));
    sets[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int sum = 0; sum <= s; sum++)
            sets[sum][i] = sets[sum][i-1];
        for (int sum = 0; sum <= s-i; sum++)
            sets[sum+i][i] += sets[sum][i-1];
    }
    
    fout << sets[s][N-1] << "\n";
    
    return 0;
}