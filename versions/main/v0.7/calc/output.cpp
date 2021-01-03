#include "output.h"

bool myTextView::init(QObject * ptr) {
    if (ptr) {
        p = ptr;
        return true;
    }
    else return false;
}

bool myTextView::setText(QString s) {
    if (p) {
        p->setProperty("text", s);
        return true;
    }
    else return false;
}
