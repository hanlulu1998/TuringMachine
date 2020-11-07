//
// Created by HanLulu on 2020/11/6.
//

#include "TM.hpp"
#include <iostream>
#include "TM.hpp"

using namespace std;

int main() {
    int x = 0, y = 0;
    cout << "程序计算x^y，请输入x和y，并以回车结束：" << endl;
    cout << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    TM t(x, y);
    t.print();
    t.run();
    cout << "结果为：" << endl;
    cout << t.result() << endl;


    return 0;
}
