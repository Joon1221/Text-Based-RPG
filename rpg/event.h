#ifndef EVENT_H
#define EVENT_H

class Mon;
class TimeBomb;

class Event {
public:
    int time;
    
    Event();
    Event(int time);
    virtual ~Event();
    
    void print();
    
    virtual void trigger() = 0; // pure virtual function
};

class MonRespawnEvent : public Event {
protected:
    Mon *mon;
    
public:
    MonRespawnEvent();
    MonRespawnEvent(int time, Mon *mon);
    virtual ~MonRespawnEvent();
    
    virtual void trigger();
};

class DayAndNightEvent : public Event {
protected:    
public:
    DayAndNightEvent();
    DayAndNightEvent(int time);
    virtual ~DayAndNightEvent();
    
    virtual void trigger();
};

class TimeBombEvent : public Event {
protected:
    TimeBomb *timeBomb;
    
public:
    TimeBombEvent();
    TimeBombEvent(int time, TimeBomb *timeBomb);
    virtual ~TimeBombEvent();
    
    virtual void trigger();
};

class BossRushEvent : public Event {
protected:
public:
    BossRushEvent();
    BossRushEvent(int time);
    virtual ~BossRushEvent();
    
    virtual void trigger();
};

class StatLogEvent : public Event {
protected:
    string logFilename;
    bool destroy;
    
public:
    StatLogEvent();
    StatLogEvent(const StatLogEvent &other);
    StatLogEvent(int time, string logFilename);
    
    virtual ~StatLogEvent();
    
    void setSelfDestroy(bool destroy);
    
    virtual void trigger();
};

#endif
