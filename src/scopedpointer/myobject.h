#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject 
{
    Q_OBJECT

public:
    explicit MyObject(QObject *parent = Q_NULLPTR);
    virtual ~MyObject(); 
};

#endif // MYOBJECT_H
