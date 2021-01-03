#include "biginteger.h"

int PInteger::log10(ll x) {
    constexpr ll p1 = 1e1, p2 = 1e2, p4 = 1e4, p8 = 1e8, p16 = 1e16;
    int r = 0;
    if (x >= p16) x /= p16, r |= 16;
    if (x >= p8)  x /= p8,  r |= 8;
    if (x >= p4)  x /= p4,  r |= 4;
    if (x >= p2)  x /= p2,  r |= 2;
    if (x >= p1)  x /= p1,  r |= 1;
    return r;
}

ll PInteger::pow10(int x) {
    ll r = 1, a = 10;
    for (;x;x>>=1) {
        if (x&1) r = r * a;
        a = a * a;
    } return r;
}

int PInteger::log10() const {
    int nn = n-1;
    while (a[nn] == 0 && nn > 0) --nn;
    return log10(a[nn]) + nn * M;
}

PInteger::PInteger() : n(1) {
    throw "PInteger : Error, dangerous constructor";
}

PInteger::PInteger(int n) : n(n) {
    if (n == 0) throw "PInteger : Error, new PInteger with len=0";
    a = new ll[n];
    for (int i=0;i<n;i++) a[i] = 0;
}

PInteger::PInteger(const std::string &s) {
    int l = s.length() - 1;
    a = new ll[n = l/PInteger::M+1];
    for (int i=0;i<n;i++) a[i] = 0;
    ll x = 0;
    for (int i=s.length()-1,d=1,j=0;i>=0;i--) {
        if (s[i] < '0' || s[i] > '9') throw "PInteger's constructor : Error, not a digit";
        x += (s[i] - '0') * d;
        d *= 10;
        if (d == PM || i == 0) d = 1, a[j] = x, x = 0, ++j;
    }
}

PInteger::PInteger(const PInteger &A) : n(A.n) {
    a = new ll[n];
    for (int i=0;i<n;i++) a[i] = A.a[i];
}

const PInteger& PInteger::operator = (const PInteger &A) {
    if (a == NULL) throw "PInteger : Error, a == NULL !";
    ll *p = new ll[n=A.n];//要考虑前后相等的情况
    for (int i=0;i<n;i++) p[i] = A.a[i];
    delete[] a;
    a = p;
    return *this;
}

PInteger::~PInteger() {
//    std::cout << "Delete : n = " << n << std::endl;
    delete[] a;
}

PInteger PInteger::Int(ll x) {
    if (x < 0) throw "PInteger::Int : Error, PInteger must be non-negative";
    PInteger A(log10(x)/PInteger::M+1);
    for (int t=0;x;t++, x/=PM) A.a[t] = x % PM;
    return A;
}

PInteger PInteger::shift(int d) const {
    PInteger B((log10()+d) / PInteger::M + 1);
    int d1 = d / PInteger::M;
    ll d2 = PInteger::pow10(d % PInteger::M);

    for (int i=0;i<n;i++) {
        B.a[i+d1] += a[i] * d2;
        B.a[i+d1+1] += B.a[i+d1] / PInteger::PM;
        B.a[i+d1] %= PInteger::PM;
    }
    return B;
}

PInteger operator + (const PInteger &A,const PInteger &B) {
    int l = std::max(A.log10(), B.log10()) + 1;
    PInteger C(l/PInteger::M+1);

    for (int i=0;i<C.n;i++) {
        C.a[i] += (i < A.n ? A.a[i] : 0) + (i < B.n ? B.a[i] : 0);
        if (C.a[i] >= PInteger::PM) C.a[i] -= PInteger::PM, ++C.a[i+1];
    }
    C.n = C.log10() / PInteger::M + 1;
    return C;
}

PInteger operator - (const PInteger &A,const PInteger &B) {
    int l = std::max(A.log10(), B.log10());
    PInteger C(l/PInteger::M+1);

    for (int i=0;i<C.n;i++) {
        C.a[i] += (i < A.n ? A.a[i] : 0) - (i < B.n ? B.a[i] : 0);
        if (C.a[i] < 0) C.a[i] += PInteger::PM, --C.a[i+1];
    }
    C.n = C.log10() / PInteger::M + 1;
    return C;
}

PInteger operator * (const PInteger &A,const PInteger &B) {
    int l = A.log10() + B.log10() + 1;
    PInteger C(l/PInteger::M+1);

    for (int i=0;i<A.n;i++) for (int j=0;j<B.n;j++) {
        C.a[i+j] += A.a[i] * B.a[j];
        C.a[i+j+1] += C.a[i+j] / PInteger::PM;
        C.a[i+j] %= PInteger::PM;
    }
    C.n = C.log10() / PInteger::M + 1;
    return C;
}

bool operator == (const PInteger &A,const PInteger &B) {
    int n = std::max(A.n, B.n);
    for (int i=n-1;i>=0;i--) {
        if ((i < A.n ? A.a[i] : 0) != (i < B.n ? B.a[i] : 0)) return false;
    }
    return true;
}

bool operator < (const PInteger &A,const PInteger &B) {
    int n = std::max(A.n, B.n);
    for (int i=n-1;i>=0;i--) {
        if ((i < A.n ? A.a[i] : 0) < (i < B.n ? B.a[i] : 0)) return true;
        else if ((i < A.n ? A.a[i] : 0) > (i < B.n ? B.a[i] : 0)) return false;
    }
    return false;
}

