#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nWorkers(2),
    m_nTimerId(0)
{
    ui->setupUi(this);
    //
    m_nWorkers = std::min(m_nWorkers,10);
    for(int i = 0; i < m_nWorkers; ++i)
        m_lWorkers << new Worker(i + '0');
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
    if(pEvent->timerId() == m_nTimerId) {
        srand((unsigned)time(NULL));
        int n = rand() % m_nWorkers;
        if(m_lWorkers[n]->isRunning()) {
            ui->statusBar->setToolTip(
                        "Restarting " + QString::number(n) + " worker");
            m_lWorkers[n]->stop();
            m_lWorkers[n]->start();
        }
    }
    else
        QWidget::timerEvent(pEvent);
}

void MainWindow::on_action_Start_triggered()
{
    foreach (Worker* wThread, m_lWorkers) {
        if(wThread->isRunning()) {
            wThread->stop();
        }
        else {
            wThread->start();
        }
    }
    //
    if(ui->action_Start->text() == QString("&Start"))
        ui->action_Start->setText("&Stop");
    else
        ui->action_Start->setText("&Start");
}
