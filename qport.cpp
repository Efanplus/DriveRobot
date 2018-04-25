#pragma execution_character_set("utf-8")
#include "qport.h"
#include "ui_qport.h"



QPort* QPort::p = NULL;

QPort *QPort::instance()
{
    if(p == NULL)
        p = new QPort();
    return p;
}

QPort::QPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPort)
{
    ui->setupUi(this);
    QFont font("楷体",16);
    QGroupBox *GroupBox = new QGroupBox(tr("串口设置"));
    GroupBox->setFont(font);
    QGridLayout *GridLayout = new QGridLayout;
    this->setLayout(GridLayout);
    GridLayout->addWidget(GroupBox);
    GroupBox->setLayout(ui->gridLayout);

    //关于串口的程序
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //波特率默认设置为显示第(3+1)项
    ui->BaundBox->setCurrentIndex(3);

    //调试界面，方便调试指令用
    Order_Debug = new QWidget;
    send = new QTextEdit;
    receive = new QTextEdit;
    send_button = new QPushButton(tr("发送数据"));
    clear_button = new QPushButton(tr("清空窗口"));
    QHBoxLayout  *h_buttons = new QHBoxLayout;
    h_buttons->addWidget(send_button);
    h_buttons->addWidget(clear_button);
    QFrame *buttons = new QFrame;
    buttons->setLayout(h_buttons);

    manuallabel = new QLabel(tr("输入指令"));
    manualorder = new QLineEdit;
    QHBoxLayout *h_order = new QHBoxLayout;
    h_order->addWidget(manuallabel);
    h_order->addWidget(manualorder);
    QFrame *order = new QFrame;
    order->setLayout(h_order);

    QVBoxLayout *V_debug = new QVBoxLayout;
    Order_Debug->setLayout(V_debug);
    QGroupBox *send_box = new QGroupBox(tr("发送窗口"));
    QGroupBox *receive_box = new QGroupBox(tr("接收窗口"));
    QGridLayout *send_layout = new QGridLayout;
    QGridLayout *receive_layout = new QGridLayout;
    send_box->setLayout(send_layout);
    receive_box->setLayout(receive_layout);
    send_layout->addWidget(send);
    receive_layout->addWidget(receive);

    V_debug->addWidget(send_box);
    V_debug->addWidget(receive_box);
    V_debug->addWidget(order);
    V_debug->addWidget(buttons);


    connect(clear_button,SIGNAL(clicked(bool)),this,SLOT(cleardata()));
    connect(send_button,SIGNAL(clicked(bool)),this,SLOT(senddata_text()));
}

QPort::~QPort()
{
    delete ui;
}

char QPort::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
    else return ch-ch;//不在0-f范围内的会发送成0
}

void QPort::StringToHex(QString str, QByteArray &senddata)
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

void QPort::deBlank(QString &strs)
{
    QString sstr;
    for(int i = 0; i < strs.length(); i++)
    {
        sstr.append(strs.section(' ',i,i).trimmed());
    }
    strs = sstr;
}

void QPort::on_OpenButton_clicked()
{
    if(ui->OpenButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->BaundBox->currentText().toInt());
        //设置数据位数
        switch(ui->BitnumBox->currentIndex())
        {
        case 8: serial->setDataBits(QSerialPort::Data8); break;
        default: break;
        }
        //设置奇偶校验
        switch(ui->ParityBox->currentIndex())
        {
        case 0: serial->setParity(QSerialPort::NoParity); break;
        default: break;
        }
        //设置停止位
        switch(ui->StopBox->currentIndex())
        {
        case 1: serial->setStopBits(QSerialPort::OneStop); break;
        case 2: serial->setStopBits(QSerialPort::TwoStop); break;
        default: break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaundBox->setEnabled(false);
        ui->BitnumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->OpenButton->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &QPort::Read_data);
        emit enable_control(true);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaundBox->setEnabled(true);
        ui->BitnumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->OpenButton->setText(tr("打开串口"));
        emit enable_control(false);
    }
}

void QPort::Read_data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        receive->insertPlainText(buf.toHex());
//        ui->textEdit->insertPlainText("\n");
    }
    QString sstr;
    sstr = tr(buf.toHex());
    buf.clear();
    //serial->write(buf);
}

void QPort::cleardata()
{
    send->clear();
    receive->clear();
}

void QPort::senddata_text()
{
    str_order = manualorder->text();
    send_order();
}

void QPort::send_order()
{
    QString str = str_order;
    deBlank(str);
    if(!str.isEmpty())
    {
         int len =str.length();
         if(len%2 == 1)   //如果发送的数据个数为奇数的，则在前面最后落单的字符前添加一个字符0
             {
                 str = str.insert(len-1,'0'); //insert(int position, const QString & str)
             }
         QByteArray senddata;
         StringToHex(str,senddata);//将str字符串转换为16进制的形式
//         qDebug() << "senddata: " <<senddata << endl;
         serial->write(senddata);//发送到串口
    }
//    if(send->toPlainText() == NULL)
//    {
//        send->setPlainText(str_order);
//    }
//    else {
//        send->setPlainText(ui->Send_text->toPlainText() + "\n" + str_order);
//    }
    if(!str_order.isEmpty())
    {
        send->insertPlainText(str_order);
    }
}

void QPort::on_DebugButton_clicked()
{
    Order_Debug->show();
}
