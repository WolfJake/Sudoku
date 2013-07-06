#include "clock.h"
#include "ui_clock.h"
#include <QTime>
#include <QTimer>

Clock::Clock(QWidget *parent) :
    QLCDNumber(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    initGui();
}

Clock::~Clock()
{
    delete timer;
    delete ui;
}

void Clock::initGui()
{
    setSegmentStyle(Filled);
    setWindowTitle(tr("Timer"));
    resize(150, 60);
}

void Clock::showTime()
{
    QTime time = QTime::currentTime();
    time = time.addSecs(-initialTime.hour() * 3600 - initialTime.minute() * 60 - initialTime.second());
    QString text = time.toString("hh:mm:ss");

    display(text);
}

void Clock::startTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    initialTime = QTime::currentTime();
    display("00:00");
    showTime();
}

void Clock::stopTimer()
{
    timer->stop();
}

int Clock::getTimeScore()
{
    QTime time = QTime::currentTime();
    time = time.addSecs(-initialTime.hour() * 3600 - initialTime.minute() * 60 - initialTime.second());
    return time.hour() * 3600 + time.minute() * 60 + time.second();
}
