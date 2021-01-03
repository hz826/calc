#pragma once

#include "mainheader.h"
#include "algo.h"
#include "rational.h"

/*
    RadicalExtension����ʽ������) ��
        ������Q(2^(1/2)) = a + b*2^(1/2)
              Q(2^(1/3),5^(1/2)) = a + b*2^(1/3) + c*2^(2/3) + d*5^(1/2) + e*2^(1/3)*5^(1/2) + f*2^(2/3)*5^(1/2)

    Base����ʽ������ �Ļ�����
        ���赱ǰ ��ʽ������ Ϊ Q(p1^(1/a1), p2^(1/a2), ...) ,���� p1,p2,... Ϊ����
        ���Ϊ map{ (p1,a1), (p2,a2), ... }, ����aiΪ>1������

    Factor�����ӣ�
        ��ǰ ��ʽ������ �� ���� �ɱ�ʾΪ F = p1^(b1/a1) * p2^(b2/a2), ... ������ p1,p2,... Ϊ������biΪ [0,ai) ������
        ���� ��ʽ������ �е�ÿһ��Ԫ�� ���ɱ�ʾΪ 
            alpha1 * F1 + alpha2 * F2 + ... ������ alpha1,alpha1,...�������� ������ F1,F2,... ��������

    Ϊ���㴢�棬Base �ܽ�ͨ�� encode ���� Base �µ� Factor ת��Ϊһ���Ǹ�������ͨ�� decode ��ԭ
*/
class Factor : public std::map<ll, ll> {
};

class Base : public Factor {
private:
public:
    friend Base operator | (Base X, Base Y);

    ll encode(const Factor &F);
    Factor decode(ll x);
    double getDouble(const Factor &F);
    void print(const Factor &F);
};

class Values : public std::map<ll, Rational> {
};