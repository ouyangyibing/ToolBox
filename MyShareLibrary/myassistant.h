#ifndef MYASSISTANT_H
#define MYASSISTANT_H

#include <QFile>
#include <QString>

//MyAssistant
namespace my {

/*************
 * 获取系统时间
 ************/
QString  getCurentTime(const QString &format = "yyyy-MM-dd hh:mm:ss");

/**********************************
 * 读取文件数据
 * name: 需要读取的文件名
 * data: 引用，将读取的数据赋值于该引用
 * return: 读取成功或者失败
 *********************************/
bool readFile(const QString &name, QString &data);

/********************
 * 读取并返回读取的数据
 ********************/
QString readFile(const QString &name);

/***************
 * 写入数据至文件
 ***************/
bool writeFile(const QString &name,
               const QByteArray &data,
               const QIODevice::OpenMode flags = QIODevice::WriteOnly|QIODevice::Text);

/**************
 * 追加数据至文件
 **************/
bool appendFileData(const QString &name, const QByteArray &data);
}

#endif // MYASSISTANT_H
