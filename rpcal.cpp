#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;
 
vector<int> stack;
int stack_space = 3;
int working = 1;
char str[10];
 
int stack_pop() {
    int pop = stack.back();
    stack.pop_back();
    return pop;
}
 
void opspace() {
    cout << endl;
    for(int i=0;i<(stack_space+1);i++) {
        cout << "\t";
    }
    //cout << " ";
}
 
int add() {
    int a = stack_pop();
    int b = stack_pop();
    int c = b + a;
    opspace();
    cout << b << " + " << a << " = " << c;
    return c;
}
 
int subtract() {
    int a = stack_pop();
    int b = stack_pop();
    int c = b - a;
    opspace();
    cout << b << " - " << a << " = " << c;
    return c;
}
 
int multiply() {
    int a = stack_pop();
    int b = stack_pop();
    int c = b * a;
    opspace();
    cout << b << " * " << a << " = " << c;
    return c;
}
 
int divide() {
    int a = stack_pop();
    int b = stack_pop();
    int c = b / a;
    opspace();
    cout << b << " / " << a << " = " << c;
    return c;
}
 
int modulo() {
    int a = stack_pop();
    int b = stack_pop();
    int c = b % a;
    opspace();
    cout << b << " % " << a << " = " << c;
    return c;
}
 
int interpret() {
    char str[10];
    cin >> str;
    /**
    cout << str;
    /**/
    if(strncmp(str,"q",1)==0) {
        working = 0;
    } else if(strncmp(str,"+",1)==0) {
        stack.push_back(add());
    } else if(strncmp(str,"-",2)==0) {
        stack.push_back(subtract());
    } else if(strncmp(str,"*",1)==0) {
        stack.push_back(multiply());
    } else if(strncmp(str,"/",1)==0) {
        stack.push_back(divide());
    } else if(strncmp(str,"%",1)==0) {
        stack.push_back(modulo());
    } else {
        int num = strtol(str,NULL,10);
        stack.push_back(num);
        return num;
    }
}
 
void dumpstack() {
    for(int i=(stack_space-stack.size());i<0;i++) {
        stack_space++;
    }
    for(int i=0;i<(stack_space-stack.size());i++) {
        cout << "\t";
    }
    for(int i=0;i<stack.size();i++) {
        cout << "\t" << stack[i];
    }
}
 
void prompt() {
    cout << "\t|  ";
}
 
int loop() {
    while(working) {
        dumpstack();
        prompt();
        interpret();
        cout << endl;
    }
    return stack.back();
}
 
void stack_init() {
        stack.push_back(0);
    return;
}
 
void stack_clear() {
    stack.clear();
}
 
int main() {
    stack_init();
    stack_clear();
    dumpstack();cout << endl;
    cout << "==========================" << endl;
/*    int exit = */loop();
//    opspace();
//    cout << exit;
    return 0;
}
