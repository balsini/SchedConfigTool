#ifndef JSONMANAGER_HPP
#define JSONMANAGER_HPP

#include <QString>

#include "types.hpp"

SchedParameter parseJSONString(const QString &str);
QString constructJSONString(const SchedParameter &sp);

#endif // JSONMANAGER_HPP
