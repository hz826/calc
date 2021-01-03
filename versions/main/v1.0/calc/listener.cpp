#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    text = "$";
}

void Listener::init_link(Renderer * pR) {
    this->pRenderer = pR;
    //this->pTextView = pT;
}

void Listener::BeforeModify() {
    qDebug() << text << endl;
}

void Listener::AfterModify() {
    qDebug() << text << endl << endl;
    pRenderer->Refresh(text);
}

void Listener::sendkey(QString key) {
    BeforeModify();
    text.replace("$",key);
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

    AfterModify();
}
