#pragma execution_character_set("utf-8")
#ifndef QPORT_H
#define QPORT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class QPort;
}

class QPort : public QWidget
{
    Q_OBJECT

private:
    static QPort *p;

public:
    static QPort* instance();
    explicit QPort(QWidget *parent = 0);
    ~QPort();
    char ConvertHexChar(char ch);
    void StringToHex(QString str, QByteArray & senddata);
    void deBlank(QString &strs);

private slots:
    void on_OpenButton_clicked();
    void Read_data();
    void send_order();

private:
    Ui::QPort *ui;
    QSerialPort *serial;
    QString str_order;
    QString str_receive;
};

#endif // QPORT_H
