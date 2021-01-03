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
    insert(new dNode(x,y,xx,yy));
}

void Box::insert(int x,int y,Box *box) {
    insert(new dNode(x,y,box));
}

Box::Box() : start(NULL), w(0), hu(0), hd(0) {}

Box::Box(QString text,int size,int w,int h) : start(NULL), w(w), hu(h/2), hd(h-h/2) {
    insert(new dNode(0,-hu,text,size));
}

Box::~Box() {
    while (start != NULL) {
        dNode *tmp = start->nxt;
        delete start;
        start = tmp;
    }
}
