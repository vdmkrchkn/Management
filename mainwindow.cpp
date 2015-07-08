#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nWorkers(2), m_nTimerId(0), m_bStopped(true)
{
    ui->setupUi(this);
    //
    m_nWorkers = std::min(m_nWorkers,10);
    for(int i = 0; i < m_nWorkers; ++i)
        m_lWorkers << new Worker(i);
}

MainWindow::~MainWindow()
{
    delete ui;
    foreach (Worker* wThread, m_lWorkers) {
        wThread->stop();
        wThread->wait(); // ожидание завершения потока
    }
}

void MainWindow::showEvent(QShowEvent *pEvent)
{
    m_nTimerId = startTimer(10000);
}

void MainWindow::hideEvent(QHideEvent *pEvent)
{
    killTimer(m_nTimerId);
}

void MainWindow::timerEvent(QTimerEvent *pEvent)
{
    if(pEvent->timerId() == m_nTimerId && !m_bStopped) {
        srand((unsigned)time(NULL));
        int n = rand() % m_nWorkers;
        if(m_lWorkers[n]->isRunning()) {
            m_lWorkers[n]->stop();
            ui->statusBar->showMessage(
                        "Restarting " + QString::number(n) + " worker", 5000);
            QThread::sleep(5);
            m_lWorkers[n]->start();
        }
    }
    else
        QWidget::timerEvent(pEvent);
}

void MainWindow::on_action_Start_triggered()
{
    if(m_bStopped) {
        foreach (Worker* wThread, m_lWorkers)
            wThread->start();
        m_bStopped = false;
        ui->action_Start->setText("&Stop");
    }
    else {
        foreach (Worker* wThread, m_lWorkers)
            wThread->stop();
        m_bStopped = true;
        ui->action_Start->setText("&Start");
    }
}
