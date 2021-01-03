#include "expr.h"
std::map<Hash, Expr*> Expr::Expr_hashmap;

void Expr::HashInsert(Expr *p) {
    if (Expr_hashmap.find(p->getHash()) != Expr_hashmap.end()) {
        delete Expr_hashmap[p->getHash()];
    }
    Expr_hashmap[p->getHash()] = p;
}

void Expr::HashClear() {
    for (auto &x : Expr_hashmap) {
        delete x.second;
    }
    Expr_hashmap.clear();
}

Hash Expr::getHash() const {
    return hash;
}

Hash Expr::calcHash() {
    Hash tmp;

    switch (TYPE) {
        case e:
            return hash = (Num.getHash() + Hash(9320851)) * Hash(2718281);

        case pi:
            return hash = (Num.getHash() + Hash(1048932)) * Hash(31415926);

        case NUM:
            return hash = (Num.getHash() + Hash(35963049)) * Hash(20201228);

        case SUM:
//            print();
            tmp = Hash(2184019) + Num.getHash();
            for (auto &x : Sum) {
//                x.second.printtrig();  std::cout << std::endl;
//                x.second.getHash().print();  std::cout << std::endl;
                tmp = tmp + (x.first + Hash(19387)) * (x.second.getHash() + Hash(19834));
            }
//            tmp.print();
            return hash = tmp;

        case MUL:
            tmp = Hash(1295109) + Num.getHash();
            for (auto &x : Mul) {
                tmp = tmp + (x.first + Hash(189437)) * (x.second.getHash() + Hash(409603));
            }
            return hash = tmp;

        case POW:
            return hash = (Num.getHash() + Hash(818480)) * (F->getHash() + Hash(9879647)) * (F2->getHash() + Hash(811472));

        case ABS:
            return hash = (Num.getHash() + Hash(10924184)) * (F->getHash() + Hash(834530)) * (F->getHash() + Hash(181272));

        case SIN:
            return hash = (Num.getHash() + Hash(829471)) * (F->getHash() + Hash(198247)) * (F->getHash() + Hash(8172));

        case COS:
            return hash = (Num.getHash() + Hash(1243152)) * (F->getHash() + Hash(6854253)) * (F->getHash() + Hash(15463768));

        case TAN:
            return hash = (Num.getHash() + Hash(1243152)) * (F->getHash() + Hash(6854253)) * (F->getHash() + Hash(15463768));

        case LN:
            return hash = (Num.getHash() + Hash(1243152)) * (F->getHash() + Hash(6854253)) * (F->getHash() + Hash(15463768));
    }
    throw "Expr : Error, unknown TYPE";
}

Expr::Expr() : TYPE(OTHER) {}
Expr::Expr(ll R) : TYPE(NUM), Num(R) {calcHash();}
Expr::Expr(Rational R) : TYPE(NUM), Num(R) {calcHash();}
Expr::Expr(Number R) : TYPE(NUM), Num(R) {calcHash();}

Expr::Expr(Reader &R) : TYPE(NUM), Num(R.readRational()) {calcHash();}

void Expr::simp() {
    switch (TYPE) {
        case SUM:
            for (auto it = Sum.begin(); it != Sum.end(); ) {
                if (it->second == Expr::Number(0)) it = Sum.erase(it);
                else ++it;
            }
            if (Sum.size() == 0) {
                Num = 0;
                Sum.clear();
                TYPE = NUM;
            } else if (Sum.size() == 1) {
                Expr tmp = *Expr_hashmap[Sum.begin()->first];
                tmp.Num = tmp.Num * Sum.begin()->second;
                *this = tmp;
            }
            break;
        case MUL:
            for (auto it = Mul.begin(); it != Mul.end(); ) {
                if (it->second == Rational(0)) it = Mul.erase(it);
                else ++it;
            }
            if (Mul.size() == 0) {
                Mul.clear();
                TYPE = NUM;
            } else if (Mul.size() == 1 && Mul.begin()->second == 1) {
                Expr tmp = *Expr_hashmap[Mul.begin()->first];
                tmp.Num = tmp.Num * Num;
                *this = tmp;
            }
            break;
    }
    if (TYPE == SUM) {
        for (auto &x : Sum) {
            x.second = x.second * Num;
        }
        Num = 1;
    }
}

