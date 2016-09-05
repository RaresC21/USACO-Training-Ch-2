/*
 ID: RaresC
 LANG: C++
 TASK: castle
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX 51
int width, height;
int ind=1;
int room_size[MAX*MAX], max_double;
int x, y; char dir; // position of wall.

struct Square {
    bool n, w, e, s;
    int ind;
} square[MAX][MAX];

void fill_room(int i, int k) {
    if (i < 0 || i >= height || k < 0 || k >= width) return;
    if (square[i][k].ind != 0) return;
    
    room_size[ind] ++;
    square[i][k].ind = ind;
    if (!square[i][k].n) fill_room(i-1, k);
    if (!square[i][k].e) fill_room(i, k+1);
    if (!square[i][k].s) fill_room(i+1, k);
    if (!square[i][k].w) fill_room(i, k-1);
}

void cut_walls() {
    // we only need to check for walls and different rooms on Norht or East.
    // we checked to the north and west earlier through a different wall's North or East.
    
    int size=0;
    for (int k = 0; k < width; k++)
        for (int i = height-1; i >= 0; i--) {
            // check for wall to the North and if there's a different room on that side.
            if (i-1 >= 0 && square[i][k].n && square[i-1][k].ind != square[i][k].ind) {
                size = room_size[square[i-1][k].ind] + room_size[square[i][k].ind];
                if (size > max_double) {
                    max_double = size;
                    x = k; y = i; dir = 'N';
                }
            }
            // same for East
            if (k+1 < width && square[i][k].e && square[i][k+1].ind != square[i][k].ind) {
                size = room_size[square[i][k+1].ind] + room_size[square[i][k].ind];
                if (size > max_double) {
                    max_double = size;
                    x = k; y = i; dir = 'E';
                }
            }
        }
}

int main() {
    
    ifstream fin ("castle.in");
    ofstream fout ("castle.out");
    
    fin >> width >> height;
    for (int i = 0; i < height; i++)
        for (int k = 0; k < width; k++) {
            int a; fin >> a;
            if (a - 8 >= 0) square[i][k].s = true, a-=8;
            if (a - 4 >= 0) square[i][k].e = true, a-=4;
            if (a - 2 >= 0) square[i][k].n = true, a-=2;
            if (a - 1 >= 0) square[i][k].w = true, a-=1;
        }
    
    for (int i = 0; i < height; i++)
        for (int k = 0; k < width; k++)
            if (square[i][k].ind == 0) {
                fill_room(i,k);
                ind++;
            }
    ind--; // negate the last addition, since there were no rooms for it.
    int max_room = 0; // get largest room
    for (int i = 0; i <= ind; i++)
        if (max_room < room_size[i]) max_room = room_size[i];
    cut_walls();
    fout << ind << "\n" << max_room << "\n" << max_double << "\n" << y+1 << " " << x+1 << " " << dir << "\n";
    
    return 0;
}