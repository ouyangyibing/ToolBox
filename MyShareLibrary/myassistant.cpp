#include "myassistant.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>
#include <QTextStream>

bool My::readFile(const QString &name, QString &data)
{
    QFile file(name);
    if(!file.exists()) {
        return false;
    }

    if(!file.open(QFile::ReadOnly)) {
        QMessageBox::critical(NULL, "提示", QString("%1: %2").arg("读取失败", name));
        file.close();
        return false;
    }

    QTextStream in(&file);
    data = in.readAll();
    file.close();
    return true;
}

QString My::readFile(const QString &name)
{
    QString buf;
    readFile(name, buf);
    return buf;
}

bool My::writeFile(const QString &name, const QByteArray &data, const QIODevice::OpenMode flags)
{
    QFileInfo fileInfo(name);
    QString path = fileInfo.path();

    if(!QFile::exists(path)) {
        if(! QDir().mkpath(path)) {
            QMessageBox::critical(NULL, "提示", QString("%1: %2").arg("无法创建文件夹", path));
        }
    }

    QFile file(name);
    if ( !file.open(flags)) {
        QMessageBox::critical(NULL, "提示", QString("%1: %2").arg("无法创建文件", name));
    }

    QTextStream out(&file);
    out << data ;
    out.flush();
    file.close();

    return true;
}

bool My::appendFileData(const QString &name, const QByteArray &data)
{
    return writeFile(name, data, QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
}

QString My::getCurentTime(const QString &format)
{
    return QDateTime::currentDateTime().toString(format);
}
