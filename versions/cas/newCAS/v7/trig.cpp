#include "trig.h"

const RadicalExtension Trig::c15 = Rational(1,4) * (RadicalExtension(6,Rational(1,2)) + RadicalExtension(2,Rational(1,2)));
const RadicalExtension Trig::c30 = Rational(1,2) * RadicalExtension(3,Rational(1,2));
const RadicalExtension Trig::c45 = Rational(1,2) * RadicalExtension(2,Rational(1,2));

Trig::Trig() : p(RadicalExtension(0)), q(RadicalExtension(1)), base(1) {
}

Trig::Trig(SPoly p, SPoly q,ll base) : p(p), q(q), base(base) {
	/*out << "<>" << std::endl;
	out << "p  ";  p.printexp();  out << std::endl;
	out << "q  ";  q.printexp();  out << std::endl;*/
	if (base > 2) getCyclotomicPolynomial();
	simp();
	/*out << "p  ";  p.printexp();  out << std::endl;
	out << "q  ";  q.printexp();  out << std::endl;
	out << "<>" << std::endl;*/
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

bool operator == (Trig A, Trig B) {
    return A.base == B.base && A.p == B.p && A.q == B.q;
}

void Trig::simp() {
	/*out << "simp!" << std::endl;
	out << "p  ";  p.printexp();  out << std::endl;
	out << "q  ";  q.printexp();  out << std::endl;*/
	/*printexp();
	out << "cyc  ";  cyc.print("x");  out << std::endl << std::endl;*/

	if (base == 2) {
		p[0] = p[0] - p[1];  p[1] = RadicalExtension(0);
		q[0] = q[0] - q[1];  q[1] = RadicalExtension(0);
	} else if (base > 2) {
		p = p % cyc;
		q = q % cyc;
	}
	SPoly g = SPoly::gcd(p, q);
//    p.print("x");  out << std::endl;
//    q.print("x");  out << std::endl;
//    g.print("x");  out << std::endl;
	p = p / g;
	q = q / g;

	ll gg = base;
	for (auto& x : p) if (x.first > 0 && !(x.second == RadicalExtension(0))) gg = Algo::gcd(gg, x.first);
	for (auto& x : q) if (x.first > 0 && !(x.second == RadicalExtension(0))) gg = Algo::gcd(gg, x.first);
	
	/*printexp();
	out << "cyc  ";  cyc.print("x");  out << std::endl;
	out << "gg : " << gg << std::endl;*/

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

void Trig::printexp(std::ostream &out) const {
	std::stringstream ss;
	ss << "w_{" << base << "}";
	std::string s;
	ss >> s;

	out << "(";
	p.print(out,s);
	out << ")";
	out << " / ";
	out << "(";
	q.print(out,s);
	out << ")";
	out << "       base = " << base << std::endl;
}

void Trig::printtrig(std::ostream &out,const SPoly &p) const {
	bool fi = false;
	for (auto& x : p) {
		if (Rational(0) < x.first) break;
		if (fi) out << " + ";  else fi = true;
		if (x.first == Rational(0)) {
			x.second.print(out);
			continue;
		}
		auto it = p.find(-x.first);
		if (it == p.end()) throw "printtrig error!";
		else if (x.second == it->second) {
			(x.second * RadicalExtension(2)).print(out);
			out << "*cos(";
			Rational(x.first * (-360),base).print(out);
			out << "бу)";
		}
		else throw "printtrig error!";
	}
}

void Trig::printtrig(std::ostream &out) const {
	out << "[";
	printtrig(out,p);
	out << "]";
	out << " / ";
	out << "[";
	printtrig(out,q);
	out << "]";
//	out << std::endl;
}

std::string Trig::toTeX(const SPoly &p) const {
    std::stringstream ss;
    std::string output;
    bool fi = false;
    for (auto& x : p) {
        if (Rational(0) < x.first) break;
        if (fi) ss << "+";  else fi = true;
        if (x.first == Rational(0)) {
            ss << x.second.toTeX();
            continue;
        }
        auto it = p.find(-x.first);
        if (it == p.end()) throw "trig::toTeX error!";
        else if (x.second == it->second) {
            ss << (x.second * RadicalExtension(2)).toTeX();
            ss << "*\\cos(";
            ss << Rational(x.first * (-360),base).toTeX();
            ss << "\\deg)";
        }
        else throw "trig::toTeX error!";
    }
    ss >> output;
    return output;
}

std::string Trig::toTeX() const {
    std::stringstream ss;
    std::string output;
    if (q.size() == 1) {
        SPoly pp = p;
        auto it = q.find(0);
        if (it == q.end()) throw "Trig::toTeX Error";
        RadicalExtension inv = 1 / it->second;
        for (auto &x : pp) {
            x.second = x.second * inv;
        }
        ss << toTeX(pp);
    } else {
        ss << "\\frac{" << toTeX(p) << "}{" << toTeX(q) << "}";
    }
    ss >> output;
    return output;
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

bool Trig::isRadicalExtension() const {
    return base == 1;
}

RadicalExtension Trig::toRadicalExtension() const {
    if (base == 1) {
        auto itp = p.find(0);
        auto itq = q.find(0);
        if (itq == q.end()) throw "Trig::toRadicalExtension : Error, divided by zero !";
        if (itp == p.end()) return RadicalExtension(0);
        return itp->second / itq->second;
    } else throw "Trig::toRadicalExtension : Error, not a RadicalExtension !";
}

bool Trig::isRational() const {
    if (isRadicalExtension()) {
        RadicalExtension tmp = toRadicalExtension();
        return tmp.isRational();
    }
    return false;
}

Rational Trig::toRational() const {
    return toRadicalExtension().toRational();
}

bool Trig::isInteger() const {
    if (isRadicalExtension()) {
        RadicalExtension tmp = toRadicalExtension();
        return tmp.isInteger();
    }
    return false;
}

Integer Trig::toInteger() const {
    return toRadicalExtension().toRational().toInteger();
}

Hash Trig::getHash() const {
    Hash res = Hash(1430953,9480657) * Hash(base);
    for (auto &x : p) res = res + Hash(x.first+31084) * Hash(x.first+39840,197402973) * Hash(1028110,x.first+1094) * x.second.getHash();
    return res;
}