Expr Expr::add(Expr &A,Expr &B,char mode) {
    Expr C;
    C.TYPE = Expr::SUM;  C.Num = 1;

    if (A.TYPE == Expr::SUM) {
        for (auto &x : A.Sum) {
            C.Sum[x.first] = C.Sum[x.first] + x.second;
        }
    } else {
        Expr * tmp = new Expr(A);
        tmp->Num = 1;
        tmp->calcHash();
        Expr::HashInsert(tmp);
        C.Sum[tmp->getHash()] = C.Sum[tmp->getHash()] + A.Num;
    }

    if (B.TYPE == Expr::SUM) {
        for (auto &x : B.Sum) {
            if (mode == '+') C.Sum[x.first] = C.Sum[x.first] + x.second;
            else C.Sum[x.first] = C.Sum[x.first] - x.second;
        }
    } else {
        Expr * tmp = new Expr(B);
        tmp->Num = 1;
        tmp->calcHash();
        Expr::HashInsert(tmp);
        if (mode == '+') C.Sum[tmp->getHash()] = C.Sum[tmp->getHash()] + B.Num;
        else C.Sum[tmp->getHash()] = C.Sum[tmp->getHash()] - B.Num;
    }

    C.simp();
    C.calcHash();
    return C;
}

Expr Expr::mul(Expr &A,Expr &B,char mode) {
    Expr C;
    C.TYPE = Expr::MUL;  C.Num = 1;

    C.Num = C.Num * A.Num;
    if (A.TYPE == Expr::NUM) {}
    else if (A.TYPE == Expr::MUL) {
        for (auto &x : A.Mul) {
            C.Mul[x.first] = C.Mul[x.first] + x.second;
        }
    } else {
        Expr * tmp = new Expr(A);
        if (tmp->TYPE == Expr::SUM) {
            Expr::Number inv = 1 / tmp->Sum.begin()->second;
            C.Num = C.Num * tmp->Sum.begin()->second;
            for (auto &x : tmp->Sum) x.second = x.second * inv;
        } else tmp->Num = 1;
//        tmp->print();
        tmp->calcHash();
        Expr::HashInsert(tmp);
        C.Mul[tmp->getHash()] = C.Mul[tmp->getHash()] + 1;
    }

    if (mode == '*') C.Num = C.Num * B.Num;
    else C.Num = C.Num / B.Num;
    if (B.TYPE == Expr::NUM) {}
    else if (B.TYPE == Expr::MUL) {
        for (auto &x : B.Mul) {
            if (mode == '*') C.Mul[x.first] = C.Mul[x.first] + x.second;
            else C.Mul[x.first] = C.Mul[x.first] - x.second;
        }
    } else {
        Expr * tmp = new Expr(B);
        if (tmp->TYPE == Expr::SUM) {
            Expr::Number inv = 1 / tmp->Sum.begin()->second;
            if (mode == '*') C.Num = C.Num * B.Sum.begin()->second;
            else C.Num = C.Num * inv;
            for (auto &x : tmp->Sum) x.second = x.second * inv;
        } else tmp->Num = 1;
//        tmp->print();
        tmp->calcHash();
        Expr::HashInsert(tmp);
        if (mode == '*') C.Mul[tmp->getHash()] = C.Mul[tmp->getHash()] + 1;
        else C.Mul[tmp->getHash()] = C.Mul[tmp->getHash()] - 1;
    }

    C.simp();
    C.calcHash();
    return C;
}

Expr operator + (Expr A,Expr B) {return Expr::add(A,B,'+');}
Expr operator - (Expr A,Expr B) {return Expr::add(A,B,'-');}
Expr operator * (Expr A,Expr B) {return Expr::mul(A,B,'*');}
Expr operator / (Expr A,Expr B) {return Expr::mul(A,B,'/');}

