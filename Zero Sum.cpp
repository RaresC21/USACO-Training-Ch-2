/*
 ID: RaresC
 LANG: C++
 TASK: zerosum
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;

#define MAX 9
int signs[MAX];
char ops[3] = {' ', '+', '-'};
int N;

ofstream fout ("zerosum.out");

void print() {
    fout << 1;
    for (int i = 0; i < N-1; i++)
        fout << ops[signs[i]+1] << i+2;
    fout << "\n";
}

bool eval() {
    
    int sum = 1;
    int last_num = 1, last_op = 1;
    // last_op = 0 - blank, = 1 - sum, = -1 - subtraction
    for (int i = 0; i < N-1; i++) {
        switch (signs[i]) {
            case -1:
                sum += -last_op*last_num + last_op*(last_num*10 + i+2);
                last_num = last_num*10 + i+2;
                break;
            case 0:
                sum += i+2;
                last_op = 1;
                last_num = i+2;
                break;
            case 1:
                sum -= i+2;
                last_op = -1;
                last_num = i+2;
                break;
            default:
                break;
        }
    }
    
    if (sum == 0) return true;
    return false;
}

void recurse(int cur) {
    
    if (cur == N-1) {
        if (eval())
            print();
        return;
    }
    
    for (int i = -1; i <= 1; i++) {
        signs[cur] = i;
        recurse(cur+1);
    }
    
}

int main() {
    
    ifstream fin ("zerosum.in");
    
    fin >> N;
    recurse(0);
    
    return 0;
}