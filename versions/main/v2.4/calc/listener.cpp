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

void Listener::onclick(int x,int y) {

}

void Listener::sendkey(QString key) {
    BeforeModify();
    text.replace("|",key);
    AfterModify();
}

void Listener::backspace() {
    BeforeModify();
    int index = text.indexOf("|"), pos=0;
    for (pos=index-1;pos>=0;pos--) {
        if (text[pos] == QChar('$')) break;
    }
    if (pos == -1) return ;
    QString tmp = text.mid(pos+1, index-pos-1);
    qDebug() << tmp << endl;
    if(tmp.length()==1){
        if(tmp!="}"){
        text.remove(pos,2);
        }
        else
        left();
    }
    if(tmp.length()==2){
        if(tmp=="}{"){
        left();
        }
        else if(tmp=="^{"){
        text.remove(pos+1,5);
        text.replace(pos,1,"|");
        }
        else
        text.remove(pos,3);
    }
    if(tmp.length()==3){
        text.remove(pos,4);
    }
    if(tmp.length()==4){
        text.remove(pos,5);
    }
    if(tmp.length()==5){
        if(tmp=="\\abs{"){
        text.remove(pos+1,8);
        text.replace(pos,1,"|");
        }
        else if(tmp=="\\log{"){
        text.remove(pos+1,11);
        text.replace(pos,1,"|");
        }
        else
        text.remove(pos,6);
    }
    if(tmp.length()==6){
        if(tmp=="\\frac{"){
        text.remove(pos+1,12);
        text.replace(pos,1,"|");
        }
        else
        text.remove(pos+1,9);
        text.replace(pos,1,"|");
    }
    if(tmp.length()==7){
    text.remove(pos+1,13);
    text.replace(pos,1,"|");
    }
    AfterModify();
}
void Listener::left() {
    BeforeModify();
    int index = text.indexOf("|"), pos=0;
    for (pos=index-1;pos>=0;pos--) {
        if (text[pos] == QChar('$')) break;
    }
    if (pos != -1) {
        text[pos] = QChar('|');
        text[index] = QChar('$');
    }
    AfterModify();
}

void Listener::right() {
    BeforeModify();
    int index = text.indexOf("|"), pos;

    for (pos=index+1;pos<text.length();pos++) {
        if (text[pos] == QChar('$')) break;
    }

    if (pos != text.length()) {
        text[pos] = QChar('|');
        text[index] = QChar('$');
    }
    AfterModify();
}

void Listener::home() {
    BeforeModify();
    int index = text.indexOf("|");
    if(index!=0){
        text[0] = QChar('|');
        text[index] = QChar('$');
    }
    AfterModify();
}

void Listener::end() {
    BeforeModify();
    BeforeModify();
    int index = text.indexOf("|");
    if(index+1!=text.length()){
        text[index] = QChar('$');
        text[text.length()-1] = QChar('|');
    }
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
    text="\\log{$^{$\\frac{$\\log{$1$2$3$}{$5$}}{$1$+$\\sqrtn{$1$2$3$}{$4$5$}$}$}$}{$1$+$\\abs{$\\frac{$1$2$3$4$5$}{$1$}$\\sqrtn{$\\frac{$1$}{$2$}$}{$\\sqrt{$2$}$-$\\frac{$1$}{$2$}$}$}$}|";
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
