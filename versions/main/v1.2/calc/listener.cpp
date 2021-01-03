#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    text = "$";
}

void Listener::init_link(Renderer * pR, QObject * pT) {
    this->pRenderer = pR;
    this->pTextView = new TextView(pT);
}

void Listener::BeforeModify() {
    qDebug() << text << endl;
}

void Listener::AfterModify() {
    qDebug() << text << endl << endl;
    pTextView->setText("!");
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
    text.replace("$","");
    text = "$" + text;
    AfterModify();
}

void Listener::end() {
    BeforeModify();
    text.replace("$","");
    text = text + "$";
    AfterModify();
}

void Listener::clear() {
    BeforeModify();
    text = "$";
    AfterModify();
}
//