PInteger operator / (const PInteger &A,const PInteger &B) {
    if (B == PInteger::Int(0)) throw "Integer : Error, divided by zero !";
    int d = A.log10() - B.log10();
    if (d < 0) return PInteger::Int(0);
    PInteger AA(A), C(d/PInteger::M+1);

    while (d >= 0) {
        PInteger BB = B.shift(d);
        while (!(AA < BB)) {
            AA = AA - BB;
            C.a[d/PInteger::M] += PInteger::pow10(d % PInteger::M);
        }
        --d;
    }
    C.n = C.log10() / PInteger::M + 1;
    return C;
}

PInteger operator % (const PInteger &A,const PInteger &B) {
    if (B == PInteger::Int(0)) throw "Integer : Error, divided by zero !";
    int l = B.log10(), d = A.log10() - B.log10();
    if (d < 0) return A;
    PInteger AA(A), C(l/PInteger::M+1);

    while (d >= 0) {
        PInteger BB = B.shift(d);
        while (!(AA < BB)) AA = AA - BB;
        --d;
    }
    for (int i=0;i<C.n;i++) C.a[i] = AA.a[i];
    C.n = C.log10() / PInteger::M + 1;
    return C;
}

void PInteger::output(std::ostream &out,ll x) {
    for (int i=PInteger::M-1;i>=0;i--) {
        out << ((x / PInteger::pow10(i)) % 10);
    }
}

std::ostream & operator << (std::ostream &out,const PInteger &A) {
    out << A.a[A.n-1];
    for (int i=A.n-2;i>=0;i--) PInteger::output(out, A.a[i]);
    return out;
}

double PInteger::toDouble() const {
    double res = 0;
    for (int i=n-1;i>=0;i--) {
        res = res * PInteger::PM + a[i];
    }
    return res;
}

ll PInteger::toLongLong() const {
    if (n > 2) throw "Integer : Error, too large to change";
    ll res = 0;
    for (int i=n-1;i>=0;i--) {
        res = res * PInteger::PM + a[i];
    }
    return res;
}

Integer::Integer() : symbol('+'), X(PInteger::Int(0)) {
//    std::cout << "new empty Integer" << std::endl;
}

Integer::Integer(ll x) : symbol(x < 0 ? '-' : '+'), X(PInteger::Int(std::abs(x))) {
//    std::cout << "new Integer : " << x << std::endl;
}

Integer::Integer(const PInteger &X,char symbol) : X(X), symbol(symbol) {
    if (X == PInteger::Int(0)) this->symbol = '+';
}

Integer::Integer(const Integer &A) : X(A.X), symbol(A.symbol) {
}


Integer operator + (const Integer &A,const Integer &B) {
    if (A.symbol == '+' && B.symbol == '+') return Integer(A.X+B.X,'+');
    else if (A.symbol == '-' && B.symbol == '-') return Integer(A.X+B.X,'-');
    else if (A.symbol == '+' && B.symbol == '-') {
        if (!(A.X < B.X)) /*A>=B*/return Integer(A.X-B.X,'+');
        else return Integer(B.X-A.X,'-');
    }
    else /*if (A.symbol == '-' && B.symbol == '+')*/ {
        if (!(B.X < A.X)) /*B>=A*/return Integer(B.X-A.X,'+');
        else return Integer(A.X-B.X,'-');
    }
}

Integer operator - (const Integer &A,const Integer &B) {
    if (A.symbol == '+' && B.symbol == '-') return Integer(A.X+B.X,'+');
    else if (A.symbol == '-' && B.symbol == '+') return Integer(A.X+B.X,'-');
    else if (A.symbol == '+' && B.symbol == '+') {
        if (!(A.X < B.X)) /*A>=B*/return Integer(A.X-B.X,'+');
        else return Integer(B.X-A.X,'-');
    }
    else /*if (A.symbol == '-' && B.symbol == '-')*/ {
        if (!(B.X < A.X)) /*B>=A*/return Integer(B.X-A.X,'+');
        else return Integer(A.X-B.X,'-');
    }
}

Integer operator * (const Integer &A,const Integer &B) {
    if (A == Integer(0) || B == Integer(0)) return Integer(0);
    if (A.symbol == B.symbol) return Integer(A.X*B.X,'+');
    else return Integer(A.X*B.X,'-');
}

bool operator <  (const Integer &A,const Integer &B) {
    if (A.symbol == '+' && B.symbol == '+') return A.X < B.X;
    else if (A.symbol == '+' && B.symbol == '-') return false;
    else if (A.symbol == '-' && B.symbol == '+') return true;
    else /*if (A.symbol == '-' && B.symbol == '-')*/ return B.X < A.X;
}

bool operator == (const Integer &A,const Integer &B) {
    return A.symbol == B.symbol && A.X == B.X;
}

Integer operator / (const Integer &A,const Integer &B) {
    if (A.symbol == B.symbol) return Integer(A.X/B.X,'+');
    else return Integer(A.X/B.X,'-');
}

Integer operator % (const Integer &A,const Integer &B) {
    if (A.symbol == B.symbol) return Integer(A.X%B.X,'+');
    else return Integer(A.X%B.X,'-');
}

std::istream & operator >> (std::istream &in,Integer &A) {
    std::string s;
    in >> s;
    if (s[0] == '-') A.symbol = '-', s = s.substr(1);  else A.symbol = '+';
    A.X = PInteger(s);
    return in;
}

std::ostream & operator << (std::ostream &out,const Integer &A) {
    if (A.symbol == '-') out << '-';
    out << A.X;
    return out;
}

double Integer::toDouble() const {
    if (symbol == '+') return X.toDouble();
    else return -X.toDouble();
}

ll Integer::toLongLong() const {
    if (symbol == '+') return X.toDouble();
    else return -X.toDouble();
}

bool Integer::canChangetoLongLong() const {
    return X.n <= 2;
}