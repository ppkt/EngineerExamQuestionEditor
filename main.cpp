#include <QtGui/QApplication>
#include "questioneditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuestionEditor w;
    w.show();

    return a.exec();
}
