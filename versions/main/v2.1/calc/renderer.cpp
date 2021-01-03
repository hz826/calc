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

Renderer::Renderer(QString text,int defaultSize) : R(text), defaultSize(defaultSize) {}

int Renderer::lower(int size) {return qMax(size-2,12);}
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
        now->insert(0,0,qMax(up->w, dn->w)+2,0);
        now->insert(center(now->w, up->w), -up->hd - 3, up);
        now->insert(center(now->w, dn->w),  dn->hu + 7, dn);
        return now;
    } else {
        throw "unknown function";
    }
}

Box* Renderer::readBracket(int size, QChar lc, QChar rc) {
    if (R.next() != lc) throw "unmatched bracket";
    else R.getnxt();

    Box* box = read(size);

    if (R.next() != rc) throw "unmatched bracket";
    else R.getnxt();

    return box;
}

Box* Renderer::read(int size) {
    Box* box = new Box();
    while (R.next() != QChar('`') && R.next() != QChar('}')) {
        if(R.next() == '$' || R.next() == '|') {
            R.getnxt();
        }
        else if (R.next() != QChar('\\')) {
            Box* now = new Box(QString(R.next()), size);
            box->insert(box->w,0,now);
            R.getnxt();
        }
        else if (R.next() == QChar('\\')) {
            Box * now = readFunction(size);
            box->insert(box->w,0,now);
        }
        else throw "unknown char";
    }
    return box;
}

void Renderer::get(int x,int y) {
    Box * box = read(defaultSize);

    qDebug() << box->w << " " << box->h() << endl;
    box->draw(x,y);
    delete box;
}
