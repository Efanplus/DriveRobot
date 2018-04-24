#ifndef QSINGLETON_H
#define QSINGLETON_H

#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QMatrix4x4>

//#define Proportion_angle_pulse 1137.777778
#define PI 3.1415926



class QSingleton
{
protected:
    QSingleton()
    {}
private:
    static QSingleton *p;

public:
    static QSingleton* instance();
    void StringToHex(QString str, QByteArray & senddata);
    char ConvertHexChar(char ch);
    void deBlank(QString &strs);
    void addblank(QString &strs);
    void sleepmsec(int msec);

    QString Signed_int2hex(int filewidth,long num);
    int Signed_hex2int(QString str);


public:
    QString str_order = NULL;
    QString str_receive = NULL;

};

#endif // QSINGLETON_H

