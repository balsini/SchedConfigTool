#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

#include <QString>

class ExperimentParameter {
    bool _valid;

    long int _runs;
    long int _parallelization;
    long int _period;

public:
    ExperimentParameter() {}

    bool isValid() const { return _valid; }
    void isValid(bool valid) { _valid = valid; }

    void setRuns(long int x) { _runs = x; }
    void setParallel(long int x) { _parallelization = x; }
    void setPeriod(long int x) { _period = x; }

    long int getRuns() const { return _runs; }
    long int getParallelization() const { return _parallelization; }
    long int getPeriod() const { return _period; }

    friend std::ostream &operator<<(std::ostream &o, const ExperimentParameter &sp) {
        o << "Experiment" << std::endl;
        return o;
    }
};

#endif // TYPES_HPP
