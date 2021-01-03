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

Renderer::Renderer(QString text,QPainter *painter,int defaultSize) :
    R(text), painter(painter), defaultSize(defaultSize), exception("") {}

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

void Renderer::queryText(QString s, int size, int &w, int &h) {
    if (painter == NULL) {
        qDebug() << "n_painter is NULL!" << endl;
    }
    QFont font("Microsoft YaHei", size, 0);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();

    w = metrics.horizontalAdvance(s);
    h = metrics.ascent() * Ascent_Alpha + metrics.descent() * Descent_Alpha;
}

int Renderer::getDefaultHeight(int size) {
    int w, h;
    queryText("|", size, w, h);
    return h;
}

Box* Renderer::getBox(QString s,int size) {
    int w = 0, h = 0;
    queryText(s, size, w, h);
    return new Box(s, size, w, h);
}

Box* Renderer::readFunction(int size) {//如果匹配成功则转跳
    if (R.match(QString("\\frac"))) {
        Box * up = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * dn = readBracket(lower(size), QChar('{'), QChar('}'));
        Box * now = new Box();
        if (halt) return NULL;

        now->w = Max(up->w, dn->w) + 5;
        now->hu = up->h() + 3;
        now->hd = dn->h() + 3;

        now->insert(-up->h() - 3, center(now->w, up->w) ,up);
        now->insert(          +3, center(now->w, dn->w) ,dn);
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
            Box* now = getBox(QString(R.next()), size);
            box->insert(box->w,0,now);
            box->w += now->w;
            box->hu = Max(box->hu, now->hu);
            box->hu = Max(box->hu, now->hu);
            R.getnxt();
        } else if (R.next() == QChar('\\')) {
            readFunction(size);
        } else {
            Halt("unknown char");
            return NULL;
        }
    }
    return box;
}

QString Renderer::get() {
    Box * box = read(defaultSize);
    if (!halt) {
        //print
//        QString e = ui->text_e->toPlainText();
//        QFile file("L:/qtpro/_qtApp/text/e.txt");
//        file.open(QIODevice::WriteOnly | QIODevice::Text);
//        file.write(e.toUtf8());
//        file.close();
        delete box;
    }
    return exception;
}
