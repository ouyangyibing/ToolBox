#include "myassistant.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

bool my::readFile(const QString &path, QString &data)
{
    QFile file(path);
    if(!file.exists()) {
        return false;
    }

    if(!file.open(QFile::ReadOnly)) {
        file.close();
        return false;
    }

    QTextStream in(&file);
    data = in.readAll();
    file.close();
    return true;
}
/*
QString sFilePath = "C:\\test.txt";

QFile file(sFilePath);
//方式：Append为追加，WriteOnly，ReadOnly
if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
    QMessageBox::critical(NULL, "提示", "无法创建文件");
    return -1;
}
QTextStream out(&file);
out<<"要写入内容"<<endl;
out.flush();
file.close();

//注意写入方式的选择，注意写完后的关闭操作！
*/

bool my::writeFile(const QString &path, const QString &data)
{

}
