#pragma execution_character_set("utf-8")
#include "qsingleton.h"
#include "qmath.h"
#include <QTime>
#include <QCoreApplication>
#include <math.h>
QSingleton* QSingleton::p = NULL;

QSingleton *QSingleton::instance()
{
    if(p == NULL)
        p = new QSingleton();
    return p;
}

//字符串的变换
void QSingleton::StringToHex(QString str, QByteArray &senddata)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

char QSingleton::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return ch-ch;//不在0-f范围内的会发送成0
}

void QSingleton::deBlank(QString &strs)
{
    QString sstr;
    for(int i = 0; i < strs.length(); i++)
    {
        sstr.append(strs.section(' ',i,i).trimmed());
    }
    strs = sstr;
}

void QSingleton::addblank(QString &strs)
{
    QString str;
    deBlank(strs);
    for(int i = 0; i < strs.length(); i += 2)
    {
        str.append(strs.mid(i,2));
        if(i < strs.length())
            str.append(' ');
    }
    strs = str;
}

void QSingleton::sleepmsec(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() <dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

QString QSingleton::Signed_int2hex(int filewidth, long num)
{
    long long number = num;
    if(number <= -pow(2,filewidth*4-1) || number >= pow(2,filewidth*4-1))
        qDebug() << "角度范围出现错误";
    qDebug() << number << filewidth;
    if(number < 0)
    {
        number += pow(2,filewidth*4);
    }
    qDebug() << number << filewidth << pow(2,filewidth*4);
    QString str = QString("%1").arg(number,filewidth,16,QLatin1Char('0'));
    return str;
}

int QSingleton::Signed_hex2int(QString str)
{
    bool ok;
    int length = str.length();
    int suanz = str.toInt(&ok,16);
    if(suanz >= pow(2,length*4-1))
    {
        suanz = suanz - pow(2,length*4);
    }
    return suanz;
}
