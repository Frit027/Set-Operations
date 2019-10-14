#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonAddTwo_clicked();
    void on_pushButtonUnion_clicked();
    void on_pushButtonInter_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonDeleteTwo_clicked();
    void on_pushButtonEqual_clicked();
    void on_pushButtonFind_clicked();
    void on_pushButtonFindTwo_clicked();
    void on_pushButtonFileIn_clicked();
    void on_pushButtonFileOut_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSubTwo_clicked();

private:
    template<typename T>
    void funcUnion(QStringList text1, QStringList text2);

    template<typename T>
    void funcIntersect(QStringList text1, QStringList text2);

    template<typename T>
    void funcSubtract(QStringList text1, QStringList text2);

    template<typename T>
    void funcDelete(QString str, QStringList text);

    template<typename T>
    void funcDeleteTwo(QString str, QStringList text);

    template<typename T>
    void funcEqual(QStringList text1, QStringList text2);

    template<typename T>
    void funcFind(QStringList text, QString key);

    template<typename T>
    void print(QSet<T> set);

    bool checkIntNumber(QString str);
    bool checkDoubleNumber(QString str);
    bool checkChar(QString str);
    bool checkBool(QString str);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
