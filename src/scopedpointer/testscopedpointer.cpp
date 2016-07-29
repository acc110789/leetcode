#include <QDebug>
#include <QList>

#include "myscopedpointer.h"
#include "myobject.h"

typedef QSharedPointer<MyObject> mySharedObject;

template <typename T>
struct MyCustomScopedPointerDeleter
{
    static inline void cleanup(T *pointer)
    {
        qDebug() << "\033[31;1m" << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__ << "\033[0m";
        // Enforce a complete type.
        // If you get a compile error here, read the section on forward declared
        // classes in the MyScopedPointer documentation.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete pointer;
        pointer = Q_NULLPTR;
    }
};

int main(int argc, char *argv[]) 
{
    MyScopedPointer<MyObject> myObjPtr1(new MyObject);
    MyScopedPointer<MyObject, MyCustomScopedPointerDeleter<MyObject> > myObjPtr2(new MyObject);
    
    MyObject *myObjPtr3 = new MyObject; // memory leak

    QList<mySharedObject> mySharedObjList;
    for (int i = 0; i < 10; i++) 
        mySharedObjList.append(mySharedObject(new MyObject));

    return 0;
}
