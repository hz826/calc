#include "renderer.h"

Renderer::Reader::Reader(QString text):text(text),index(0){
    //qDebug()<<"new renderer"+text<<endl;
}

QChar Renderer::Reader:: at(int i){
    return i < text.length() ? text[i] : QChar('}');
}
QString Renderer::Reader::debug(){
    return text.left(index+1);
}

QChar Renderer::Reader::ext(){
    return at(index);
}

void Renderer::Reader::getnxt() {
    if (index < text.size()) ++index;
    //qDebug()<<text[index];
}
void Renderer::Reader::getlast() {
    if (index < text.size()) --index;
}
bool Renderer::Reader::match(QString s) {
    for (int i=0;i<s.length();i++) if (s[i] != at(index+i)) return false;
    for (int i=0;i<s.length();i++) getnxt();
    return true;
}
bool Renderer::Reader::end() {
    return index >= text.size();
}

///////////////////////////////

Renderer::Renderer(QString text,int defaultSize) : R(text), defaultSize(defaultSize) {}

int Renderer::lower(int size) {return qMax(size-2,8);}
int Renderer::difference(int w1,int w2) {
/*
  ----------------  w1
      --------      w2
  ^---^             return
*/
    return (w1-w2) / 2;
}

Box* Renderer::readFunction(int size,Box *& last) {//读汉书
    last = NULL;
    if (R.match("\\ln("))  return new Box("ln(", size);
    if (R.match("\\lg("))  return new Box("lg(", size);
    if (R.match("\\sin(")) return new Box("sin(", size);
    if (R.match("\\cos(")) return new Box("cos(", size);
    if (R.match("\\tan(")) return new Box("tan(", size);
    if (R.match("\\PI"))   return last = new Box("π",size);
    if (R.match("\\E"))    return last = new Box("e",size);
    if (R.match("\\deg"))  return new Box("°",size);

    if (R.match("\\frac")) {
        Box * up = readBracket(lower(size), '{', '}');
        Box * dn = readBracket(lower(size), '{', '}');
        Box * now = new Box();
        now->insert(2,0,qMax(up->w, dn->w)+12,0);
        now->insert(difference(now->w, up->w), -up->hd - 5, up);
        now->insert(difference(now->w, dn->w),  dn->hu + 7, dn);
        return last = now;
    }
    if (R.match("\\sqrt")){
        bool mode = false;
        if (R.ext() == 'n') {
            mode = true;
            R.getnxt();
        }
        Box*up=mode ? readBracket(8,'{', '}') : (new Box());
        Box*dn=readBracket(size,'{', '}');
        Box*now=new Box();
        const float w1=0.4;
        const float w2=0.25;
        const float w3=0.15;
        const float h1=1.1;
        const float h2=0.3;
        const float h3=0.15;
        const int h=-5;
        QPoint p1(up->w,dn->hd*(1-h3));
        QPoint p2(up->w+dn->hd*w3,dn->hd*(1-h2));
        QPoint p3(up->w+dn->hd*(w2+w3),dn->hd);
        QPoint p4(up->w+dn->hd*(w1+w2+w3),-dn->hu*h1);
        QPoint p5(up->w+dn->w+dn->hd*(w1+w2+w3),-dn->hu*h1);
        now->insert(p1.rx(),p1.ry(),p2.rx(),p2.ry());
        now->insert(p2.rx(),p2.ry(),p3.rx(),p3.ry());
        now->insert(p3.rx(),p3.ry(),p4.rx(),p4.ry()+h);
        now->insert(p4.rx(),p4.ry()+h,p5.rx(),p5.ry()+h);
        now->insert(p4.rx()-up->w-4,p4.ry()+h,up);
        now->insert(p4.rx(),0,dn);
        return last = now;
    }
    if (R.match("\\log")){
        Box*left1=new Box("log",size);
        Box*left2=new Box("(",size);
        Box*body2=readBracket(8,'{','}');
        Box*body1=readBracket(size,'{','}');

        Box*right=new Box(QString(')'),size);
        Box* now=new Box();
        now->insert(0,0,left1);
        now->insert(left1->w,body2->hu+size/2,body2);
        now->insert(left1->w+body2->w,0,left2);
        now->insert(left1->w+body2->w+left2->w+2,0,body1);
        now->insert(left1->w+body2->w+left2->w+body1->w+4,0,right);
        return last = now;
    }
    if (R.match("\\abs")){
        Box*body=readBracket(size,'{','}');
        Box*now=new Box();
        const float h=1.1;
        const int d=3;
        now->insert(d,body->hd,d,-body->hu*h);
        now->insert(2*d,0,body);
        now->insert(4*d+body->w,body->hd,4*d+body->w,-body->hu*h);
        return last = now;
    }

    else throw "unknown function";
}

