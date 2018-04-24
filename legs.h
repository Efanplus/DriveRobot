#ifndef LEGS_H
#define LEGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

namespace Ui {
class Legs;
}

class Legs : public QWidget
{
    Q_OBJECT

public:
    explicit Legs(QWidget *parent = 0);
    ~Legs();

private:
    Ui::Legs *ui;
};

#endif // LEGS_H
