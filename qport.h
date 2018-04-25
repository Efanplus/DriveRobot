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
#include <QTextEdit>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QLabel>

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

    QString str_order;
    QString str_receive;

private slots:
    void on_OpenButton_clicked();
    void Read_data();
    void cleardata();
    void senddata_text();

    void on_DebugButton_clicked();

public slots:
    void send_order();

private:
    Ui::QPort *ui;
    QSerialPort *serial;
    QWidget *Order_Debug;
    QTextEdit *send;
    QTextEdit *receive;
    QPushButton *send_button;
    QPushButton *clear_button;

    QLabel *manuallabel;
    QLineEdit *manualorder;

signals:
    void enable_control(bool);


};

#endif // QPORT_H
