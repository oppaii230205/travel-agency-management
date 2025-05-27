#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QVariant>
#include <QDateTime>

class Event {
public:
    Event() : _timestamp(QDateTime::currentDateTime()) {}
    virtual ~Event() = default;

    QDateTime timestamp() const { return _timestamp; }
    virtual QString name() const = 0;
    virtual QVariantMap data() const = 0;

private:
    QDateTime _timestamp;
};

#endif // EVENT_H
