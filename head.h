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

private slots:
    void on_ZeroButton_clicked();

    void on_StartButton_clicked();

    void on_Slider_head_LR_valueChanged(int value);

    void on_Slider_head_valueChanged(int value);

    void on_PauseButton_clicked();

private:
    Ui::Head *ui;

signals:
    void send_order();
};

#endif // HEAD_H
