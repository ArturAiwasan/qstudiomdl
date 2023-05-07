#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString studiomdlavojo;
    QString qcdosiernomo;
    QString gameinfotxtvojo;
    QString qcdosiervojo;
    void SetupWindowTitle(QMainWindow *MainWindow, QString title)
    {
        MainWindow->setWindowTitle(title);
    };
    QProcess process;
    QStringList processarg {};
    QSettings settings;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_actionMalfermi_qc_dosieron_triggered();

    void on_actionEliri_triggered();

    void on_actionPri_QT_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_tekst_studiomdlvojo_textChanged();

    void on_actionPri_la_programo_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
