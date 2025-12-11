#include <iostream>
#include <cstring>
#include <stack>
#include <cmath>
using namespace std;

stack<int> num;     // 操作数
stack<char> sig;    // 操作符

int infix_level(char a){
    if(a == '^') return 3;
    if(a == '*' || a == '/') return 2;
    if(a == '+' || a == '-') return 1;
    return 0;   // 括号
}

void infix_calc(){
    int b = num.top(); num.pop();
    int a = num.top(); num.pop(); 
    if(sig.top() == '+') num.push(a+b); 
    if(sig.top() == '-') num.push(a-b); 
    if(sig.top() == '*') num.push(a*b); 
    if(sig.top() == '/') num.push(a/b); 
    if(sig.top() == '^') num.push(pow(a, b)); 
    sig.pop();
}

string infix(string s){
    int x=0;    // 临时存储数字
    bool flg=0; // 是否是数字

    for(auto c: s)
    if(c>='0' && c<='9'){
        x = x*10 + c-'0';
        flg=1;
    }else{
        if(flg){
            num.push(x);
            x=0;
            flg=0;
        }   // 数字入栈
        if(c=='('){
            sig.push(c);
            continue;
        }   // 左括号入栈
        if(c==')'){
            while(sig.top()!='(') 
                infix_calc();
            sig.pop();
            continue;
        }   // 右括号, 一直计算到左括号
        
        // 此时c是运算符, 且有运算级更低的, 形如 (a*b+)
        while(sig.size() && infix_level(sig.top()) >= infix_level(c)) 
            infix_calc();
        sig.push(c);
    }
    // 最后一个数字
    if(flg) num.push(x);
    // 最后一个运算符
    while(sig.size()) infix_calc(); 
    return to_string(num.top());
}