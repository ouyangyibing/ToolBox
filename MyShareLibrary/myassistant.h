#ifndef MYASSISTANT_H
#define MYASSISTANT_H

#include <QFile>
#include <QString>

//MyAssistant
namespace My {

/*
 * func: 获取系统时间
 * format: 时间格式
 * return: 返回对应格式的系统时间字符串
 */
QString  getCurentTime(const QString &format = "yyyy-MM-dd hh:mm:ss");

/*
 * func: 读取文件数据
 * name: 待读取的文件路径名
 * data: 引用，将读取的数据赋值于该引用
 * return: 读取成功返回 true， 失败返回 false
 */
bool readFile(const QString &name, QString &data);

/*
 * func: 读取文件数据
 * name: 待读取的文件路径名
 * return: 返回读取出来的数据
 */
QString readFile(const QString &name);

/*
 * func: 写入数据至文件，当路径或文件不存在时，自动创建
 * name: 待写入的文件路径名
 * data: 待写入的数据
 * flags: 文件打开方式
 * return: 写入成功返回true， 失败返回 false
 */
bool writeFile(const QString &name,
               const QByteArray &data,
               const QIODevice::OpenMode flags = QIODevice::WriteOnly|QIODevice::Text);

/*
 * func: 追加数据至文件，当路径或文件不存在时，自动创建
 * name: 待写入的文件路径名
 * data: 待写入的数据
 * return: 写入成功返回true， 失败返回 false
 */
bool appendFileData(const QString &name, const QByteArray &data);
}

#endif // MYASSISTANT_H
