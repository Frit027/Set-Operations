#include <QSet>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Operations on sets");

    QPixmap pix(":/new/MIREA_logo.png");

    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->lineEditFirst->setReadOnly(true);
    ui->lineEditSecond->setReadOnly(true);
    ui->lineEditRes->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

template<typename T>
void MainWindow::print(QSet<T> set)
{
    QString res;
    for(auto t : set)
    {
        res += t;
        res += " ";
    }

    ui->lineEditRes->setText(res);
}

template<typename T>
void MainWindow::funcUnion(QStringList text1, QStringList text2)
{
    QSet<T> mySet1;
    QSet<T> mySet2;

    mySet1 = text1.toSet();
    mySet2 = text2.toSet();

    mySet1.unite(mySet2);

    MainWindow::print(mySet1);
}

template<typename T>
void MainWindow::funcIntersect(QStringList text1, QStringList text2)
{
    QSet<T> mySet1;
    QSet<T> mySet2;

    mySet1 = text1.toSet();
    mySet2 = text2.toSet();

    mySet1.intersect(mySet2);
    MainWindow::print(mySet1);
}

template<typename T>
void MainWindow::funcSubtract(QStringList text1, QStringList text2)
{
    QSet<T> mySet1;
    QSet<T> mySet2;

    mySet1 = text1.toSet();
    mySet2 = text2.toSet();

    mySet1.subtract(mySet2);
    MainWindow::print(mySet1);
}

template<typename T>
void MainWindow::funcEqual(QStringList text1, QStringList text2)
{
    QSet<T> mySet1;
    QSet<T> mySet2;

    mySet1 = text1.toSet();
    mySet2 = text2.toSet();

    if(mySet1 == mySet2)
        QMessageBox::about(this, "Сообщение", "Множества равны.");
    else
        QMessageBox::critical(this, "Сообщение", "Множества не равны.");
}

template<typename T>
void MainWindow::funcFind(QStringList text, QString key)
{
    QSet<T> mySet;

    mySet = text.toSet();
    QSet<QString>::iterator it = mySet.find(key);

    if(it != mySet.end())
        QMessageBox::about(this, "Сообщение", "Элемент входит в множество.");
    else
        QMessageBox::critical(this, "Сообщение", "Элемент не входит в множество.");
}

void MainWindow::on_pushButtonAdd_clicked()
{
    bool ok, flag = true;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Элемент:"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
    {
        QStringList str = ui->lineEditFirst->text().split(" ");

        switch(ui->comboBox->currentIndex())
        {
            case 0:
                flag = MainWindow::checkIntNumber(text);
                break;
            case 1:
                flag = MainWindow::checkDoubleNumber(text);
                break;
            case 2:
                flag = MainWindow::checkChar(text);
                break;
            case 3:
                flag = MainWindow::checkBool(text);
                break;
        }

        if(flag)
        {
            if(str.contains(text))
                QMessageBox::about(this, "Сообщение", "Элемент уже входит в множество.");
            else
            {
                ui->lineEditFirst->setText(ui->lineEditFirst->text() + text + " ");
                ui->comboBox->setEnabled(false);
            }
        }
        else
            QMessageBox::warning(this, "Сообщение", "Несоответствие типа.");
    }
}

void MainWindow::on_pushButtonAddTwo_clicked()
{
    bool ok, flag = true;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Элемент:"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
    {
        QStringList str = ui->lineEditSecond->text().split(" ");

        switch(ui->comboBox->currentIndex())
        {
            case 0:
                flag = MainWindow::checkIntNumber(text);
                break;
            case 1:
                flag = MainWindow::checkDoubleNumber(text);
                break;
            case 2:
                flag = MainWindow::checkChar(text);
                break;
            case 3:
                flag = MainWindow::checkBool(text);
                break;
        }

        if(flag)
        {
            if(str.contains(text))
                QMessageBox::about(this, "Сообщение", "Элемент уже входит в множество.");
            else
            {
                ui->lineEditSecond->setText(ui->lineEditSecond->text() + text + " ");
                ui->comboBox->setEnabled(false);
            }
        }
        else
            QMessageBox::warning(this, "Сообщение", "Несоответствие типа.");
    }
}

void MainWindow::on_pushButtonUnion_clicked()
{
    QStringList str1 = ui->lineEditFirst->text().split(" ");
    QStringList str2 = ui->lineEditSecond->text().split(" ");
    MainWindow::funcUnion<QString>(str1, str2);
}

void MainWindow::on_pushButtonInter_clicked()
{
    QStringList str1 = ui->lineEditFirst->text().split(" ");
    QStringList str2 = ui->lineEditSecond->text().split(" ");
    MainWindow::funcIntersect<QString>(str1, str2);
}

