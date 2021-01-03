#include "renderer.h"

Renderer::Reader::Reader(QString text):text(text),index(0){
    qDebug()<<"new renderer"+text<<endl;
}

QChar Renderer::Reader:: at(int i){
    return i<text.length()?text[i]:QChar('}');
}
QString Renderer::Reader::debug(){
    return text.left(index+1);
}

QChar Renderer::Reader::ext(){
    return at(index);
}

void Renderer::Reader::getnxt() {
    if (index < text.size()) ++index;
    qDebug()<<text[index];
}
void Renderer::Reader::getlast() {
    if (index < text.size()) --index;
}
bool Renderer::Reader::match(QString s) {
    for (int i=0;i<s.length();i++) if (s[i] != at(index+i)) return false;
    for (int i=0;i<s.length();i++) getnxt();
    return true;
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

Box* Renderer::readFunction(int size) {//读汉书
    if (R.match("\\ln("))  return new Box("ln(", size);
    if (R.match("\\lg("))  return new Box("lg(", size);
    if (R.match("\\sin(")) return new Box("sin(", size);
    if (R.match("\\cos(")) return new Box("cos(", size);
    if (R.match("\\tan(")) return new Box("tan(", size);
    if (R.match("\\PI"))   return new Box("π",size);
    if (R.match("\\E"))    return new Box("e",size);
    if (R.match("\\deg"))  return new Box("°",size);
    if (R.match("\\frac")) {
        Box * up = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * dn = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * now = new Box();
        now->insert(2,0,qMax(up->w, dn->w)+12,0);
        now->insert(difference(now->w, up->w), -up->hd - 5, up);
        now->insert(difference(now->w, dn->w),  dn->hu + 7, dn);
        return now;
    }

    if (R.match("\\sqrt")){
        bool mode = false;
        if (R.ext() == QChar('n')) {
            mode = true;
            R.getnxt();
}
        Box*dn=readBracket(size,QChar('{'), QChar('}'));

        Box*up=mode ? readBracket(8,QChar('{'), QChar('}')) : (new Box());
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
        return now;
    }
    if (R.match("\\log")){
        Box*left1=new Box("log",size);
        Box*left2=new Box("(",size);

        Box*body1=readBracket(size,QChar('{'),QChar('}'));
        Box*body2=readBracket(8,QChar('{'),QChar('}'));
        Box*right=new Box(QString(')'),size);
        Box* now=new Box();
        now->insert(0,0,left1);
        now->insert(left1->w,body2->hu+size/2,body2);
        now->insert(left1->w+body2->w,0,left2);
        now->insert(left1->w+body2->w+left2->w+2,0,body1);
        now->insert(left1->w+body2->w+left2->w+body1->w+4,0,right);
        return now;
    }
    if (R.match("\\abs")){
        Box*body=readBracket(size,QChar('{'),QChar('}'));
        Box*now=new Box();
        const float h=1.1;
        const int d=3;
        now->insert(d,body->hd,d,-body->hu*h);
        now->insert(2*d,0,body);
        now->insert(4*d+body->w,body->hd,4*d+body->w,-body->hu*h);
        return now;
    }

    else throw "unknown function";
}

Box* Renderer::readBracket(int size, QChar lc, QChar rc) {//读括弧
    if (R.match("{}")||R.match("{$}")){
        Box*now=new Box();
        Box*tool=new Box();
        const int d=3;
        mpainter.Query("a",size,tool->w,tool->hu);
        now->insert(d,-tool->hu/2,d+tool->w,-tool->hu/2);
        now->insert(d,tool->hu/2,d+tool->w,tool->hu/2);
        now->insert(d,-tool->hu/2,d,tool->hu/2);
        now->insert(d+tool->w,-tool->hu/2,d+tool->w,tool->hu/2);
        return now;
    }
    if (R.match("{|}")){
        Box*now=new Box();
        Box*tool=new Box();
        const int d=3;
        mpainter.Query("a",size,tool->w,tool->hu);
        now->insert(d,-tool->hu/2,d+tool->w,-tool->hu/2);
        now->insert(d,tool->hu/2,d+tool->w,tool->hu/2);
        now->insert(d,-tool->hu/2,d,tool->hu/2);
        now->insert(d+tool->w,-tool->hu/2,d+tool->w,tool->hu/2);
        now->insert(d,-tool->hu/2,tool->hu/2,1,true);
        return now;
    }

    if (R.ext() != lc) throw "unmatched bracket";
    else R.getnxt();
    Box* box = read(size);
    if (R.ext() != rc) throw "unmatched bracket";
    else R.getnxt();

    return box;
}

Box* Renderer::read(int size) {//读文苯
    Box* box = new Box();
    Box*last=NULL;

    while (R.ext() != QChar('}')) {
        if(R.ext() == '$' || R.ext() == '|') {
            if(R.ext()=='|') {
                if(box->w==0) box->insert(0,-13,13,1,true);
                    box->insert(box->w,-box->hu,box->hd,1,true);
            }
            R.getnxt();
        }
        else if (R.ext() == QChar('\\') ) {
            Box *now = readFunction(size);
            box->insert(box->w,0,now);
            last=now;
        }
        else if (R.ext() == QChar('+') || R.ext() == QChar('-') || R.ext() == QChar('*') || R.ext() == QChar('/')) {
            Box * now = NULL;
            if (R.ext() == QChar('+')) now = new Box("+",size);
            else if (R.ext() == QChar('-')) now = new Box("-",size);
            else if (R.ext() == QChar('*')) now = new Box("×",size);
            else if (R.ext() == QChar('/')) now = new Box("÷",size);
            box->insert(box->w,0,now);
            last=NULL;
            R.getnxt();
        }
        else if(R.ext()==QChar('^')){
            R.getnxt();
            Box*now=readBracket(10,QChar('{'),QChar('}'));
            if(last==NULL) {
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
            R.getnxt();
            last=now;
        }
        //else throw "unknown char";
    }
    return box;
}

void Renderer::get(int x,int y,QVector<QPoint> &cursor,bool showCursor) {
    Box * box = read(defaultSize);
    box->draw(x,y,showCursor);
    delete box;
}
