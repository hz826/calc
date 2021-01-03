#include "box.h"

Box::dNode::dNode(int x,int y,QString text,int size) :
    x(x), y(y), mode(TEXT) {
    int len = text.length();
    Text.text = new char[len+1];
    for (int i=0;i<len;i++) Text.text[i] = text.at(i).toLatin1();
    Text.text[len] = '\0';
    Text.size = size;
    qDebug() << Text.text << endl;
}

Box::dNode::dNode(int x,int y,int xx,int yy) :
    x(x), y(y), mode(LINE) {
    Line.xx = xx;
    Line.yy = yy;
}

Box::dNode::dNode(int x,int y,Box * box) :
    x(x), y(y), mode(BOX), box(box) {}

Box::dNode::~dNode() {
    switch (mode) {
        case TEXT:
            if (Text.text != NULL) delete [] Text.text;
            break;
        case BOX:
            if (box != NULL) delete box;
            break;
        default:
            break;
    }
}

int Box::h() {return hu + hd;}

void Box::insert(dNode * node) {
    node->nxt = start;
    start = node;
}

void Box::insert(int x,int y,int xx,int yy) {
    w  = qMax(w , qMax( x, xx));
    hu = qMax(hu, qMax(-y,-yy));
    hd = qMax(hd, qMax( y, yy));
    insert(new dNode(x,y,xx,yy));
}

void Box::insert(int x,int y,Box *box) {
    w  = qMax(w ,  x + box->w );
    hu = qMax(hu, -y + box->hu);
    hd = qMax(hd,  y + box->hd);
    insert(new dNode(x,y,box));
}

void Box::draw(int x,int y) {
    for (dNode *p = start; p != NULL; p = p->nxt) {
        switch (p->mode) {
            case dNode::TEXT:
                mpainter.Text(p->Text.text, p->Text.size, p->x+x, p->y+y);
                break;

            case dNode::LINE:
                mpainter.Line(p->x+x,p->y+y,p->Line.xx+x,p->Line.yy+y);
                break;

            case dNode::BOX:
                p->box->draw(p->x+x,p->y+y);
                break;

            case dNode::CURSOR:
                break;
        }
    }
}

Box::Box() : start(NULL), w(0), hu(0), hd(0) {}

Box::Box(QString text,int size) : start(NULL) {
    int hh = 0;
    mpainter.Query(text, size, w, hh);
    hd = hh / 2;
    hu = hh - hd;
    insert(new dNode(0,-hu,text,size));
}

Box::~Box() {
    while (start != NULL) {
        dNode *tmp = start->nxt;
        delete start;
        start = tmp;
    }
}
