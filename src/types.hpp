#ifndef TYPES_HPP
#define TYPES_HPP


enum scheduler_type {
  SCHED_DEADLINE,
  QoS_Feedback
};

class SchedParameter {
  bool _valid;

  scheduler_type _type;

  long int _deadline;
  long int _priority;
  long int _runtime;
  long int _period;
  long int _responsetime;

public:
  SchedParameter() :
    _valid(false) {}
  SchedParameter(long int period, long int deadline, long int runtime) :
    _valid(true),
    _type(SCHED_DEADLINE),
    _deadline(deadline),
    _runtime(runtime),
    _period(period) {}
  SchedParameter(long int responsetime) :
    _valid(true),
    _type(QoS_Feedback),
    _responsetime(responsetime) {}

  void setParam(long int period, long int deadline, long int runtime, long int priority)
  {
    _valid = true;
    _type = SCHED_DEADLINE;
    _deadline = deadline;
    _runtime = runtime;
    _period = period;
    _priority = priority;
  }

  void setParam(long int responsetime)
  {
    _valid = true;
    _type = QoS_Feedback;
    _responsetime = responsetime;
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

  long int getDeadline() const { return _deadline; }
  long int getRunTime() const { return _runtime; }
  long int getPriority() const { return _priority; }
  long int getPeriod() const { return _period; }
  long int getResponseTime() const { return _responsetime; }
};

#endif // TYPES_HPP
