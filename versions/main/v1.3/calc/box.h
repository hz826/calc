#ifndef BOX_H
#define BOX_H
#include <QString>

class Box {
private:
    class dNode {
    public:
        dNode *nxt;
        int x, y;
        enum {
            TEXT, LINE, BOX
        } mode;

        union {
            struct {
                QString text;
                int size;
            } Text;
            struct {
                int xx, yy;
            } Line;
            Box * box;
        };

        dNode(int x,int y,QString text,int size);
        dNode(int x,int y,int xx,int yy);
        dNode(int x,int y,Box * box);
    } *start;

public:
    int w, h;
    void insert(dNode * node);
    void insert(int x1,int y1,int x2,int y2);
    void insert(int x,int y,Box *box);
    Box();
    Box(QString text,int size,int w,int h);
};

#endif // BOX_H
