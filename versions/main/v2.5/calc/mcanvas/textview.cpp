#include "textview.h"

TextView::TextView(QObject * p) : text(p) {
}

void TextView::setText(QString s) {
    text->setProperty("text",s);
}
