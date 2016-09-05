/*
 ID: RaresC
 LANG: C++
 TASK: lamps
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX 101
int N, nPresses, total;
int final[MAX];
int current[MAX];
bool used[5];
string ans[MAX*100];

void add_answer() {
    for (int i = 1; i <= N; i++)
        ans[total] = ans[total] + (char)(current[i]+(int)'0');
}

void button_1() {
    for (int i = 1; i <= N; i++)
        if (current[i] == 1) current[i] = 0;
        else current[i] = 1;
}

void button_2() {
    for (int i = 1; i <= N; i+=2)
        if (current[i] == 1) current[i] = 0;
        else current[i] = 1;
}

void button_3() {
    for (int i = 2; i <= N; i+=2)
        if (current[i] == 1) current[i] = 0;
        else current[i] = 1;
}

void button_4() {
    for (int i = 1; i <= N; i+=3)
        if (current[i] == 1) current[i] = 0;
        else current[i] = 1;
}

void choose_Button(int i) {
    switch (i) {
        case 1:
            button_1();
            break;
        case 2:
            button_2();
            break;
        case 3:
            button_3();
        case 4:
            button_4();
        default:
            break;
    }
}

bool check_seq() {
    for (int i = 1; i <= N; i++) {
        if (final[i] == -1) continue;
        if (final[i] != current[i]) return false;
    }
    
    return true;
}

void solve(int press, int last) {
    
    if (press > nPresses) return;
    
    if (((press != 0 && nPresses % press == 0) || press == 0) && check_seq()) {
        add_answer();
        total ++;
    }
    
    for (int i = 1; i <= 4; i++) {
        if (used[i]) continue;
        
        choose_Button(i);
        used[i] = true;
        
        press++;
        solve(press, i);
        press--;
        
        used[i] = false;
        choose_Button(i);
    }
    
}

int main() {
    
    ifstream fin ("lamps.in");
    ofstream fout ("lamps.out");
    
    fin >> N >> nPresses;
    memset(final, -1, sizeof(final));
    for (int i = 1; i <= N; i++)
        current[i] = 1;
    
    int toggle; fin >> toggle;
    while (toggle != -1) {
        final[toggle] = 1;
        fin >> toggle;
    }
    fin >> toggle;
    while (toggle != -1) {
        final[toggle] = 0;
        fin >> toggle;
    }
    
    solve(0, 0);
    
    if (total == 0)
        fout << "IMPOSSIBLE\n";
    else {
        sort(ans, ans+total);
        for (int i = 0; i < total; i++)
            if (i == 0 || ans[i] != ans[i-1])
                fout << ans[i] << "\n";
    }
    
    return 0;
}