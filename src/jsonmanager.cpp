#include "jsonmanager.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

SchedParameter parseJSONString(const QString &str)
{
  SchedParameter sp;

  QJsonDocument stream = QJsonDocument::fromJson(str.toUtf8());
  QJsonObject jsonObjMain = stream.object();
  QJsonValue jsonValMain = jsonObjMain.value(QString("main"));
  QJsonObject item = jsonValMain.toObject();

  if (item.value("policy") != QJsonValue::Undefined) {
    if (item.value("policy").toString() == "SCHED_DEADLINE") {
      bool setPeriod = false;
      bool setDeadline = false;
      bool setRunTime = false;
      bool setPriority = false;
      bool setPath = false;
      bool setArgs = false;

      sp.setType(SCHED_DEADLINE);

      if (item.value("deadline") != QJsonValue::Undefined ) {
        sp.setDeadline(item.value("deadline").toInt());
        setDeadline = true;
      }
      if (item.value("period") != QJsonValue::Undefined ) {
        sp.setPeriod(item.value("period").toInt());
        setPeriod = true;
      }
      if (item.value("runtime") != QJsonValue::Undefined ) {
        sp.setRunTime(item.value("runtime").toInt());
        setRunTime = true;
      }
      if (item.value("priority") != QJsonValue::Undefined ) {
        sp.setPriority(item.value("priority").toInt());
        setPriority = true;
      }
      if (item.value("path") != QJsonValue::Undefined ) {
        sp.setPath(item.value("path").toString());
        setPath = true;
      }
      if (item.value("args") != QJsonValue::Undefined ) {
        sp.setArgs(item.value("args").toString());
        setArgs = true;
      }

      if (!setPeriod)
        sp.setPeriod(0);
      if (!setDeadline)
        sp.setDeadline(0);
      if (!setRunTime)
        sp.setRunTime(0);
      if (!setPriority)
        sp.setPriority(0);
      if (!setPath)
        sp.setPath("");
      if (!setArgs)
        sp.setArgs("");

      sp.isValid(true);

    } else if (item.value("policy").toString() == "QoS_Feedback") {
      bool setResponseTime = false;
      bool setPath = false;
      bool setArgs = false;

      sp.setType(QoS_Feedback);

      if (item.value("responsetime") != QJsonValue::Undefined ) {
        sp.setResponseTime(item.value("responsetime").toInt());
        setResponseTime = true;
      }
      if (item.value("path") != QJsonValue::Undefined ) {
        sp.setPath(item.value("path").toString());
        setPath = true;
      }
      if (item.value("args") != QJsonValue::Undefined ) {
        sp.setArgs(item.value("args").toString());
        setArgs = true;
      }

      if (!setResponseTime)
        sp.setResponseTime(0);
      if (!setPath)
        sp.setPath("");
      if (!setArgs)
        sp.setArgs("");

      sp.isValid(true);
    }
  }
  return sp;
}

QString constructJSONString(const SchedParameter &sp)
{
  QJsonDocument stream;
  QJsonObject jsonObjMain;
  QJsonObject jsonObj;

  switch (sp.getType()) {
    case SCHED_DEADLINE:
      jsonObj.insert("period", QJsonValue((int)sp.getPeriod()));
      jsonObj.insert("deadline", QJsonValue((int)sp.getDeadline()));
      jsonObj.insert("runtime", QJsonValue((int)sp.getRunTime()));
      jsonObj.insert("priority", QJsonValue((int)sp.getPriority()));

      if (sp.getPath().length() > 0) {
        jsonObj.insert("path", QJsonValue(sp.getPath()));
        jsonObj.insert("args", QJsonValue(sp.getArgs()));
      }

      jsonObj.insert("policy", QString("SCHED_DEADLINE"));
      break;
    case QoS_Feedback:
      jsonObj.insert("responsetime", QJsonValue((int)sp.getResponseTime()));

      if (sp.getPath().length() > 0) {
        jsonObj.insert("path", QJsonValue(sp.getPath()));
        jsonObj.insert("args", QJsonValue(sp.getArgs()));
      }

      jsonObj.insert("policy", QString("QoS_Feedback"));
      break;
    default: break;
  }

  jsonObjMain.insert("main", jsonObj);
  stream.setObject(jsonObjMain);

  return stream.toJson();
}

