#ifndef ARM_H
#define ARM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

namespace Ui {
class Arm;
}

class Arm : public QWidget
{
    Q_OBJECT

public:
    explicit Arm(QWidget *parent = 0);
    ~Arm();

private:
    Ui::Arm *ui;
};

#endif // ARM_H
