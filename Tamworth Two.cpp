/*
 ID: RaresC
 LANG: C++
 TASK: ttwo
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX 10
char maze[MAX][MAX];
int dir[8] = {0,-1, 1,0, 0,1, -1,0};
int f_x, f_y, f_d, c_x, c_y, c_d;

void make_step(int *x, int *y, int *d) {
    
    int x1 = *x + dir[*d];
    int y1 = *y + dir[*d+1];
    
    if (x1 < 0 || y1 < 0 || x1 >= 10 || y1 >= 10 || maze[y1][x1] == '*')
        *d = (*d + 2) % 8;
    else {
        *x = x1;
        *y = y1;
    }
}

int main() {
    
    ifstream fin ("ttwo.in");
    ofstream fout ("ttwo.out");
    
    for (int i = 0; i < MAX; i++)
        for (int k = 0; k < MAX; k++) {
            fin >> maze[i][k];
            if (maze[i][k] == 'C') {
                c_x = k;
                c_y = i;
            }
            if (maze[i][k] == 'F') {
                f_x = k;
                f_y = i;
            }
        }
    
    long steps = 0;
    while (steps < 16000) {
        steps++;
        make_step(&f_x, &f_y, &f_d);
        make_step(&c_x, &c_y, &c_d);
        if (f_x == c_x && f_y == c_y)
            break;
    }
    
    if (steps == 16000) fout << 0 << "\n";
    else fout << steps << "\n";
    
    return 0;
}