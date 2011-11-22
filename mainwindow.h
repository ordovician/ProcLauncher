#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtCore/QProcess>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void SelectScriptFile();
    void RunSelectedScript();

    // callbacks for running external process
    void ProcessStarted();
    void ProcessStateChanged (QProcess::ProcessState new_state);

    void ReadFromProcesss();

private:
    Ui::MainWindow *ui;
    QProcess *process_;
};

#endif // MAINWINDOW_H
