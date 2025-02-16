#include "humanresourcemachine.h"
#include <QtWidgets/QApplication>
//#include <crtdbg.h>

int main(int argc, char *argv[])
{
    /*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(100000);*/

    QApplication a(argc, argv);
    humanresourcemachine w;
    w.show();
    return a.exec();
}