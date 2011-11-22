#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QFileDialog>
#include <QtCore/QDir>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectScriptFile() {
    QString file_path = QFileDialog::getOpenFileName(this, "Select script file to run", QDir::homePath());
    ui->file_path_field->setText(file_path);
}

void MainWindow::RunSelectedScript() {
    QString script_path = ui->file_path_field->text();

    QStringList arguments;

    process_ = new QProcess(this);
    connect(process_, SIGNAL(started()), SLOT(ProcessStarted()));
    connect(process_, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(ProcessStateChanged(QProcess::ProcessState)));
    connect(process_, SIGNAL(readyReadStandardOutput()), SLOT(ReadFromProcesss()));

    process_->start(script_path, arguments);
}

QString toString(QProcess::ProcessState state) {
    switch (state) {
    case QProcess::NotRunning: return "The process is not running.";
    case QProcess::Starting:   return "The process is starting, but the program has not yet been invoked.";
    case QProcess::Running:	        return "The process is running and is ready for reading and writing.";
    default:
        break;
    }

    return "Unknown state";
}

void MainWindow::ProcessStarted() {
    ui->message_box->append("Process started");
}

void MainWindow::ProcessStateChanged (QProcess::ProcessState new_state) {
    ui->message_box->append("Changed state to: " + toString(new_state));
}

void MainWindow::ReadFromProcesss() {
    ui->message_box->append("One invocation:");
    while (process_->canReadLine()) {
        QString line = process_->readLine();
        ui->message_box->append(line.trimmed());
    }
}
