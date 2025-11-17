#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    // 聲明 Read 函數
    QString Read(QString Filename);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
