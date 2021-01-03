#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    text = "|";
}

Listener::~Listener() {
    delete pTAnswer;
    delete pTStatus;
}

void Listener::init_link(mCanvas * pP, QObject * pT1, QObject * pT2) {
    pCanvas = pP;
    pTAnswer = new TextView(pT1);
    pTStatus = new TextView(pT2);
}

void Listener::BeforeModify() {
}

void Listener::AfterModify() {
    pTStatus->setText(text);
    pCanvas->Refresh(text);
}

void Listener::sendkey(QString key) {
    BeforeModify();
    text.replace("|",key);
    AfterModify();
}

void Listener::backspace() {
    BeforeModify();

    AfterModify();
}

void Listener::left() {
    BeforeModify();

    AfterModify();
}

void Listener::right() {
    BeforeModify();

    AfterModify();
}

void Listener::home() {
    BeforeModify();

    AfterModify();
}

void Listener::end() {
    BeforeModify();

    AfterModify();
}

void Listener::clear() {
    BeforeModify();
    text = "|";
    AfterModify();
}

void Listener::calc() {

}

void Listener::test() {
    BeforeModify();
    text="\\log{^{\\frac{\\log{123}{5}}{1+\\sqrtn{123}{45}}}}{1+\\abs{\\frac{12345}{1}\\sqrtn{\\frac{1}{2}}{\\sqrt{2}-\\frac{1}{2}}}}";
    //text="\\sqrtn{234}{2345}";
    //text="\\log{\\frac{1+2^{\\abs{\\abs{\\abs{tan(lg(sin(ln(sin(1+\\sqrt{\\frac{\\frac{1}{\\frac{1}{1}+1}}{\\frac{1}{1+\\frac{1}{1}}}})))))}}}}}{12345}";
    //text="tan(lg(sin(ln(sin(1+\\sqrt{\\frac{\\frac{1}{\\frac{1}{1}+1}}{\\frac{1}{1+\\frac{1}{1}}}})))))";
    //text="\\log{\\frac{1+\\sqrt{3}}{2}}{\\frac{1+\\sqrt{3}}{2}}";
    //text="\\log{5}{\\log{4}{\\log{2}{3}}}";

    //text="\\frac{12345}{1}\\sqrtn{\\frac{1}{2}}{\\sqrt{2}-\\frac{1}{2}}";
    //text = "1+\\sqrt{\\frac{\\frac{1}{\\frac{1}{1}+1}}{\\frac{1}{1+\\frac{1}{1}}}}";
    //text = "$1$+$\\frac{$2$+$\\frac{$3$+$\\frac{$4$}{$5$}$}{$6$+$\\frac{$7$}{$8$+$\\frac{$9$}{$1$0$}$}$}$}{$1$1$}|";
    AfterModify();
}
