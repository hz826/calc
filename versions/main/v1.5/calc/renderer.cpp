#include "renderer.h"

Renderer::Reader::Reader(QString text) : text(text), index(0) {
    qDebug() << "new renderer : " + text << endl;
}

QChar Renderer::Reader::at(int i) {
    return i < text.size() ? text[i] : QChar('`');
}

QChar Renderer::Reader::next() {
    return at(index);
}

void Renderer::Reader::getnxt() {
    if (index < text.size()) ++index;
}

bool Renderer::Reader::match(QString s) {
    for (int i=0;i<s.length();i++) if (s[i] != at(index+i)) return false;
    for (int i=0;i<s.length();i++) getnxt();
    return true;
}

///////////////////////////////

Renderer::Renderer(QString text,int defaultSize) : R(text), defaultSize(defaultSize), exception("") {}

void Renderer::Halt(QString E) {
    halt = true;
    exception = E;
}

int Renderer::Max(int x,int y) {return (x > y) ? x : y;}
int Renderer::Min(int x,int y) {return (x < y) ? x : y;}
int Renderer::lower(int size) {return Max(size-2,12);}
int Renderer::center(int w1,int w2) {
/*
  ----------------  w1
      --------      w2
      ^             return
*/
    return (w1-w2) / 2;
}

Box* Renderer::readFunction(int size) {//如果匹配成功则转跳
    if (R.match(QString("\\frac"))) {
        Box * up = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * dn = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * now = new Box();
        if (halt) return NULL;

        now->w = Max(up->w, dn->w) + 5;
        now->hu = up->h() + 3;
        now->hd = dn->h() + 7;

        now->insert(center(now->w, up->w), -up->hd - 3, up);
        now->insert(center(now->w, dn->w),  dn->hu + 7, dn);
        now->insert(0,0,now->w,0);
        return now;
    } else {
        Halt("unknown function");
        return NULL;
    }
}

Box* Renderer::readBracket(int size, QChar lc, QChar rc) {
    if (R.next() != lc) {
        Halt("unmatched bracket");
        return NULL;
    } else R.getnxt();

    Box* box = read(size);

    if (R.next() != rc) {
        Halt("unmatched bracket");
        return NULL;
    } else R.getnxt();

    return box;
}

Box* Renderer::read(int size) {
    Box* box = new Box();
    while (R.next() != QChar('`') && R.next() != '}') {
        if (halt) {
            return NULL;
        } else if (R.next() != QChar('\\')) {
            Box* now = new Box(QString(R.next()), size);
            box->insert(box->w,0,now);
            box->w += now->w;
            box->hu = Max(box->hu, now->hu);
            box->hd = Max(box->hd, now->hd);
            R.getnxt();
        } else if (R.next() == QChar('\\')) {
            Box * now = readFunction(size);
            box->insert(box->w,0,now);
            box->w += now->w;
            box->hu = Max(box->hu, now->hu);
            box->hd = Max(box->hd, now->hd);
        } else {
            Halt("unknown char");
            return NULL;
        }
    }
    return box;
}

QString Renderer::get(int x,int y) {
//    Box *q = new Box(painter,"hello",20);
//    Box *p = new Box();
//    p->insert(0,0,q);
//    p->insert(0,-30,100,30);
//    p->draw(painter,x,y);

    Box * box = read(defaultSize);
    qDebug() << box->w << " " << box->h() << endl;
    if (!halt) {
        box->draw(x,y);
//        QString e = ui->text_e->toPlainText();
//        QFile file("L:/qtpro/_qtApp/text/e.txt");
//        file.open(QIODevice::WriteOnly | QIODevice::Text);
//        file.write(e.toUtf8());
//        file.close();
        delete box;
    }
    return exception;
}