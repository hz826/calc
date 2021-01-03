#include "listener.h"

int Listener::Select(int x){
    int z=0;
    while(x+1<text.size()&&z!=-1){
        if(text[x+1]==QChar('{')){
          z++;
        }
        if(text[x+1]==QChar('}')){
          z--;
        }
        x++;
    };
    return x;
}

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    text = "|";
}

void Listener::init_link(mCanvas * pP) {
    pCanvas = pP;
    AfterModify();
}

void Listener::BeforeModify() {
}

void Listener::AfterModify() {
    pCanvas->Refresh(text,"","");
}

void Listener::onclick(int x,int y) {
    BeforeModify();
//    qDebug() << "onclick (" << x << "," << y << ")"  << endl;
    if (pCanvas->mode != mCanvas::FREE) return;
    pCanvas->mode = mCanvas::READ;

    int n = pCanvas->cursor_num;
    QPoint *c = pCanvas->cursor_pos;

    int d = 1<<30, pos = -1;
    for (int i=0;i<n;i++) {
        int nd = (c[i].x()-x)*(c[i].x()-x) + (c[i].y()-y)*(c[i].y()-y);
        if (nd < d) {
            pos = i;
            d = nd;
        }
    }
    if (pos == -1) qDebug() << "Listener : Error! Can't find any cursor" << endl;

    text.replace("|","$");

    for (int i=0;i<text.length();i++) if (text[i] == '$') {
        if (pos == 0) {
            text[i] = '|';
            break;
        } else --pos;
    }
    if (pos > 0) qDebug() << "Listener : Error! Can't find the corresponding cursor" << endl;
    pCanvas->mode = mCanvas::FREE;
    AfterModify();
}

void Listener::up() {
    BeforeModify();

    if (pCanvas->mode != mCanvas::FREE) return;
    pCanvas->mode = mCanvas::READ;

    QPoint *c = pCanvas->cursor_pos;

    int x, y, l = -1, r = -1, index = 0, id = 0;
    int d = 1<<30, pos = -1;

    for (int i=0;i<text.size();i++) {
        if (text[i] == '|') {
            index = i;
            break;
        }
        if (text[i] == '$') ++id;
    }
    x = c[id].x(), y = c[id].y();

    for (int i=index;i>=0;i--) {
        if (text.mid(i,6) == "\\frac{") {
            int l1 = i+5, r1 = Select(l1), l2 = r1+1, r2 = Select(l2);
            if (l2 <= index && index <= r2) {
                l = l1, r = r1;
                break;
            }
        }
    }
    if (l == -1) {
        pCanvas->mode = mCanvas::FREE;
        return ;
    }

    text.replace("|","$");
    for (int i=0,j=0;i<text.size();i++) {
        if (text[i] == '$') {
            if (l <= i && i <= r) {
                int nd = (c[j].x()-x)*(c[j].x()-x) + (c[j].y()-y)*(c[j].y()-y);
                if (nd < d) {
                    pos = j;
                    d = nd;
                }
            }
            ++j;
        }
    }

    for (int i=0;i<text.length();i++) if (text[i] == '$') {
        if (pos == 0) {
            text[i] = '|';
            break;
        } else --pos;
    }
    pCanvas->mode = mCanvas::FREE;
    AfterModify();
}

void Listener::down() {
    BeforeModify();

    if (pCanvas->mode != mCanvas::FREE) return;
    pCanvas->mode = mCanvas::READ;

    QPoint *c = pCanvas->cursor_pos;

    int x, y, l = -1, r = -1, index = 0, id = 0;
    int d = 1<<30, pos = -1;

    for (int i=0;i<text.size();i++) {
        if (text[i] == '|') {
            index = i;
            break;
        }
        if (text[i] == '$') ++id;
    }
    x = c[id].x(), y = c[id].y();

    for (int i=index;i>=0;i--) {
        if (text.mid(i,6) == "\\frac{") {
            int l1 = i+5, r1 = Select(l1), l2 = r1+1, r2 = Select(l2);
            if (l1 <= index && index <= r1) {
                l = l2, r = r2;
                break;
            }
        }
    }
    if (l == -1) {
        pCanvas->mode = mCanvas::FREE;
        return ;
    }

    text.replace("|","$");
    for (int i=0,j=0;i<text.size();i++) {
        if (text[i] == '$') {
            if (l <= i && i <= r) {
                int nd = (c[j].x()-x)*(c[j].x()-x) + (c[j].y()-y)*(c[j].y()-y);
                if (nd < d) {
                    pos = j;
                    d = nd;
                }
            }
            ++j;
        }
    }

    for (int i=0;i<text.length();i++) if (text[i] == '$') {
        if (pos == 0) {
            text[i] = '|';
            break;
        } else --pos;
    }
    pCanvas->mode = mCanvas::FREE;
    AfterModify();
}

