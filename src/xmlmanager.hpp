#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <QString>

#include "types.hpp"

ExperimentParameter parseXMLString(const QString &str);
QString constructXMLString(const ExperimentParameter &sp);

#endif // XMLMANAGER_H