Expr operator ^ (Expr A,Expr B) {
    if (B.TYPE == Expr::NUM && B.Num.isRational()) {
        if (B.Num == 0) {
            return Expr(1);
        }
        else if (B.Num == 1) {
            return A;
        }
        if (A.TYPE == Expr::MUL) {
            for (auto &x : A.Mul) {
                x.second = x.second * B.Num.toRational();
            }
            A.simp();
            return A;
        }
        else if (A.TYPE == Expr::NUM && A.Num.isRational() && A.Num.toRational().p < 100000 && A.Num.toRational().q < 100000) {
            Expr C;
            C.TYPE = Expr::NUM;
            C.Num = RadicalExtension(A.Num.toRational(), B.Num.toRational());
            C.calcHash();
            return C;
        }
        else {
            Expr C;
            C.TYPE = Expr::MUL;
            Expr * tmp = new Expr(A);

            if (tmp->Num.isRational() && tmp->Num.toRational().p < 100000 && tmp->Num.toRational().q < 100000) {
//                tmp->Num.printtrig();  std::cout << std::endl;
//                B.Num.printtrig();  std::cout << std::endl;
                C.Num = RadicalExtension(tmp->Num.toRational(), B.Num.toRational());
                tmp->Num = 1;
            }
            else C.Num = 1;

            tmp->calcHash();
            Expr::HashInsert(tmp);
            C.Mul[tmp->getHash()] = B.Num.toRational();
            return C;
        }
    }

    Expr C;
    C.Num = 1;  C.TYPE = Expr::POW;
    Expr * tmpA = new Expr(A), * tmpB = new Expr(B);
    tmpA->calcHash();  tmpB->calcHash();
    Expr::HashInsert(tmpA);  Expr::HashInsert(tmpB);
    C.F = tmpA, C.F2 = tmpB;
    return C;
}

Expr Expr::PI() {Expr E(1);  E.TYPE = pi;  E.calcHash();  return E;}
Expr Expr::E() {Expr E(1);  E.TYPE = e;  E.calcHash();  return E;}

Expr Expr::abs(Expr a) {
    Expr C;
    C.TYPE = Expr::ABS;  C.Num = 1;
    Expr * tmp = new Expr(a);
    tmp->calcHash();
    Expr::HashInsert(tmp);
    C.F = tmp;
    return C;
}

Expr Expr::sin(Expr a) {
    if (a.TYPE == pi && a.Num.isRational()) {
        Rational tmp = a.Num.toRational();
        if (tmp.q < 1000) return Expr(Trig::sin(tmp));
    }
    Expr C;
    C.TYPE = Expr::SIN;  C.Num = 1;
    Expr * tmp = new Expr(a);
    tmp->calcHash();
    Expr::HashInsert(tmp);
    C.F = tmp;
    return C;
}

Expr Expr::cos(Expr a) {
    if (a.TYPE == pi && a.Num.isRational()) {
        Rational tmp = a.Num.toRational();
        if (tmp.q < 1000) return Expr(Trig::cos(tmp));
    }
    Expr C;
    C.TYPE = Expr::COS;  C.Num = 1;
    Expr * tmp = new Expr(a);
    tmp->calcHash();
    Expr::HashInsert(tmp);
    C.F = tmp;
    return C;
}

Expr Expr::tan(Expr a) {
    if (a.TYPE == pi && a.Num.isRational()) {
        Rational tmp = a.Num.toRational();
        if (tmp.q < 1000) return Expr(Trig::tan(tmp));
    }
    Expr C;
    C.TYPE = Expr::TAN;  C.Num = 1;
    Expr * tmp = new Expr(a);
    tmp->calcHash();
    Expr::HashInsert(tmp);
    C.F = tmp;
    return C;
}

Expr Expr::ln(Expr a) {
    Expr C;
    C.TYPE = Expr::LN;  C.Num = 1;
    Expr * tmp = new Expr(a);
    tmp->calcHash();
    Expr::HashInsert(tmp);
    C.F = tmp;
    return C;
}

