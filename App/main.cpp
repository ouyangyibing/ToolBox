#include "mainwindow.h"
#include <QApplication>
#include "myassistant.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //CommonHelper::setStyle("./style.qss");
    //CommonHelper::setStyle("E:/Study_file/QT/QT_Code/ToolBox/ToolBox/App/style.qss");

    MainWindow w;
    w.show();

    return a.exec();
}
