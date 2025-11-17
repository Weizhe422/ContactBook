#include "mywidget.h"
#include "ui_mywidget.h"
#include "QMessageBox"
#include "QTextStream"
#include "QFile"
#include "QDebug"
#include "QFileDialog"

QString mFilename = "C:/Users/user/Desktop/EX/ContactBook.txt";

// 寫入文件的函數
void Write(QString Filename, QString str)
{
    QFile mFile(Filename); // 宣告QFile函數
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out << str;
    mFile.flush(); // 刷新mFile
    mFile.close(); // 關閉mFile
}

// 讀取文件的函數
QString MyWidget::Read(QString Filename)
{
    QFile mFile(Filename);
    if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file for read";
        return "";
    }

    QTextStream in(&mFile);
    QString fileContent = in.readAll();
    mFile.close();
    return fileContent;
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QStringList ColTotle;
    ui->tableWidget->setColumnCount(4);
    ColTotle << QStringLiteral("學號") << QStringLiteral("班級") << QStringLiteral("姓名") << QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1, *inputRow2, *inputRow3, *inputRow4;
    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, inputRow4);
}

void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile = "";
    int rc, cc;
    rc = ui->tableWidget->rowCount();
    cc = ui->tableWidget->columnCount();
    mFilename = QFileDialog::getSaveFileName(this, "匯出存檔", ".");

    for (int i = 0; i < rc; i++) {
        for (int j = 0; j < cc; j++) {
            saveFile += ui->tableWidget->item(i, j)->text() + ",";
        }
        saveFile += "\n";
    }
    Write(mFilename, saveFile);
}

void MyWidget::on_pushButton_4_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "選擇檔案", ".", "Text Files (*.txt);;All Files (*)");

    if (openFileName.isEmpty()) {
        return;  // 如果沒有選擇檔案，直接返回
    }

    QString fileContent = Read(openFileName);

    // 將匯入的資料顯示到 QTableWidget
    ui->tableWidget->setRowCount(0);  // 清空現有的資料

    QStringList lines = fileContent.split("\n");
    foreach (const QString &line, lines) {
        if (!line.isEmpty()) {
            QStringList fields = line.split(",");
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
            for (int i = 0; i < fields.size(); ++i) {
                ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
            }
        }
    }
}

void MyWidget::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "結束", "確定要退出嗎?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
