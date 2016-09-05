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
char *opchar;
bool shift = false;

void dumpstack() {
	for(int i = (stack_space - stack.size()); i < 0 ; i++) {			// for each time we have to shift over a tab
		stack_space++;
		cout << endl;
		shift = true;
	}
	cout << endl;
	for(int i = 0; i < (int)(stack_space - stack.size()); i++) {
		cout << "\t";
	}
	for(unsigned i = 0; i < stack.size(); i++) {
		cout << stack[i] << "\t";
	}
}

void prompt() {	cout << "|  "; }

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

class F2 {
private:
    int err_push;
public:
    F2(int err, int (FuncName)(int[3]));
    int (*func)(int[3]);
    void f() {
        if (!checkDepth(2)) {
                stack.push_back(err_push);
                opspace();
                cerr << "rpcalc: not enough operands; pushing " << err_push << endl;
            }
        int c[3] = { stack_pop() , stack_pop() };
        c[2] = func(c);
        opspace();
        cout << c[1] << ' ' << opchar << ' ' << c[0] << " = " << c[2] << endl;
        stack.push_back(c[2]);
        return;
    }
};

F2::F2(int err, int FuncName(int[3]))
{
    err_push = err;
    func = FuncName;
    return;
}

int addition(int c[3]) { c[2] = c[1] + c[0]; return c[2]; }
int subtraction(int c[3]) { c[2] = c[1] - c[0]; return c[2]; }
int multiplication(int c[3]) { c[2] = c[1] * c[0]; return c[2]; }
int division(int c[3]) {
    if (c[0] != 0) { c[2] = c[1] / c[0]; return c[2]; }
    opspace(); cerr << "rpcalc: division by 0 is forbidden" << endl;
    stack.push_back(c[1]); return c[0];}
int modulation(int c[3]) {
    if (c[0] != 0) { c[2] = c[1] % c[0]; return c[2]; }
    opspace(); cerr << "rpcalc: modulo 0 is forbidden" << endl;
    stack.push_back(c[1]); return c[0];}
int power(int c[3]) { c[2] = pow(c[1], c[0]); return c[2]; }

F2 add (0,&addition);
F2 subtract (0, &subtraction);
F2 multiply (1, &multiplication);
F2 divide (1, &division);
F2 mod (1, &modulation);
F2 raise (1, &power);

void interpret() {
	char str[16];
	fill(str, str+16, 0);
	cin >> str;
	opchar = str;
    while(*opchar)
    { switch (*opchar)
        {   case 'q' : { working = 0; break; }
            case '.' :
            case ' ' : { break; }
            case 'f' : { dumpstack(); break; }
            case 'c' : { stack.clear(); break; }
            case 'r' : { int i = stack_pop(); int j = stack_pop(); stack.push_back(i); stack.push_back(j); break; }
            case 'd' : { stack.push_back(stack.back()); break; }
            case 'Z' : { stack.push_back(ceil(log10(stack_pop()))); break;}
            case 'z' : { stack.push_back(stack.size()); break; }
            case '+' : { add.f(); break; }
            case '-' : { subtract.f(); break; }
            case '*' : { multiply.f(); break; }
            case '/' : { divide.f(); break; }
            case '%' : { mod.f(); break; }
            case '^' : { raise.f(); break; }
            case '_' : { stack.push_back(0-strtol(opchar, &opchar, 0)); break; }
            default : { stack.push_back(strtol(opchar, &opchar, 0)); }
        }
        opchar++;
    }
}

int loop() {
    while(working) {
        dumpstack();
        prompt();
        interpret();
        }
    return stack.back();
}
void stack_init() { stack.push_back(0); return; }
void stack_clear() { stack.clear(); }
int main() {
    stack_init();
    stack_clear();
    dumpstack();
    cout << endl << "==========================" << endl;
    return loop();
}
