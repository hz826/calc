#include "box.h"

Box::dNode::dNode(int x,int y,QString text,int size) :
    x(x), y(y), mode(TEXT) {
    Text.text = text;
    Text.size = size;
}

Box::dNode::dNode(int x,int y,int xx,int yy) :
    x(x), y(y), mode(LINE) {
    Line.xx = xx;
    Line.yy = yy;
}

Box::dNode::dNode(int x,int y,Box * box) :
    x(x), y(y), mode(BOX), box(box) {}


void Box::insert(dNode * node) {
    start->nxt = node;
    start = node;
}

void Box::insert(int x,int y,int xx,int yy) {
    insert(new dNode(x,y,xx,yy));
}

void Box::insert(int x,int y,Box *box) {
    insert(new dNode(x,y,box));
}

Box::Box() : start(NULL), w(0), h(0) {}

Box::Box(QString text,int size,int w,int h) : start(NULL), w(w), h(h) {
    insert(new dNode(0,-h/2,text,size));
}
