#ifndef OBSERVER_H
#define OBSERVER_H

class Match;

class Observer {
public:
    virtual void update(Match* match) = 0;
    virtual ~Observer() {}
};

#endif // OBSERVER_H
