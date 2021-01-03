#include "poly.h"

Poly::Poly() {
}

Poly::Poly(Rational R) {
	(*this)[0] = R;
}

Poly operator + (Poly A, Poly B) {
	Poly C;
	for (auto& x : A) C[x.first] = x.second;
	for (auto& y : B) C[y.first] = C[y.first] + y.second;
	C.simp();
	return C;
}

Poly operator - (Poly A, Poly B) {
	Poly C;
	for (auto& x : A) C[x.first] = x.second;
	for (auto& y : B) C[y.first] = C[y.first] - y.second;
	C.simp();
	return C;
}

Poly operator * (Poly A, Poly B) {
	Poly C;
	for (auto& x : A) for (auto& y : B) C[x.first+y.first] = C[x.first + y.first] + x.second * y.second;
	C.simp();
	return C;
}

Poly operator / (Poly A, Poly B) {
	if (B.size() == 0) throw "Poly : divided by zero";
	Poly C;
	while (A.size() > 0 && A.deg() >= B.deg()) {
		ll d = A.deg() - B.deg();
		Rational a = A.rbegin()->second / B.rbegin()->second;
		A = A - B * Poly::xn(d) * a;
		C[d] = a;
	}
	C.simp();
	return C;
}

ll Poly::deg() { return size() == 0 ? 0 : rbegin()->first; }

void Poly::simp() {
	for (auto it = begin(); it != end(); ) {
		if (it->second == Rational(0)) it = erase(it);
		else ++it;
	}
}

Poly Poly::xn(ll n) {
	Poly A;
	A[n] = 1;
	return A;
}

void Poly::print(const std::string &var) {
	bool fi = false;
	for (auto &x : *this) {
		if (fi) std::cout << " + "; else fi = true;
		x.second.print();
		if (x.first != 0) std::cout << "*" << var << "^" << x.first;
	}
	//std::cout << std::endl;
}

Poly Poly::cyclotomic_polynomial(ll n) {
	Poly res(1);
	for (int i = 1; i <= n; i++) if (n % i == 0 && Algo::mu(n / i) == 1) {
		Poly tmp;
		tmp[i] = 1;
		tmp[0] = -1;
		res = res * tmp;
	}
	for (int i = 1; i <= n; i++) if (n % i == 0 && Algo::mu(n / i) == -1) {
		Poly tmp;
		tmp[i] = 1;
		tmp[0] = -1;
		res = res / tmp;
	}
	return res;
}

SPoly::SPoly() {
}

SPoly::SPoly(Rational R) {
	(*this)[0] = R;
}

bool SPoly::check() {
	for (auto& x : *this) {
		if (x.first > 0) break;
		auto it = find(-x.first);
		if (!(x.second == it->second)) return false;
	}
	return true;
}

SPoly SPoly::xn(ll n) {
	SPoly A;
	A[n] = A[-n] = 1;
	return A;
}

SPoly operator + (SPoly A, SPoly B) {
	SPoly C;
	for (auto& x : A) C[x.first] = x.second;
	for (auto& y : B) C[y.first] = C[y.first] + y.second;
	C.simp();
	return C;
}

SPoly operator - (SPoly A, SPoly B) {
	SPoly C;
	for (auto& x : A) C[x.first] = x.second;
	for (auto& y : B) C[y.first] = C[y.first] - y.second;
	C.simp();
	return C;
}

SPoly operator * (SPoly A, SPoly B) {
	SPoly C;
	for (auto& x : A) for (auto& y : B) C[x.first + y.first] = C[x.first + y.first] + x.second * y.second;
	C.simp();
	return C;
}

SPoly operator / (SPoly A, SPoly B) {
	if (B.size() == 0) throw "SPoly : divided by zero";
	if (!A.check() || !B.check()) throw "SPoly : not a SPoly";
	SPoly C;
	while (A.size() > 0 && A.deg() >= B.deg()) {
		ll d = A.deg() - B.deg();
		Rational a = A.rbegin()->second / B.rbegin()->second;
		A = A - B * SPoly::xn(d) * a;
		C[d] = C[0-d] = a;
	}
	C.simp();
	return C;
}

SPoly operator % (SPoly A, SPoly B) {
	if (B.size() == 0) throw "SPoly : divided by zero";
	if (!A.check() || !B.check()) throw "SPoly : not a SPoly";

	while (A.size() > 0 && A.deg() >= B.deg()) {
		ll d = A.deg() - B.deg();
		Rational a = A.rbegin()->second / B.rbegin()->second;
		A = A - B * SPoly::xn(d) * a;
	}
	return A;
}

ll SPoly::deg() { return size() == 0 ? 0 : rbegin()->first; }

void SPoly::simp() {
	for (auto it = begin(); it != end(); ) {
		if (it->second == Rational(0)) it = erase(it);
		else ++it;
	}
}

void SPoly::print(const std::string &var) {
	bool fi = false;
	for (auto& x : *this) {
		if (fi) std::cout << " + "; else fi = true;
		x.second.print();
		if (x.first != 0) std::cout << "*" << var << "^" << x.first;
	}
	//std::cout << std::endl;
}

std::complex<double> SPoly::getDouble(std::complex<double> var) {
	std::complex<double> res = 0;
	for (auto& x : *this) res += x.second.getDouble() * std::pow(var, x.first);
	return res;
}

SPoly SPoly::gcd(SPoly p,SPoly q) {
	if (p.size() == 0 || (q.size() > 0 && p.deg() < q.deg())) std::swap(p, q);
	while (q.size()) {
		p = p % q;
		std::swap(p, q);
	}
	return p;
}

SPoly SPoly::cyclotomic_polynomial(ll n) {
	Poly c = Poly::cyclotomic_polynomial(n);
	ll d = c.deg();
	if (d % 2 != 0) throw "SPoly::cyclotomic : phi(n) is not even";
	d /= 2;
	SPoly res;
	for (auto& x : c) res[x.first - d] = x.second;
	return res;
}