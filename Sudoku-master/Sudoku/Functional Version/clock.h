#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>

namespace Ui {
class Clock;
}

class Clock : public QLCDNumber
{
    Q_OBJECT
    
public:
    explicit Clock(QWidget *parent = 0);
    ~Clock();
    int timeAdded;
    
private:
    Ui::Clock *ui;
    QTime initialTime;
    QTimer *timer;


public slots:
    void startTimer();
    void stopTimer();
    int getTimeScore();

private slots:
    void showTime();
    void initGui();


};

#endif // CLOCK_H
