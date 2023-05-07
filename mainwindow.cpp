#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (settings.contains("GameInfoVojo")) {
        gameinfotxtvojo = settings.value("GameInfoVojo").toString();
        ui->tekst_gameinfotxtvojo->setPlainText(gameinfotxtvojo);
    };
    if (settings.contains("StudiomdlVojo")) {
        studiomdlavojo = settings.value("StudiomdlVojo").toString();
        ui->tekst_studiomdlvojo->setPlainText(studiomdlavojo);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    studiomdlavojo = QFileDialog::getOpenFileName(this, "Malfermi dosieron", "", "Ĉiuj dosieroj (*)");
    ui->tekst_studiomdlvojo->setPlainText(studiomdlavojo);
    settings.setValue("StudiomdlVojo", studiomdlavojo);
}

void MainWindow::on_pushButton_4_clicked()
{
    gameinfotxtvojo = QFileDialog::getOpenFileName(this, "Malfermi dosieron", "", "Necesaj (*.txt)");
    ui->tekst_gameinfotxtvojo->setPlainText(gameinfotxtvojo);
    settings.setValue("GameInfoVojo", gameinfotxtvojo);
}

void MainWindow::on_actionMalfermi_qc_dosieron_triggered()
{
    qcdosiervojo = QFileDialog::getOpenFileName(this, "Malfermi dosieron", "", "Necesaj (*.qc)");
    qcdosiernomo = "./" + QFileInfo(qcdosiervojo).fileName();
    processarg << qcdosiernomo;
    SetupWindowTitle(this, "Qstudiomdl @ " + qcdosiervojo);
}

void MainWindow::on_actionEliri_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionPri_QT_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString dosierujo = QFileInfo(qcdosiervojo).absolutePath();
    process.setWorkingDirectory(dosierujo);
    //qDebug() << "Nun dosierujo: " << dosierujo;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(studiomdlavojo, processarg);
    process.waitForStarted();
    process.waitForFinished(-1);
    if (!process.waitForFinished()) {
        qDebug() << "Failed to run process";
    };
    if (process.exitStatus() == QProcess::CrashExit) {
        qDebug() << "Process crashed";
    };
    if (process.exitCode() != 0) {
        qDebug() << "Process exited with error code" << process.exitCode();
    };
    QString eligo = process.readAll();
    ui->tekst_studiomdleligo->setPlainText(eligo);
    //qDebug() << "qc nomo: " << qcdosiernomo;
    //qDebug() << "studiomdl vojo: " << studiomdlavojo;
    //qDebug() << "proces erero: "<< process.error();
    process.terminate();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->tekst_studiomdleligo->setPlainText("");
}

void MainWindow::on_tekst_studiomdlvojo_textChanged()
{
    studiomdlavojo = ui->tekst_studiomdlvojo->toPlainText();
    settings.setValue("StudiomdlVojo", studiomdlavojo);
}

void MainWindow::on_actionPri_la_programo_triggered()
{
    QMessageBox prila(this);
    prila.setWindowTitle(tr("Informaĵo"));
    prila.setTextFormat(Qt::RichText);
    prila.setText("<h2>qstudiomdl</h2><p>Autoro: arbtttrn6 (arturaiwasan[@]gmail.com)</p>\
    <br><a href='https://vk.com/btttrn6'>\
            VK</a>");
    prila.exec();
}
