#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Reader {
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
	return ('a' <= next() && next() <= 'z') || ('A' <= next() && next() <= 'Z');
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

class Number {
private:
	static double qpow(double a,long long x) {
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

	bool isInteger() {
		return fabs(round(v) - v) < 1e-7;
	}

public:
	Number() : v(0) {}
	Number(int v) : v(v) {}
	Number(double v) : v(v) {}
	Number(Reader &R) {v = R.readDouble();}

	double v;
	friend Number operator + (Number A,Number B) {return Number(A.v+B.v);}
	friend Number operator - (Number A,Number B) {return Number(A.v-B.v);}
	friend Number operator * (Number A,Number B) {return Number(A.v*B.v);}
	friend Number operator / (Number A,Number B) {
		if (B.v == 0.0) throw "divied by zero!";
		return Number(A.v/B.v);
	}
	friend Number operator ^ (Number A,Number B) {
		if (B.isInteger()) return Number(std::pow(A.v,round(B.v)));
		else if (B.v < 0) throw "base is negative!";
		return Number(std::pow(A.v,B.v));//in cmath
	}

	static Number PI() {return Number(acos(-1));}
	static Number E() {return Number(exp(1));}
	static Number abs(Number a) {return Number(std::abs(a.v));}
	static Number sin(Number a) {return Number(std::sin(a.v));}
	static Number cos(Number a) {return Number(std::cos(a.v));}
	static Number tan(Number a) {return Number(std::tan(a.v));}
	static Number ln(Number a)  {
		if (a.v < 0) throw "ln : a<0";
		return Number(std::log(a.v));
	}
	static Number lg(Number a)  {
		if (a.v < 0) throw "lg : a<0";
		return Number(std::log10(a.v));
	}
	static Number log(Number a,Number b) {
		if (a.v < 0) throw "log : a<0";
		if (a.v == 1) throw "log : a=1";
		if (b.v < 0) throw "log : b<0";
		return Number(std::log(b.v) / std::log(a.v));
	}
	static Number sqrt(Number a) {
		if (a.v < 0) throw "sqrt : a<0";
		return Number(std::sqrt(a.v));
	}
	static Number sqrtn(Number a,Number b) {
		return a ^ (Number(1) / b);
	}
};

template<typename T>
class Calc {
	private:
		Reader R;
		T readFunc();
		T read4();
		T read3();
		T read2();
		T read1();
		T readBracket(char lc,char rc);
	public:
		Calc(string str);
		T get();
};

template<typename T>
Calc<T>::Calc(string str) : R(str) {
	
}

template<typename T>
T Calc<T>::readFunc() {
	string func = R.readFunc();
	T res;
	if (func == "E") return Number::E();
	if (func == "PI") return Number::PI();
	if (func == "abs") return Number::abs(readBracket('{','}'));
	if (func == "sin") return Number::sin(readBracket('(',')'));
	if (func == "cos") return Number::cos(readBracket('(',')'));
	if (func == "tan") return Number::tan(readBracket('(',')'));
	if (func == "ln") return Number::ln(readBracket('(',')'));
	if (func == "lg") return Number::lg(readBracket('(',')'));
	if (func == "log") return Number::log(readBracket('{','}'),readBracket('{','}'));
	if (func == "sqrtn") return Number::log(readBracket('{','}'),readBracket('{','}'));
	if (func == "sqrt") return Number::sqrt(readBracket('{','}'));
	return res;
}

template<typename T>
T Calc<T>::read4() {
	T Left(1);
	if (R.next() == '-') {
		R.getnxt();
		Left = T(-1);
	}
	
	for (bool flag = true;flag;) {
		T Right;

		switch (R.next()) {
			case '(' : 
				Right = readBracket('(',')');
				break;
			
			case '\\' :
				R.getnxt();
				Right = readFunc();
				break;
			
			default :
				if (!R.isDigit()) {
					flag = false;
					break;
				}
				Right = T(R);
		}
		if (flag) Left = Left * Right;
	}
	return Left;
}

template<typename T>
T Calc<T>::read3() {
	T Left = read4();
	while (R.next() == '^') {
		R.getnxt();
		T Right = readBracket('{','}');
		Left = Left ^ Right;
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
		if (tmp == '*') Left = Left * Right;
		if (tmp == '/') Left = Left / Right;
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
		if (tmp == '+') Left = Left + Right;
		if (tmp == '-') Left = Left - Right;
	}
	return Left;
}

template<typename T>
T Calc<T>::readBracket(char lc,char rc) {
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
	Calc<Number> X(string("\\sin(1/3*\\PI)^{2}"));
	try {
		Number ans = X.get();
		printf("%f\n",ans.v);
	}
	catch (const char * err) {
		cout << "catched!" << endl;
		cout << err << endl << endl;
	}
}