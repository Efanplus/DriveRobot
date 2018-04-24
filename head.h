#ifndef HEAD_H
#define HEAD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

namespace Ui {
class Head;
}

class Head : public QWidget
{
    Q_OBJECT

public:
    explicit Head(QWidget *parent = 0);
    ~Head();

private:
    Ui::Head *ui;
};

#endif // HEAD_H
