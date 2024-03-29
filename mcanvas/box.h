#ifndef BOX_H
#define BOX_H
#include <QString>
#include <QDebug>
#include "mpainter.h"

/* box.h
 *
 * box 是数学书写时最基本的结构，由链表（dNode）连接
 * 有4种绘画命令：TEXT, LINE, BOX, CURSOR
 * delete 时只需要delete 父节点
 * draw 命令绘制整颗子树
 *
 * 以左边中间的点(0,0)为原点
 * 左上角(0,-hu), 右下角(w,hd)
 */

class Box {
private:
    class dNode {
    public:
        dNode *nxt;

        int x, y;
        enum {TEXT, LINE, BOX, CURSOR} mode;
        union {
            struct {ushort *text;  int size;} Text;//以(x,y)为左上角绘制文字
            struct {int xx, yy;} Line;
            Box *box;
            struct {int yy;int id=0;  bool show=false;} Cursor;
        };

        dNode(int x,int y,QString text,int size);
        dNode(int x,int y,int xx,int yy);
        dNode(int x,int y,Box *box);
        dNode(int x1,int y1,int y2,int id,bool show);
        ~dNode();
    } *start;
    void insert(dNode *node);
public:
    int w, hu, hd;
    int h();
    void insert(int x1,int y1,int y2,int id,bool show);//相对坐标（内部自适应）
    void insert(int x1,int y1,int x2,int y2);//相对坐标（内部自适应）
    void insert(int x,int y,Box *box);//相对坐标（内部自适应）
    void draw(int x,int y,QPoint *cursor_pos,bool showCursor);//绝对坐标
    Box();//构造空box
    Box(QString text,int size);//构造一个只包含文字的box
    ~Box();
};

#endif // BOX_H
