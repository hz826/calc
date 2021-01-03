#include "radicalextension.h"

void RadicalExtension::changebase(Base nbase) {
//    base.print(base); std::cout<<std::endl;
//    nbase.print(nbase); std::cout<<std::endl;
    Values nvalue;
    for (auto v : value) {
        Factor F = base.decode(v.first);
        for (auto &x : F) {
            if (base.find(x.first) == base.end() || nbase.find(x.first) == nbase.end())
                throw "RadicalExtension : Error, invalid changeBase !";
            // x.second / base[x.first] == x.nsecond / nbase[x.first]
            x.second = x.second * nbase[x.first] / base[x.first];
        }
        nvalue[nbase.encode(F)] = v.second;
    }
    base = nbase;
    value = nvalue;
}

bool operator == (RadicalExtension A, RadicalExtension B) {
    A.simp();
    B.simp();
    return A.base == B.base && A.value == B.value;
}

RadicalExtension operator + (RadicalExtension A, RadicalExtension B) {
    RadicalExtension C;
    C.base=A.base|B.base;
    A.changebase(C.base);
    B.changebase(C.base);
    for(auto &x : A.value) C.value[x.first] = C.value[x.first] + x.second;
    for(auto &x : B.value) C.value[x.first] = C.value[x.first] + x.second;
    C.simp();
    return C;
}

RadicalExtension operator - (RadicalExtension A, RadicalExtension B) {
    RadicalExtension C;
    C.base=A.base|B.base;
    A.changebase(C.base);
    B.changebase(C.base);
    for(auto &x : A.value) C.value[x.first] = C.value[x.first] + x.second;
    for(auto &x : B.value) C.value[x.first] = C.value[x.first] - x.second;
    C.simp();
    return C;
}

RadicalExtension operator * (RadicalExtension A, RadicalExtension B) {
    RadicalExtension C;
    C.base=A.base|B.base;
    A.changebase(C.base);
    B.changebase(C.base);

    for(auto i:A.value) {
    	for(auto j:B.value) {
    	    Rational res=i.second*j.second;
    		Factor F1,F2,F3;
    		F1=A.base.decode(i.first);
    		F2=B.base.decode(j.first);
    	    for(auto it=F1.begin();it!=F1.end();++it) {
    		    F3[it->first] += it->second;
    		}
    		for(auto it=F2.begin();it!=F2.end();++it) {
    		    F3[it->first] += it->second;
    		}
    		for(auto it=F3.begin();it!=F3.end();++it) {
    			ll mx = C.base.find(it->first)->second;
				if (it->second >= mx) {
					it->second -= mx;
					res = res * Rational(it->first); 
				}
    		}
    		C.value[C.base.encode(F3)] = C.value[C.base.encode(F3)] + res;
		}
    }
    C.simp();
    return C;
}

