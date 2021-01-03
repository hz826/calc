#include "box.h"

Box::dNode::dNode(int x,int y,QString text,int size) :
    x(x), y(y), mode(TEXT) {
    int len = text.length();
    Text.text = new ushort[len+1];
    for (int i=0;i<len;i++) Text.text[i] = text.at(i).unicode();
    Text.text[len] = 0;
    Text.size = size;
//    qDebug() << Text.text << endl;
}

Box::dNode::dNode(int x,int y,int xx,int yy) :
    x(x), y(y), mode(LINE) {
    Line.xx = xx;
    Line.yy = yy;
}

Box::dNode::dNode(int x,int y,Box * box) ://because of mode，dnode has 3 forms
    x(x), y(y), mode(BOX), box(box) {}


Box::dNode::dNode(int x1,int y1,int y2,int id,bool show):
    x(x1),y(y1),mode(CURSOR) {
    Cursor.yy = y2;
    Cursor.id = id;
    Cursor.show = show;
}

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

void Box::insert(dNode * node) {//插入node
    node->nxt = start;
    start = node;
}

void Box::insert(int x1,int y1,int y2,int id,bool show){
    insert(new dNode(x1,y1,y2,id,show));
}

void Box::insert(int x,int y,int xx,int yy) {//插入知县
    w  = qMax(w , qMax( x, xx));
    hu = qMax(hu, qMax(-y,-yy));
    hd = qMax(hd, qMax( y, yy));
    insert(new dNode(x,y,xx,yy));
}

void Box::insert(int x,int y,Box *box) {//查入box
    w  = qMax(w ,  x + box->w );//紫东跳帧边界
    hu = qMax(hu, -y + box->hu);
    hd = qMax(hd,  y + box->hd);
    insert(new dNode(x,y,box));
}

void Box::draw(int x,int y,QVector<QPoint> &cursor,bool showCursor) {//生成链表
    for (dNode *p = start; p != NULL; p = p->nxt) {
        QString text = "";
        switch (p->mode) {
            case dNode::TEXT:
                for (ushort*c=p->Text.text;*c!=0;++c) text.append(*c);
                mpainter.Text(text, p->Text.size, p->x+x, p->y+y);
                break;

            case dNode::LINE:
                mpainter.Line(p->x+x,p->y+y,p->Line.xx+x,p->Line.yy+y);
                break;

            case dNode::BOX:
                p->box->draw(p->x+x,p->y+y,cursor,showCursor);
                break;

            case dNode::CURSOR:
                //qDebug() << "size " << cursor.size() << endl;
                cursor[p->Cursor.id] = QPoint(p->x+x,(p->y+p->Cursor.yy)/2+y);
                if (showCursor && p->Cursor.show) {
                    mpainter.Line(p->x+x,p->y+y,p->x+x,p->Cursor.yy+y);
                    mpainter.Line(p->x+x+1,p->y+y,p->x+x+1,p->Cursor.yy+y);
                    mpainter.Line(p->x+x+2,p->y+y,p->x+x+2,p->Cursor.yy+y);
                    mpainter.Line(p->x+x+3,p->y+y,p->x+x+3,p->Cursor.yy+y);
                }
                break;
        }
    }
//    mpainter.Line(x,y-hu,x+w,y-hu);
//    mpainter.Line(x,y+hd,x+w,y+hd);
//    mpainter.Line(x,y-hu,x,y+hd);
//    mpainter.Line(x+w,y-hu,x+w,y+hd);
}

Box::Box() : start(NULL), w(0), hu(0), hd(0) {}

Box::Box(QString text,int size) : start(NULL) {
    //qDebug() << text << endl;
    int hh = 0;
    mpainter.Query(text, size, w, hh);//w,hh被修改城text的
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
