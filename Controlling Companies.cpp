/*
 ID: RaresC
 LANG: C++
 TASK: concom
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX 101
int N;
int owns[MAX][MAX];
bool control[MAX][MAX];

void control_update(int owner, int comp) {
    
    // if already control, don't do this
    if (control[owner][comp])
        return;
    
    // 'owner' controls 'comp'
    control[owner][comp] = true;
    
    for (int i = 0; i < MAX; i++)
        owns[owner][i] += owns[comp][i];
    
    // controllers of owner control i
    for (int i = 0; i < MAX; i++)
        if (control[i][owner])
            control_update(i, comp);
    
    for (int i = 0; i < MAX; i++)
        if (owns[owner][i] > 50)
            control_update(owner, i);
}

void update_c(int owner, int comp, int pc) {
    
    // if company 'i' control company 'owner'
    for (int i = 0; i < MAX; i++)
        if (control[i][owner])
            owns[i][comp] += pc;
    
    // if 'i' controls 'comp'
    for (int i = 0; i < MAX; i++)
        if (owns[i][comp] > 50)
            control_update(i, comp);
    
}

int main() {
    
    ifstream fin ("input.txt");
    ofstream fout ("concom.out");
    
    fin >> N; N++;
    for (int i = 0; i < N; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        owns[a][b] = c;
        update_c(a, b, c);
    }
    
    for (int i = 0; i < MAX; i++)
        for (int k = 0; k < MAX; k++)
            if (i != k && control[i][k])
                cout << i << " " << k << "\n";
    
    return 0;
}