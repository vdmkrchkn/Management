#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void showEvent(QShowEvent *pEvent = 0);
    void hideEvent(QHideEvent *pEvent = 0);
    void timerEvent(QTimerEvent *pEvent);
private slots:
    void on_action_Start_triggered();
private:
    Ui::MainWindow *ui;
    int m_nWorkers;
    QList<Worker*> m_lWorkers;
    int m_nTimerId;
    bool m_bStopped;
};

#endif // MAINWINDOW_H
