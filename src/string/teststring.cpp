#include <QScopedPointer>
#include <QDebug>

class MyString
{
public:
    explicit MyString(const char* str) 
        : m_str(str) 
    {
        qDebug() << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__;
    }

    virtual ~MyString() 
    {
        qDebug() << "DEBUG:" << __FILE__ << __PRETTY_FUNCTION__;
    }

    int toInt(bool* ok = Q_NULLPTR, int base = 10) const
    {
        char* endptr;
        long val;

        errno = 0;
        val = strtol(m_str, &endptr, base);
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || 
            (errno != 0 && val == 0)) {
            if (ok != 0)
                *ok = false;
            qCritical() << strerror(errno);
        }
        if (endptr == m_str) {
            if (ok != 0)
                *ok = false;
            qCritical() << "No digits were found";
        }

        if (ok != 0)
            *ok = true;
        if (*endptr != '\0')
            qInfo() << "Further characters after number" << endptr;

        return val;
    }
    
    int toInt(bool& ok, int base = 10) const
    {
        char* endptr;
        long val;

        errno = 0;
        val = strtol(m_str, &endptr, base);
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || 
            (errno != 0 && val == 0)) {
            ok = false;
            qCritical() << strerror(errno);
        }
        if (endptr == m_str) {
            ok = false;
            qCritical() << "No digits were found";
        }

        ok = true;
        if (*endptr != '\0')
            qInfo() << "Further characters after number" << endptr;

        return val;
    }

private:
    const char* m_str;
};

int main(int argc, char* argv[]) 
{
    QScopedPointer<MyString> myStrPtr(new MyString("77"));
    bool ok;
    qDebug() << myStrPtr->toInt(&ok) << "\033[31m" << ok << "\033[0m";
    qDebug() << "\033[32m" << ok << "\033[0m";
    ok = false;
    qDebug() << myStrPtr->toInt(ok) << "\033[31m" << ok << "\033[0m";
    qDebug() << "\033[32m" << ok << "\033[0m";
    return 0;
}