Expr Expr::lg(Expr a) {
    return ln(a) / ln(Expr(10));
}

Expr Expr::log(Expr a,Expr b) {
    return ln(a) / ln(b);
}

Expr Expr::sqrt(Expr a) {
    return a ^ Expr(Rational(1,2));
}

Expr Expr::sqrtn(Expr a,Expr b) {
    return a ^ (Expr(1) / b);
}

void Expr::print(std::ostream &out) const {
    bool fi = true;
    out << "Hash = ";  hash.print(out);  out << std::endl << "TYPE = ";
    switch (TYPE) {
        case e:
            out << "E" << std::endl;
            Num.printtrig(out);  out << " * E";
            break;

        case pi:
            out << "PI" << std::endl;
            Num.printtrig(out);  out << " * PI";
            break;

        case NUM:
            out << "NUM" << std::endl;
            Num.printtrig(out);  out << " * I";
            break;

        case SUM:
            out << "SUM" << std::endl;
            for (const auto &p : Sum) {
                if (fi) fi = false;
                else out << " + ";
                out << "({";  p.second.printtrig(out); out << "} * ";  out << "Expr->";  p.first.print(out);  out << ")";
            }
            break;

        case MUL:
            out << "MUL" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * ";
            for (const auto &p : Mul) {
                if (fi) fi = false;
                else out << " * ";
                out << "({";  out << "Expr->";  p.first.print(out);  out << "} ^ ";   p.second.print(out);  out << ")";
            }
            break;

        case POW:
            out << "POW" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * { ";
            out << "Expr->";  F->getHash().print(out);
            out << " ^ ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;

        case ABS:
            out << "ABS" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * abs { ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;

        case SIN:
            out << "SIN" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * sin { ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;

        case COS:
            out << "COS" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * cos { ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;

        case TAN:
            out << "TAN" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * tan { ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;

        case LN:
            out << "LN" << std::endl;
            out << "(Num = ";  Num.printtrig(out);  out << ") * LN { ";
            out << "Expr->";  F->getHash().print(out);
            out << " }";
            break;
    }
    out << std::endl << std::endl;
}

std::string Expr::toTeX() const {
    std::stringstream ss;
    std::string output;
    bool fi = true;

    if (TYPE != NUM) {
        if (!(Num == 1)) ss << Num.toTeX() << "*";
    }

    switch (TYPE) {
        case e:
            ss << "\\E";
            break;

        case pi:
            ss << "\\PI";
            break;

        case NUM:
            ss << Num.toTeX();
            break;

        case SUM:
            for (const auto &p : Sum) {
                if (fi) fi = false;
                else ss << "+";
                if (Expr_hashmap[p.first]->TYPE == NUM && Expr_hashmap[p.first]->Num == 1) {
                    ss << p.second.toTeX();
                } else if (p.second == 1) {
                    ss  << Expr_hashmap[p.first]->toTeX();
                } else ss << p.second.toTeX() << "*" << Expr_hashmap[p.first]->toTeX();
            }
            break;

        case MUL:
            for (const auto &p : Mul) {
                if (fi) fi = false;
                else ss << "*";
                if (p.second == (1)) {
                    ss << Expr_hashmap[p.first]->toTeX();
                } else ss << "(" << Expr_hashmap[p.first]->toTeX() << ")^{" << p.second.toTeX() << "}";
            }
            break;

        case POW:
            ss << "(" << F->toTeX() << ")^{" << F2->toTeX() << "}";
            break;

        case ABS:
            ss << "\\abs{" << F->toTeX() << "}";
            break;

        case SIN:
            ss << "\\sin{" << F->toTeX() << "}";
            break;

        case COS:
            ss << "\\cos{" << F->toTeX() << "}";
            break;

        case TAN:
            ss << "\\tan{" << F->toTeX() << "}";
            break;

        case LN:
            ss << "\\ln{" << F->toTeX() << "}";
            break;
    }
    ss >> output;
    return output;
}