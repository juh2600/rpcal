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
char str[16];
bool shift = false;
bool warned = false;

void dumpstack() {
	for(int i = (stack_space - stack.size()); i < 0 ; i++) {			// for each time we have to shift over a tab
		stack_space++;
		for(int j = 0; j < 7; j++) {											// for each time we have to shift down a line and over a space, which we'll do six times
			if(j!=0){cout << "\n";}
			for(int k = 0; k+1 < stack_space; k++) {
				cout << "\t";												// for each tab we already had (?)
			}
			cout << " ";
			for(int k = 0; k < j; k++) {
				cout << " ";													// a space each time to move the slash over
			}
			cout << "\\";
		}
		shift = true;
	}
	cout << endl;
	for(int i = 0; i < (stack_space - stack.size()); i++) {
		cout << "\t";
	}
	for(unsigned i = 0; i < stack.size(); i++) {
		cout << stack[i] << "\t";
	}
}

void prompt() {
	cout << "|  ";
}

int stack_pop() {
	int pop = stack.back();
	stack.pop_back();
	return pop;
}

void opspace() {
	if (!shift) {
		cout << endl;
		shift = true;
	}
	for(int i = 0; i < stack_space; i++) {
		cout << "\t";
	}
	cout << "  ";
}

int checkDepth(int deep) {
	int have;
	have = stack.size();
	return (have >= deep);
}

int add() {
	if (!checkDepth(2)) {
		stack.push_back(0);
		opspace();
		cout << "Error: Not enough operands. Pushing 0.\n";
	}
	int a = stack_pop();
	int b = stack_pop();
	int c = b + a;
	opspace();
	cout << b << " + " << a << " = " << c;
	return c;
}

int subtract() {
	if (!checkDepth(2)) {
		stack.push_back(0);
		opspace();
		cout << "Error: Not enough operands. Pushing 0.\n";
	}
	int a = stack_pop();
	int b = stack_pop();
	int c = b - a;
	opspace();
	cout << b << " - " << a << " = " << c;
	return c;
}

int multiply() {
	if (!checkDepth(2)) {
		stack.push_back(1);
		opspace();
		cout << "Error: Not enough operands. Pushing 1.\n";
	}
	int a = stack_pop();
	int b = stack_pop();
	int c = b * a;
	opspace();
	cout << b << " * " << a << " = " << c;
	return c;
}

int divide() {
	if (!checkDepth(2)) {
		stack.push_back(1);
		opspace();
		cout << "Error: Not enough operands. Pushing 1.\n";
	}
	int a = stack_pop();
	if(a==0) {
		opspace();
		cout << "Division by zero is illegal.\n";
		opspace();
		cout << "Can I interest you in a limit?\n";
		return a;
	}
	int b = stack_pop();
	int c = b / a;
	opspace();
	cout << b << " / " << a << " = " << c;
	return c;
}

int modulo() {
	if (!checkDepth(2)) {
		stack.push_back(1);
		opspace();
		cout << "Error: Not enough operands. Pushing 1.\n";
	}
	int a = stack_pop();
	if (!warned && a==0) {
		warned = true;
		opspace();
		cout << "I wouldn't try that again if I were you...\n";
		opspace();
		cout << "(Note the use of the subjunctive case of `to be'.)\n";
		return a;
	}
	int b = stack_pop();
	int c = b % a;
	opspace();
	cout << b << " % " << a << " = " << c;
	return c;
}

void interpret() {
	char str[16];
	cin >> str;
	/**
		cout << str;
	/*/
		if(strncmp(str,"q",1)==0) {
		working = 0;
	} else	if(strncmp(str,".",1)==0) {
		return;
	} else	if(strncmp(str,"+",1)==0) {
		stack.push_back(add());
	} else	if(strncmp(str,"-",2)==0) {
		stack.push_back(subtract());
	} else	if(strncmp(str,"*",1)==0) {
		stack.push_back(multiply());
	} else	if(strncmp(str,"/",1)==0) {
		stack.push_back(divide());
	} else	if(strncmp(str,"%",1)==0) {
		stack.push_back(modulo());
	} else {
		int num = strtol(str,NULL,10);
		stack.push_back(num);
	}
}

int loop() {
	while(working) {
		dumpstack();
		prompt();
		interpret();
		//cout << endl;
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
	/* int exit = */loop();
	// opspace();
	// cout << exit;
	return 0;
}
