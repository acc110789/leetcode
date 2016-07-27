#include <QDebug>

#include "myobject.h"

MyObject::MyObject(QObject *parent) 
    : QObject(parent) 
{
    qDebug() << "\033[32m" << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__ << "\033[0m";
}

MyObject::~MyObject() 
{
    qDebug() << "\033[32;1m" << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__ << "\033[0m";
}
