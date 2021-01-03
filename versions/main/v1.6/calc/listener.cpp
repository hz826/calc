#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    text = "|";
}

void Listener::init_link(mCanvas * pP, QObject * pT) {
    pCanvas = pP;
    pTextView = new TextView(pT);
}

void Listener::BeforeModify() {
}

void Listener::AfterModify() {
    pTextView->setText("!");
    pCanvas->Refresh(text);
}

void Listener::sendkey(QString key) {
    BeforeModify();
    text.replace("|",key);
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

void Listener::test() {
    BeforeModify();
    //text = "1+\\frac{1}{2}";
    text = "1+\\frac{2+\\frac{3+\\frac{4}{5}}{6+\\frac{7}{8+\\frac{9}{10}}}}{11}";
    AfterModify();
}