void Listener::sendkey(QString key) {
    BeforeModify();
    text.replace("|",key);
    AfterModify();
}

void Listener::backspace() {
    BeforeModify();
    int index = text.indexOf("|"), pos=0;
    QString tmp1=text.mid(index+1,2);
    for (pos=index-1;pos>=0;pos--) {
        if (text[pos] == QChar('$')) break;
    }
    if (pos == -1) {
        if (text != "|") {
            right();
            backspace();
        }
        /*if(tmp1=="^{"){
            int a=Listener::Select(index+3);
            text.remove(a,2);
            text.replace(index+3,1,'|');
            text.remove(index,3);
        }*/
        return;
    }
    QString tmp = text.mid(pos+1, index-pos-1);
    qDebug() << tmp << endl;
    if(tmp.length()==1){
        if(tmp1=="^{"){
            if(tmp==QChar('*')||tmp==QChar('/')||tmp==QChar('+')||tmp==QChar('-')||tmp==QChar('(')||tmp==QChar(')')){
                int a=Listener::Select(index+3);
                text.remove(a,2);
                text.replace(index+3,1,'|');
                text.remove(index,3);
            }
            else text.remove(pos,2);
        }
        else if(tmp!="}"){
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
            int a=Listener::Select(index);
            text.remove(a,2);
            text.remove(pos,index-pos);
        }
        else
            text.remove(pos,3);
    }
    if(tmp.length()==3){
            text.remove(pos,4);
    }
    if(tmp.length()==4){
        if(tmp1=="^{"){
            int a=Listener::Select(index+3);
            text.remove(a,2);
            text.replace(index+3,1,'|');
            text.remove(index,3);
        }
        if(tmp1!="^{"){
            text.remove(pos,5);
        }
    }
    if(tmp.length()==5){
        if(tmp1=="^{"){
            int a=Listener::Select(index+3);
            text.remove(a,2);
            text.replace(index+3,1,'|');
            text.remove(index,3);
        }
        if(tmp1!="^{"){
            if(tmp=="\\log{") {
                //'$\log{|}{$}$';
                int a=Listener::Select(index);
                int b=Listener::Select(a+2);
                text.remove(b,2);
                text.replace(a+2,1,"|");
                text.remove(pos,a-pos+2);
            }
            else if(tmp=="\\abs{"){
                text.remove(Listener::Select(index),2);
                text.remove(pos,index-pos);
            }
            else
                text.remove(pos,6);
        }
    }
    if(tmp.length()==6){
        if(tmp=="\\frac{"){
            QString tmp = text.mid(index+1, 1);
            if(tmp!='}'){
                Listener::right();
                Listener::backspace();
            }
            if(tmp=='}'){
                int a=Listener::Select(index);
                int b=Listener::Select(a+2);
                text.remove(b,2);
                text.replace(a+2,1,"|");
                text.remove(pos,a-pos+2);
            }
        }
        if(tmp=="\\sqrt{"){
            if(tmp1=="^{"){
                int a=Listener::Select(index+3);
                text.remove(a,2);
                text.replace(index+3,1,'|');
                text.remove(index,3);
            }
            if(tmp1!="^{"){
                text.remove(Listener::Select(index),2);
                text.remove(pos,index-pos);
            }
        }
    }
    if(tmp.length()==7){
        if(tmp1=="^{"){
            int a=Listener::Select(index+3);
            text.remove(a,2);
            text.replace(index+3,1,'|');
            text.remove(index,3);
        }
        if(tmp1!="^{"){
            int a=Listener::Select(index);
            int b=Listener::Select(a+2);
            text.remove(b,2);
            text.replace(a+2,1,"|");
            text.remove(pos,a-pos+2);
        }
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
    QString ctext = text;
    ctext.replace("$","");
    ctext.replace("|","");
    ctext.replace("\\deg","*\\PI/180");

    try {
        Number numerical_ans = Calc<Number>(ctext).get();
        QString ans = QString("≈") + QString::number(numerical_ans.v,10,5);
        pCanvas->Refresh(text, "", ans);
    } catch (const char *s) {
        pCanvas->Refresh(text, "", s);
    }
}

void Listener::test() {
    BeforeModify();
    text="$\\log{$^{$\\frac{$\\log{$1$2$3$}{$5$}}{$1$+$\\sqrtn{$1$2$3$}{$4$5$}$}$}$}{$1$+$\\abs{$\\frac{$1$2$3$4$5$}{$1$}$\\sqrtn{$\\frac{$1$}{$2$}$}{$\\sqrt{$2$}$-$\\frac{$1$}{$2$}$}$}$}|";
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
