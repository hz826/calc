#include "factor.h"

Base operator | (Base X, Base Y) {
    Base Z;
    auto i = X.begin(), j = Y.begin();
    while (i != X.end() || j != Y.end()) {
        if (j == Y.end()) { Z[i->first] = i->second;  ++i; }
        else if (i == X.end()) { Z[j->first] = j->second;  ++j; }

        else if (i->first < j->first) { Z[i->first] = i->second;  ++i; }
        else if (i->first > j->first) { Z[j->first] = j->second;  ++j; }
        else { Z[i->first] = Algo::lcm(i->second, j->second);  ++i;  ++j; }
    }
    return Z;
}

ll Base::encode(const Factor &F) const {
    ll res = 0;
    for (auto it = begin(); it != end(); ++it) {
        auto itt = F.find(it->first);
        if (itt == F.end()) res = res * it->second;
        else {
            if (itt->second >= it->second) throw "invalid Factor";
            res = res * it->second + itt->second;
        }
    }
    return res;
}

Factor Base::decode(ll x) const {
    Factor F;
    for (auto it = rbegin(); it != rend(); ++it) {
        ll tmp = x % it->second;
        x /= it->second;
        if (tmp > 0) F[it->first] = tmp;
    }
    if (x) throw "invalid Factor";
    return F;
}

double Base::getDouble(const Factor &F) const {
    double res = 1.0;
    for (const auto &x : F) {
        auto it = find(x.first);
        if (it == end()) throw "invalid Factor";
        res *= std::pow(x.first, 1.0 * x.second / it->second);
    }
    return res;
}

void Base::print(std::ostream &out,const Factor &F) const {
    for (const auto &x : F) {
        auto it = find(x.first);
        if (it == end()) throw "invalid Factor";
        out << "*" << x.first << "^{" << x.second << "/" << it->second << "}";
    }
}

std::string Base::toTeX(const Factor &F) const {
    if (F.empty()) return "";
    std::stringstream ss;
    std::string output;
    std::map<Rational,Integer> tmp;
    for (auto &x : F) {
        auto it = find(x.first);
        if (tmp[Rational(x.second,it->second)] == 0) tmp[Rational(x.second,it->second)] = 1;
        tmp[Rational(x.second,it->second)] = tmp[Rational(x.second,it->second)] * x.first;
    }
    bool flag = true;
    for (auto &x : *this) if (x.second > 2) flag = false;

    if (flag) {
        if (tmp.size() != 1) throw "Factor : toTeX Error";
        if (tmp.begin()->first == Rational(1,2)) {
            ss << "*\\sqrt{" << tmp.begin()->second << "}";
        } else throw "Factor : toTeX Error";
    } else {
        for (auto &x : tmp) {
            ss << "*" << x.second << "^{" << x.first.toTeX() << "}";
        }
    }
    ss >> output;
    return output;
}