RadicalExtension operator / (RadicalExtension A, RadicalExtension B) {//A / B = X,  (B*X)_{p^{i/a}} = A_{p^{i/a}}
    A.simp();
    B.simp();
    if (A.value.empty()) return RadicalExtension(0);
    if (B.value.size() == 1) {
        Integer b(1);
        Factor F = B.base.decode(B.value.begin()->first);
        Rational v = B.value.begin()->second;
        Factor nF;
        for (auto &x : F) {
            nF[x.first] = B.base[x.first] - x.second;
            b = b * x.first;
        }
        B.value.clear();
        B.value[B.base.encode(nF)] = v / b;
        return A*B;
    }
//    A.print();  std::cout << "  /  ";  B.print();  std::cout << std::endl;

    if (B.value.empty()) throw "RadicalExtension : Error, divided by zero !";

    Base base = A.base | B.base;

    if (base.empty()) return RadicalExtension(A.value[0] / B.value[0]);

    A.changebase(base);
    B.changebase(base);

    auto now = base.begin();
    ll p = now->first, n = now->second;
    std::vector<RadicalExtension> a, b;
    std::vector<std::vector<RadicalExtension> > V;

    Base nbase = base;
    nbase.erase(nbase.find(p));

    a.resize(n);  b.resize(n);
    for (int i=0;i<n;i++) {
        a[i].changebase(nbase);
        b[i].changebase(nbase);
    }
    V.resize(n);
    for (int i=0;i<n;i++) V[i].resize(n);

    for (const auto &x : A.value) {
        Factor F = base.decode(x.first);
        int i = (F.find(p) == F.end()) ? 0 : F.find(p)->second;
        Factor nF = F;
        if (nF.find(p) != nF.end()) nF.erase(nF.find(p));
        a[i].value[nbase.encode(nF)] = x.second;
    }
    for (const auto &x : B.value) {
        Factor F = base.decode(x.first);
        int i = (F.find(p) == F.end()) ? 0 : F.find(p)->second;
        Factor nF = F;
        if (nF.find(p) != nF.end()) nF.erase(nF.find(p));
        b[i].value[nbase.encode(nF)] = x.second;
    }

//    std::cout << "A:  ";  A.print();  std::cout << std::endl;
//    std::cout << "B:  ";  B.print();  std::cout << std::endl;
//    base.print(base);  std::cout << std::endl;
//    nbase.print(nbase);  std::cout << std::endl;
//    std::cout << "a[] ";
//    for (int i=0;i<n;i++) {
//        std::cout << "   |   ";
//        a[i].print();
//    }
//    std::cout << std::endl;
//    std::cout << "b[] ";
//    for (int i=0;i<n;i++) {
//        std::cout << "   |   ";
//        b[i].print();
//    }
//    std::cout << std::endl;
//    std::cout << std::endl;

    for (int i=0;i<n;i++) for (int j=0;j<n;j++) {
        if (i+j < n) {
            //a_{i+j} += x_i * b_j
            V[i+j][i] = b[j];
        } else {
            //a_{i+j-n} += x_i * b_j * p
            V[i+j-n][i] = b[j] * RadicalExtension(p);
        }
    }
//    for (int i=0;i<n;i++) {
//        for (int j=0;j<n;j++) {
//            V[i][j].print();
//            std::cout << "   |   ";
//        }
//        std::cout << std::endl;
//    }

    std::vector<RadicalExtension> X = Algo::solve(V,a);
    RadicalExtension res(0);
    for (int i=0;i<n;i++) {
        res = res + X[i] * RadicalExtension(p,Rational(i,n));
    }

    res.simp();
    return res;
}

void RadicalExtension::simp() {
    ll now = 1;
    Base nbase;
    for (auto it = value.begin(); it != value.end(); ) {
        if (it->second == Rational(0)) it = value.erase(it);
        else ++it;
    }

    for (auto B : base) {
        ll g = 0;
        for (const auto &v : value) {
            Factor F = base.decode(v.first);
            g = Algo::gcd(g, F[B.first]);
        }
        if (g != 0) nbase[B.first] = B.second / Algo::gcd(g, B.second);
    }
    changebase(nbase);
 }

RadicalExtension::RadicalExtension() {}

RadicalExtension::RadicalExtension(ll x) {
    Factor F;
    value[base.encode(F)] = x;
}

RadicalExtension::RadicalExtension(Rational A) {//A
    Factor F;
    value[base.encode(F)] = A;
}

RadicalExtension::RadicalExtension(ll A, Rational B) {
    /*
        A^(p/q) = (a1^b1*a2^b2*...an^bn)^B
                = a1^b1B*a2^b2B*...
                = alpha * a1^b1' * a2^b2' * ...
    */
    Rational alpha(1);
    Factor F;
    std::map<ll, ll> fact = Algo::factorize(A);

    for (const auto& x : fact) {//x.fi ^ (x.se * B) = x.fi ^ tmp = 
        Rational tmp = B * Rational(x.second);
        ll m = tmp.mod().toLongLong();
        F[x.first] = tmp.p.toLongLong();
        base[x.first] = tmp.q.toLongLong();
        alpha = alpha * Algo::qpow(Rational(x.first), m);
    }

    value[base.encode(F)] = alpha;
}

RadicalExtension::RadicalExtension(Rational A, Rational B) {//(ap/aq)^B = ap^B * aq ^(-B)
    *this = RadicalExtension(A.p,B) * RadicalExtension(A.q,Rational(0)-B);
}

double RadicalExtension::getDouble() const {
    double res = 0;
    for (const auto &x : value) {
//        cout << x.second.getDouble() << " * " << base.getDouble(base.decode(x.first)) << endl;
        res += x.second.getDouble() * base.getDouble(base.decode(x.first));
    }
    return res;
}

void RadicalExtension::print() const {
    bool fi = true;
	for(const auto &x : value) {
	    if (fi) fi = false;  else std::cout << " + ";
        x.second.print();
        base.print(base.decode(x.first));
	}
}