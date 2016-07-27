/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MYSCOPEDPOINTER_H
#define MYSCOPEDPOINTER_H

#include <QtCore/qglobal.h>

#include <stdlib.h>

QT_BEGIN_NAMESPACE

template <typename T>
struct MyScopedPointerDeleter
{
    static inline void cleanup(T *pointer)
    {
        qDebug() << "\033[31m" << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__ << "\033[0m";
        // Enforce a complete type.
        // If you get a compile error here, read the section on forward declared
        // classes in the MyScopedPointer documentation.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete pointer;
    }
};

template <typename T>
struct MyScopedPointerArrayDeleter
{
    static inline void cleanup(T *pointer)
    {
        // Enforce a complete type.
        // If you get a compile error here, read the section on forward declared
        // classes in the MyScopedPointer documentation.
        typedef char IsIncompleteType[ sizeof(T) ? 1 : -1 ];
        (void) sizeof(IsIncompleteType);

        delete [] pointer;
    }
};

struct MyScopedPointerPodDeleter
{
    static inline void cleanup(void *pointer) { if (pointer) free(pointer); }
};

#ifndef QT_NO_QOBJECT
template <typename T>
struct MyScopedPointerObjectDeleteLater
{
    static inline void cleanup(T *pointer) { if (pointer) pointer->deleteLater(); }
};

class QObject;
typedef MyScopedPointerObjectDeleteLater<QObject> MyScopedPointerDeleteLater;
#endif

template <typename T, typename Cleanup = MyScopedPointerDeleter<T> >
class MyScopedPointer
{
    typedef T *MyScopedPointer:: *RestrictedBool;
public:
    explicit inline MyScopedPointer(T *p = Q_NULLPTR) : d(p)
    {
    }

    inline ~MyScopedPointer()
    {
        T *oldD = this->d;
        Cleanup::cleanup(oldD);
    }

    inline T &operator*() const
    {
        Q_ASSERT(d);
        return *d;
    }

    inline T *operator->() const
    {
        Q_ASSERT(d);
        return d;
    }

    inline bool operator!() const
    {
        return !d;
    }

#if defined(Q_QDOC)
    inline operator bool() const
    {
        return isNull() ? Q_NULLPTR : &MyScopedPointer::d;
    }
#else
    inline operator RestrictedBool() const
    {
        return isNull() ? Q_NULLPTR : &MyScopedPointer::d;
    }
#endif

    inline T *data() const
    {
        return d;
    }

    inline bool isNull() const
    {
        return !d;
    }

    inline void reset(T *other = Q_NULLPTR)
    {
        if (d == other)
            return;
        T *oldD = d;
        d = other;
        Cleanup::cleanup(oldD);
    }

    inline T *take()
    {
        T *oldD = d;
        d = Q_NULLPTR;
        return oldD;
    }

    inline void swap(MyScopedPointer<T, Cleanup> &other)
    {
        qSwap(d, other.d);
    }

    typedef T *pointer;

protected:
    T *d;

private:
    Q_DISABLE_COPY(MyScopedPointer)
};

template <class T, class Cleanup>
inline bool operator==(const MyScopedPointer<T, Cleanup> &lhs, const MyScopedPointer<T, Cleanup> &rhs)
{
    return lhs.data() == rhs.data();
}

template <class T, class Cleanup>
inline bool operator!=(const MyScopedPointer<T, Cleanup> &lhs, const MyScopedPointer<T, Cleanup> &rhs)
{
    return lhs.data() != rhs.data();
}

template <class T, class Cleanup>
Q_INLINE_TEMPLATE void qSwap(MyScopedPointer<T, Cleanup> &p1, MyScopedPointer<T, Cleanup> &p2)
{ p1.swap(p2); }

QT_END_NAMESPACE
namespace std {
    template <class T, class Cleanup>
    Q_INLINE_TEMPLATE void swap(QT_PREPEND_NAMESPACE(MyScopedPointer)<T, Cleanup> &p1, QT_PREPEND_NAMESPACE(MyScopedPointer)<T, Cleanup> &p2)
    { p1.swap(p2); }
}
QT_BEGIN_NAMESPACE



namespace QtPrivate {
    template <typename X, typename Y> struct MyScopedArrayEnsureSameType;
    template <typename X> struct MyScopedArrayEnsureSameType<X,X> { typedef X* Type; };
    template <typename X> struct MyScopedArrayEnsureSameType<const X, X> { typedef X* Type; };
}

template <typename T, typename Cleanup = MyScopedPointerArrayDeleter<T> >
class MyScopedArrayPointer : public MyScopedPointer<T, Cleanup>
{
public:
    inline MyScopedArrayPointer() : MyScopedPointer<T, Cleanup>(Q_NULLPTR) {}

    template <typename D>
    explicit inline MyScopedArrayPointer(D *p, typename QtPrivate::MyScopedArrayEnsureSameType<T,D>::Type = Q_NULLPTR)
        : MyScopedPointer<T, Cleanup>(p)
    {
    }

    inline T &operator[](int i)
    {
        return this->d[i];
    }

    inline const T &operator[](int i) const
    {
        return this->d[i];
    }

private:
    explicit inline MyScopedArrayPointer(void *) {
        // Enforce the same type.

        // If you get a compile error here, make sure you declare
        // MyScopedArrayPointer with the same template type as you pass to the
        // constructor. See also the MyScopedPointer documentation.

        // Storing a scalar array as a pointer to a different type is not
        // allowed and results in undefined behavior.
    }

    Q_DISABLE_COPY(MyScopedArrayPointer)
};

QT_END_NAMESPACE

#endif // MYSCOPEDPOINTER_H