Box* Renderer::readBracket(int size, QChar lc, QChar rc) {//读括弧
    if (R.ext() != lc) throw "unmatched bracket";
    else R.getnxt();

    QString rs = rc, s1 = rs, s2 = "$" + rs, s3 = "|" + rs;
    bool m1 = false, m2 = false;
    if (R.match(s1)) throw "syntax error";
    else if (R.match(s2)) m1 = true;
    else if (R.match(s3)) m2 = true;
    if (m1 || m2) {
        Box*now = new Box();
        int w, h;
        const int d=3;
        mpainter.Query("a",size,w,h);
        now->insert(d,-h/2,d+w,-h/2);
        now->insert(d,h/2,d+w,h/2);
        now->insert(d,-h/2,d,h/2);
        now->insert(d+w,-h/2,d+w,h/2);
        now->insert(d,-h/2,h/2,cursorid++,m2);
        return now;
    }
    Box* box = read(size);
    if (R.ext() != rc) throw "unmatched bracket";
    else R.getnxt();

    return box;
}

Box* Renderer::read(int size) {//读文苯
    Box* box = new Box();
    Box*last = NULL;

    while (R.ext() != '}') {
        if(R.ext() == '$' || R.ext() == '|') {
            if (box->w == 0) {
                int h = mpainter.Height(size);
                box->insert(0,-h/2,h-h/2,cursorid++,R.ext() == '|');
            }
            else box->insert(box->w,-box->hu,box->hd,cursorid++,R.ext() == '|');
            R.getnxt();
        }
        else if (R.ext() == '\\') {
            Box *now = readFunction(size, last);
            box->insert(box->w,0,now);
        }
        else if (R.ext() == '+' || R.ext() == '-' || R.ext() == '*' || R.ext() == '/') {
            Box * now = NULL;
            if (R.ext() == ('+')) now = new Box("+",size);
            else if (R.ext() == ('-')) now = new Box("-",size);
            else if (R.ext() == ('*')) now = new Box("×",size);
            else if (R.ext() == ('/')) now = new Box("÷",size);
            box->insert(box->w,0,now);
            last=NULL;
            R.getnxt();
        }
        else if(R.ext()=='^') {
            R.getnxt();
            Box*now=readBracket(10,'{','}');
            if (last==NULL) {
                last=box;
                Box*t=new Box();
                Box*tool=new Box();
                const int d=3;
                mpainter.Query("a",size,tool->w,tool->hu);
                t->insert(d,-tool->hu/2,d+tool->w,-tool->hu/2);
                t->insert(d,tool->hu/2,d+tool->w,tool->hu/2);
                t->insert(d,-tool->hu/2,d,tool->hu/2);
                t->insert(d+tool->w,-tool->hu/2,d+tool->w,tool->hu/2);
                box->insert(box->w,0,t);
               }
            box->insert(box->w,-last->hu*0.3-now->hd,now);
            last=box;
        }
        else {
            Box* now = new Box(QString(R.ext()), size);
            box->insert(box->w,0,now);
            if (R.ext() != '(') last = now;
            else last = NULL;
            R.getnxt();
        }
        //else throw "unknown char";
    }
    return box;
}

Box* Renderer::get() {
    cursorid = 0;
    Box * box = read(defaultSize);
    if (!R.end()) throw "Renderer : reader stopped abnormally";
    //qDebug() << cursorid << cursor.size() << endl;
    return box;
}