void MainWindow::on_pushButtonSub_clicked()
{
    QStringList str1 = ui->lineEditFirst->text().split(" ");
    QStringList str2 = ui->lineEditSecond->text().split(" ");
    MainWindow::funcSubtract<QString>(str1, str2);
}

template<typename T>
void MainWindow::funcDelete(QString str, QStringList text)
{
    QSet<T> mySet;
    QString res = "";

    mySet = text.toSet();
    QSet<QString>::iterator it = mySet.find(str);

    mySet.erase(it);

    for(auto t : mySet)
    {
        res += t;
        res += " ";
    }

    ui->lineEditFirst->setText(res);
}

template<typename T>
void MainWindow::funcDeleteTwo(QString str, QStringList text)
{
    QSet<T> mySet;
    QString res;

    mySet = text.toSet();
    QSet<QString>::iterator it = mySet.find(str);

    mySet.erase(it);

    for(auto t : mySet)
    {
        res += t;
        res += " ";
    }

    ui->lineEditSecond->setText(res);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Какой элемент удалить?"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
         MainWindow::funcDelete<QString>(text, ui->lineEditFirst->text().split(" "));
}

void MainWindow::on_pushButtonDeleteTwo_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Какой элемент удалить?"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
         MainWindow::funcDeleteTwo<QString>(text, ui->lineEditSecond->text().split(" "));
}

void MainWindow::on_pushButtonEqual_clicked()
{
    QStringList str1 = ui->lineEditFirst->text().split(" ");
    QStringList str2 = ui->lineEditSecond->text().split(" ");
    MainWindow::funcEqual<QString>(str1, str2);
}

void MainWindow::on_pushButtonFind_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Какой элемент найти?"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
        MainWindow::funcFind<QString>(ui->lineEditFirst->text().split(" "), text);
}

void MainWindow::on_pushButtonFindTwo_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ввод элемента"),
                            tr("Какой элемент найти?"), QLineEdit::Normal,
                            "", &ok);
    if (ok && !text.isEmpty())
        MainWindow::funcFind<QString>(ui->lineEditSecond->text().split(" "), text);
}

void MainWindow::on_pushButtonFileIn_clicked()
{
    ui->comboBox->setEnabled(false);
    QFile fileIn(":/new/textIn.txt");

    if(!fileIn.open(QIODevice::ReadOnly))
        QMessageBox::critical(this, "Сообщение", "Не удалось открыть файл.");
    else
    {
        QList<QString> str;

        while(!fileIn.atEnd())
        {
            str << fileIn.readLine();
        }

        str[0].chop(2);

        ui->lineEditFirst->setText(str[0]);
        ui->lineEditSecond->setText(str[1]);

        fileIn.close();
    }
}

void MainWindow::on_pushButtonFileOut_clicked()
{
    QFile fileOut("C:\\Users\\user\\Documents\\CourseWorkTwo\\Set\\textOut.txt");
    QString str1, str2, str3;

    if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::critical(this, "Сообщение", "Не удалось открыть файл.");
    }
    else
    {
        str1 = ui->lineEditFirst->text();
        str2 = ui->lineEditSecond->text();
        str3 = ui->lineEditRes->text();
        QTextStream writeStream(&fileOut);
        writeStream << '\n' << str1 << '\n' << str2 << '\n' << str3;

        QMessageBox::information(this, "Сообщение", "Файл успешно записан.");

        fileOut.close();
    }
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->lineEditFirst->setText("");
    ui->lineEditSecond->setText("");
    ui->lineEditRes->setText("");
    ui->comboBox->setEnabled(true);
}

void MainWindow::on_pushButtonSubTwo_clicked()
{
    QStringList str1 = ui->lineEditFirst->text().split(" ");
    QStringList str2 = ui->lineEditSecond->text().split(" ");
    MainWindow::funcSubtract<QString>(str2, str1);
}

bool MainWindow::checkIntNumber(QString str)
{
    for(int i = 0; i < str.length(); i++)
        if(((str[i] < '0' || str[i] > '9') && (str[i] != '-')) || (str[i] == '-' && i))
            return false;

    return true;
}

bool MainWindow::checkDoubleNumber(QString str)
{
    int k = 0;

    if(str[0] == '.' || str[str.length() - 1] == '.')
        return false;

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == '.')
            k++;
        if(((str[i] < '0' || str[i] > '9') && (str[i] != '.') && (str[i] != '-')) || (str[i] == '-' && i))
            return false;
        if(str[i] == '.' && str[i-1] == '-')
            return false;
    }

    if(k > 1 || !k)
        return false;

    return true;
}

bool MainWindow::checkChar(QString str)
{
    if(str.length() != 1)
        return false;
    return true;
}

bool MainWindow::checkBool(QString str)
{
    if(str != "0" && str != "1")
        return false;
    return true;
}
