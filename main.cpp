#include <QApplication>
#include "board.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    Board w;
    w.show();


    return app.exec();
}
