#include "trig.h"

const RadicalExtension Trig::c15 = Rational(1,4) * (RadicalExtension(6,Rational(1,2)) + RadicalExtension(2,Rational(1,2)));
const RadicalExtension Trig::c30 = Rational(1,2) * RadicalExtension(3,Rational(1,2));
const RadicalExtension Trig::c45 = Rational(1,2) * RadicalExtension(2,Rational(1,2));

Trig::Trig() : p(RadicalExtension(0)), q(RadicalExtension(1)), base(1) {
}

Trig::Trig(SPoly p, SPoly q,ll base) : p(p), q(q), base(base) {
	/*std::cout << "<>" << std::endl;
	std::cout << "p  ";  p.printexp();  std::cout << std::endl;
	std::cout << "q  ";  q.printexp();  std::cout << std::endl;*/
	if (base > 2) getCyclotomicPolynomial();
	simp();
	/*std::cout << "p  ";  p.printexp();  std::cout << std::endl;
	std::cout << "q  ";  q.printexp();  std::cout << std::endl;
	std::cout << "<>" << std::endl;*/
}

Trig::Trig(ll x) : p(Rational(x)), q(RadicalExtension(1)), base(1) {}
Trig::Trig(Rational R) : p(R), q(RadicalExtension(1)), base(1) {}
Trig::Trig(RadicalExtension R) : p(R), q(RadicalExtension(1)), base(1) {}

Trig Trig::sin(Rational alpha) {
	return cos(Rational(1, 2) - alpha);
}

Trig Trig::cos(Rational alpha) {//\alpha * pi = \alpha/2 * 2pi
	alpha = alpha / 2;
	alpha.mod();
	SPoly p;
	ll ap = alpha.p.toLongLong(), aq = alpha.q.toLongLong();
	p[ap] = p[ap] + Rational(1, 2);
	p[-ap] = p[-ap] + Rational(1, 2);
	Trig res(p, RadicalExtension(1), aq);
	return res;
}

Trig Trig::tan(Rational alpha) {
	return sin(alpha) / cos(alpha);
}

Trig Trig::sin(ll deg) {
	return sin(Rational(deg, 180));
}

Trig Trig::cos(ll deg) {
	return cos(Rational(deg, 180));
}

Trig Trig::tan(ll deg) {
	return tan(Rational(deg, 180));
}

Trig operator + (Trig A, Trig B) {
	ll nbase = Algo::lcm(A.base, B.base);
	A.changeBase(nbase);
	B.changeBase(nbase);
	return Trig(A.p * B.q + B.p * A.q, A.q * B.q, nbase);
}

Trig operator - (Trig A, Trig B) {
	ll nbase = Algo::lcm(A.base, B.base);
	A.changeBase(nbase);
	B.changeBase(nbase);
	return Trig(A.p * B.q - B.p * A.q, A.q * B.q, nbase);
}

Trig operator * (Trig A, Trig B) {
	ll nbase = Algo::lcm(A.base, B.base);
	A.changeBase(nbase);
	B.changeBase(nbase);
	return Trig(A.p * B.p, A.q * B.q, nbase);
}

Trig operator / (Trig A, Trig B) {
	ll nbase = Algo::lcm(A.base, B.base);
	A.changeBase(nbase);
	B.changeBase(nbase);
	return Trig(A.p * B.q, A.q * B.p, nbase);
}

void Trig::simp() {
	/*std::cout << "simp!" << std::endl;
	std::cout << "p  ";  p.printexp();  std::cout << std::endl;
	std::cout << "q  ";  q.printexp();  std::cout << std::endl;*/
	/*printexp();
	std::cout << "cyc  ";  cyc.print("x");  std::cout << std::endl << std::endl;*/

	if (base == 2) {
		p[0] = p[0] - p[1];  p[1] = RadicalExtension(0);
		q[0] = q[0] - q[1];  q[1] = RadicalExtension(0);
	} else if (base > 2) {
		p = p % cyc;
		q = q % cyc;
	}
	SPoly g = SPoly::gcd(p, q);
//    p.print("x");  std::cout << std::endl;
//    q.print("x");  std::cout << std::endl;
//    g.print("x");  std::cout << std::endl;
	p = p / g;
	q = q / g;

	ll gg = base;
	for (auto& x : p) if (x.first > 0 && !(x.second == RadicalExtension(0))) gg = Algo::gcd(gg, x.first);
	for (auto& x : q) if (x.first > 0 && !(x.second == RadicalExtension(0))) gg = Algo::gcd(gg, x.first);
	
	/*printexp();
	std::cout << "cyc  ";  cyc.print("x");  std::cout << std::endl;
	std::cout << "gg : " << gg << std::endl;*/

	if (gg == 0) throw "wrong gcd";
	if (gg > 1)	changeBase(base / gg);

	return;
}

void Trig::changeBase(ll nbase) {
	SPoly np, nq;
	for (auto& x : p) np[x.first * nbase / base] = x.second;
	for (auto& x : q) nq[x.first * nbase / base] = x.second;
	p = np;  q = nq;  base = nbase;
	if (base > 2) getCyclotomicPolynomial();
}

std::complex<double> Trig::getDouble() {
	std::complex<double> wn = std::exp(std::complex<double>(0, 2.0 * acos(-1) / base));
	return p.getDouble(wn) / q.getDouble(wn);
}

void Trig::printexp() {
	std::stringstream ss;
	ss << "w_{" << base << "}";
	std::string s;
	ss >> s;

	std::cout << "(";
	p.print(s);
	std::cout << ")";
	std::cout << " / ";
	std::cout << "(";
	q.print(s);
	std::cout << ")";
	std::cout << "       base = " << base << std::endl;
}

void Trig::printtrig(SPoly &p) {
	bool fi = false;
	for (auto& x : p) {
		if (Rational(0) < x.first) break;
		if (fi) std::cout << " + ";  else fi = true;
		if (x.first == Rational(0)) {
			x.second.print();
			continue;
		}
		auto it = p.find(-x.first);
		if (it == p.end()) throw "printtrig error!";
		else if (x.second == it->second) {
			(x.second * RadicalExtension(2)).print();
			std::cout << "*cos(";
			Rational(x.first * (-360),base).print();
			std::cout << "��)";
		}
		else throw "printtrig error!";
	}
}

void Trig::printtrig() {
	std::cout << "[";
	printtrig(p);
	std::cout << "]";
	std::cout << " / ";
	std::cout << "[";
	printtrig(q);
	std::cout << "]";
	std::cout << std::endl;
}

void Trig::getCyclotomicPolynomial() {
    cyc = SPoly::cyclotomic_polynomial(base);

    if (base % 24 == 0) {//   1/12 pi == (base/12)/base pi = (base/24)* 2pi/base
        SPoly tmp;
        tmp[base/24] = tmp[-base/24] = Rational(-1,2);
        tmp[0] = c15;
        cyc = SPoly::gcd(cyc, tmp);
    } else {
        if (base % 12 == 0) {
            SPoly tmp;
            tmp[base/12] = tmp[-base/12] = Rational(-1,2);
            tmp[0] = c30;
            cyc = SPoly::gcd(cyc, tmp);
        }
        if (base % 8 == 0) {
            SPoly tmp;
            tmp[base/8] = tmp[-base/8] = Rational(-1,2);
            tmp[0] = c45;
            cyc = SPoly::gcd(cyc, tmp);
        }
    }

//    std::stringstream ss;
//    ss << "w_{" << base << "}";
//    std::string s;
//    ss >> s;
//    cout << "cyc = ";  cyc.print(s);
//    cout << endl;
}