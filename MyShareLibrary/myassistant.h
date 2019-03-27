#ifndef MYASSISTANT_H
#define MYASSISTANT_H

#include <QString>

//MyAssistant
namespace my {

bool readFile(const QString &path, QString &data);
bool writeFile(const QString &path, const QString &data);

}

#endif // MYASSISTANT_H
