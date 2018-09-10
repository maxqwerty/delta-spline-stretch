#include "widget.h"
#include "patharea.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Widget w;
//    w.show();

    PathArea area;
    area.show();

    return a.exec();
}
