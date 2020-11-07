//
// Created by HanLulu on 2020/11/6.
//

#ifndef TM2_TM_HPP
#define TM2_TM_HPP

#include <iostream>
#include <vector>

using namespace std;

class TM {
public:
    TM(int, int);

    void run();

    void print();

    int result();

private:
    int rw1, rw2, rw3;
    vector<char> tape1, tape2, tape3;
    int state;


};

TM::TM(int x, int y) {
    //初始化磁带1,2,3
    for (int i = 0; i < y; i++) {
        tape1.push_back('1');
    }
    for (int i = 0; i < x; i++) {
        tape2.push_back('1');
    }
    tape3.push_back('1');
    tape3.push_back('0');
    tape3.push_back('0');

    rw1 = 0;
    rw2 = 0;
    rw3 = 0;
    state = 0;
}

void TM::print() {
    cout << "打印带1：" << endl;
    for (auto i:tape1) {
        cout << i;
    }
    cout << endl;

    cout << "打印带2：" << endl;
    for (auto i:tape2) {
        cout << i;
    }
    cout << endl;

    cout << "打印带3：" << endl;
    for (auto i:tape3) {
        cout << i;
    }
    cout << endl;


}

void TM::run() {
    while (state != 13) {
        switch (state) {
            case 0:
                if (rw1 == tape1.size()) {
                    state = 13;
                } else if (tape1[rw1] == '1') {//q0带1所有1依次变为a,进入q1
                    state = 1;
                    tape1[rw1] = 'a';
                    rw1++;
                }
                break;
            case 1:
                if (rw2 == tape2.size()) {//带2完全变为b，内循环结束
                    state = 8;
                    rw2--;
                } else if (tape2[rw2] == '1') {//q1带2所有1依次变为b，进入q2
                    state = 2;
                    tape2[rw2] = 'b';
                    rw2++;
                }
                break;
            case 2:
                if (tape3[rw3] == '1') {//q2带3的1依次变为c，进入q3
                    state = 3;
                    tape3[rw3] = 'c';
                    rw3++;
                } else if (tape3[rw3] == '0') {
                    state = 7;
                    rw3--;
                }
                break;
            case 3:
                if (tape3[rw3] == '1') {
                    rw3++;
                } else if (tape3[rw3] == '0') {//q4开始补1
                    state = 4;
                    rw3++;
                }
                break;
            case 4:
                if (rw3 == tape3.size()) {//遇到尾部空格
                    state = 5;
                    tape3.push_back('1');
                    rw3++;
                } else if (tape3[rw3] == '0') {
                    state = 5;
                    tape3[rw3] = '1';
                    rw3++;
                } else if (tape3[rw3] == '1') {
                    rw3++;
                }
                break;
            case 5:
                if (rw3 == tape3.size()) {
                    state = 6;
                    tape3.push_back('0');
                }
            case 6:
                if (tape3[rw3] == '1' || tape3[rw3] == '0') {
                    rw3--;
                } else if (tape3[rw3] == 'c') {
                    state = 2;
                    rw3++;
                }
                break;
            case 7:
                if (rw3 == -1) {
                    state = 1;
                    rw3++;
                } else if (tape3[rw3] == 'c') {//将c变为1
                    tape3[rw3] = '1';
                    rw3--;
                }
                break;
            case 8:
                if (rw2 == -1) {
                    state = 9;
                    rw2++;

                } else if (tape2[rw2] == 'b') {
                    tape2[rw2] = '1';
                    rw2--;
                }
                break;
            case 9:
                if (tape3[rw3] == '1') {
                    tape3[rw3] = 'd';
                    rw3++;
                } else if (tape3[rw3] == '0') {
                    state = 10;
                    tape3[rw3] = '1';
                    rw3++;
                }
                break;
            case 10:
                if (tape3[rw3] == '1') {
                    rw3++;
                } else if (tape3[rw3] == '0') {
                    state = 11;
                    tape3.pop_back();
                    rw3--;
                }
                break;
            case 11:
                if (tape3[rw3] == '1') {
                    state = 12;
                    tape3[rw3] = '0';
                    rw3--;
                }
                break;
            case 12:
                if (rw3 == -1) {
                    rw3++;
                    state = 0;

                } else if (tape3[rw3] == '1') {
                    rw3--;
                } else if (tape3[rw3] == 'd') {
                    tape3[rw3] = '1';
                    state = 10;
                    rw3++;
                }
                break;
            default:
                break;
        }
    }
}

int TM::result() {
    int re = 0;
    for (auto i:tape3) {
        if (i == '1') {
            re++;
        }
    }
    return re;
}

#endif //TM2_TM_HPP
