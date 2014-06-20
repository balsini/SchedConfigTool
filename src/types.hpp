#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

#include <QString>

enum scheduler_type {
  SCHED_DEADLINE,
  QoS_Feedback
};

class SchedParameter {
  bool _valid;

  scheduler_type _type;

  QString _path;
  QString _args;
  long int _deadline;
  long int _priority;
  long int _runtime;
  long int _period;
  long int _responsetime;

public:
  SchedParameter() :
    _valid(false), _priority(0) {}
  SchedParameter(long int period, long int deadline, long int runtime, QString path, QString args) :
    _valid(true),
    _type(SCHED_DEADLINE),
    _deadline(deadline),
    _priority(0),
    _runtime(runtime),
    _period(period)
  {
    _path = path;
    _args = args;
  }
  SchedParameter(long int responsetime, QString path, QString args) :
    _valid(true),
    _type(QoS_Feedback),
    _responsetime(responsetime)
  {
    _path = path;
    _args = args;
  }

  void setParam(long int period, long int deadline, long int runtime, QString path, QString args)
  {
    _valid = true;
    _type = SCHED_DEADLINE;
    _deadline = deadline;
    _runtime = runtime;
    _period = period;
    _path = path;
    _args = args;
  }

  void setParam(long int responsetime, QString path, QString args)
  {
    _valid = true;
    _type = QoS_Feedback;
    _responsetime = responsetime;
    _path = path;
    _args = args;
  }

  scheduler_type getType() const { return _type; }
  bool isValid() const { return _valid; }
  void isValid(bool valid) { _valid = valid; }

  void setType(scheduler_type type) { _type = type; }
  void setPeriod(long int period) { _period = period; }
  void setDeadline(long int deadline) { _deadline = deadline; }
  void setPriority(long int priority) { _priority = priority; }
  void setRunTime(long int runtime) { _runtime = runtime; }
  void setResponseTime(long int responsetime) { _responsetime = responsetime; }
  void setPath(QString path) { _path = path; }
  void setArgs(QString args) { _args = args; }

  long int getDeadline() const { return _deadline; }
  long int getRunTime() const { return _runtime; }
  long int getPriority() const { return _priority; }
  long int getPeriod() const { return _period; }
  long int getResponseTime() const { return _responsetime; }
  QString getPath() const { return _path; }
  QString getArgs() const { return _args; }

  friend std::ostream &operator<<(std::ostream &o, const SchedParameter &sp) {
    switch (sp.getType()) {
      case SCHED_DEADLINE:
        o << "SCHED_DEADLINE" << std::endl;
        o << "deadline: " << sp.getDeadline() << std::endl;
        o << "period: " << sp.getPeriod() << std::endl;
        o << "runtime: " << sp.getRunTime() << std::endl;
        o << "priority: " << sp.getPriority() << std::endl;
        break;
      case QoS_Feedback:
        o << "QoS_Feedback" << std::endl;
        o << "responsetime: " << sp.getResponseTime() << std::endl;
        break;
      default: break;
    }
    o << "path: " << sp.getPath().toStdString() << std::endl;
    o << "args: " << sp.getArgs().toStdString() << std::endl;
    return o;
  }
};

#endif // TYPES_HPP
