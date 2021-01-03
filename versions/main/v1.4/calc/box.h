#ifndef BOX_H
#define BOX_H
#include <QString>
#include <QDebug>

class Box {
public:
    class dNode {
    public:
        dNode *nxt;
        int x, y;
        enum {
            TEXT, LINE, BOX
        } mode;

        union {
            struct {
                char* text;
                int size;
            } Text;
            struct {
                int xx, yy;
            } Line;
            Box *box;
        };

        dNode(int x,int y,QString text,int size);
        dNode(int x,int y,int xx,int yy);
        dNode(int x,int y,Box *box);
        ~dNode();
    } *start;

    void insert(dNode *node);
public:
    int w, hu, hd;
    int h();
    void insert(int x1,int y1,int x2,int y2);
    void insert(int x,int y,Box *box);
    Box();
    Box(QString text,int size,int w,int h);

    ~Box();
};

#endif // BOX_H
