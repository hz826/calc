#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct Reader {
	private:
		string S;
		int now;

	public :
		Reader(string str);
		bool isDigit();
		bool isLetter();
		void getnxt();
		char next();
		int readInt();
		double readDouble();
		string readFunc();
};

Reader::Reader(string str) {
	S = str;
	now = 0;
}

bool Reader::isDigit() {
	return '0' <= next() && next() <= '9';
}

bool Reader::isLetter() {
	return 'a' <= next() && next() <= 'z';
}

void Reader::getnxt() {
	if (now < (int)S.length()) ++now;
}

char Reader::next() {
	return now < (int)S.length() ? S[now] : '`';
}

int Reader::readInt() {
	int res = 0;
	while (isDigit()) {
		res = res * 10 + (next()-'0');
		getnxt();
	}
	return res;
}

double Reader::readDouble() {
	double res = 0, scale = 1;
	while (isDigit()) {
		res = res * 10 + (next()-'0');
		getnxt();
	}
	if (next() == '.') {
		getnxt();
		while (isDigit()) {
			res = res * 10  + (next()-'0');
			scale *= 10;
			getnxt();
		}
	}
	return res /= scale;
}

string Reader::readFunc() {
	string res = "";
	while (isLetter()) {
		res += next();
		getnxt();
	}
	return res;
}

struct Num {
	Num() : v(0) {}
	Num(int v) : v(v) {}
	Num(double v) : v(v) {}
	Num(Reader &R) {v = R.readDouble();}
	Num(string func,Num a1) {
		
	}
	Num(string func,Num a1,Num a2) {
		
	}

private:
	double qpow(double a,long long x) {
		double r = 1;
		bool flag = false;
		if (x < 0) {
			x = -x;
			flag = true;
		}
		for (;x;x>>=1) {
			if (x & 1) r *= a;
			a *= a;
		}
		if (flag) r = 1.0 / r;
		return r;
	}
	bool isInteger(double a) {
		return fabs(round(a) - a) < 1e-7;
	}

public:
	double v;
	void add(Num x) {v += x.v;}
	void sub(Num x) {v -= x.v;}
	void mul(Num x) {v *= x.v;}
	void div(Num x) {
		if (x.v == 0) throw "divied by zero!";
		v /= x.v;
	}
	void pow(Num x) {
		if (isInteger(x.v)) {
			v = qpow(v,round(x.v));
		}
		else if (x.v < 0) throw "base is negative!";
		else v = std::pow(v,x.v);//in cmath
	}
	void func(string s) {

	}
};

template<typename T>
class Calc {
	private:
		Reader R;
		T readfunc();
		T read4();
		T read3();
		T read2();
		T read1();
		T getarg(char lc,char rc);
	public:
		Calc(string str);
		T get();
};

template<typename T>
Calc<T>::Calc(string str) : R(str) {
	
}

template<typename T>
T Calc<T>::readfunc() {
	string func = R.readFunc();
	T res;
	if (func == "sin") {

	}
	return res;
}

template<typename T>
T Calc<T>::read4() {
	T Left(1);
	if (R.next() == '-') {
		R.getnxt();
		Left = T(0);
		Left.sub(T(1));
	}
	
	for (bool flag = true;flag;) {
		T Right;

		switch (R.next()) {
			case '(' : 
				Right = getarg('(',')');
				break;
			
			case '\\' :
				R.getnxt();
				Right = readfunc();
				break;
			
			default :
				if (!R.isDigit()) {
					flag = false;
					break;
				}
				Right = T(R);
		}
		if (flag) Left.mul(Right);
	}
	return Left;
}

template<typename T>
T Calc<T>::read3() {
	T Left = read4();
	while (R.next() == '^') {
		char tmp = R.next();
		R.getnxt();
		T Right = read4();
		if (tmp == '^') Left.pow(Right);
	}
	return Left;
}

template<typename T>
T Calc<T>::read2() {
	T Left = read3();
	while (R.next() == '*' || R.next() == '/') {
		char tmp = R.next();
		R.getnxt();
		T Right = read3();
		if (tmp == '*') Left.mul(Right);
		if (tmp == '/') Left.div(Right);
	}
	return Left;
}

template<typename T>
T Calc<T>::read1() {
	T Left = read2();
	while (R.next() == '+' || R.next() == '-') {
		char tmp = R.next();
		R.getnxt();
		T Right = read2();
		if (tmp == '+') Left.add(Right);
		if (tmp == '-') Left.sub(Right);
	}
	return Left;
}

template<typename T>
T Calc<T>::getarg(char lc,char rc) {
	char Left = R.next();
	if (Left != lc) throw "unknown symbol";
	R.getnxt();
	T res = read1();
	char Right = R.next();
	if (Right != rc) throw "unmatched brace";
	R.getnxt();
	return res;
}

template<typename T>
T Calc<T>::get() {
	T res = read1();
	if (R.next() != '`') throw "syntax error";
	return res;
}

int main() {
	Calc<Num> X(string("1*2+3*4"));
	try {
		Num ans = X.get();
		printf("%f\n",ans.v);
	}
	catch (const char * err) {
		cout << "catched!" << endl;
		cout << err << endl << endl;
	}
}