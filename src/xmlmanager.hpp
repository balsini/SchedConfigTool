#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <QString>

#include "types.hpp"

SchedParameter parseXMLString(const QString &str);
QString constructXMLString(const SchedParameter &sp);

#endif // XMLMANAGER_H
