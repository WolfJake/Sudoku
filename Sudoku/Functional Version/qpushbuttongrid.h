#ifndef QPUSHBUTTONGRID_H
#define QPUSHBUTTONGRID_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class QPushButtonGrid;
}

class QPushButtonGrid : public QPushButton
{
    Q_OBJECT

public:
    explicit QPushButtonGrid(QPushButton *parent = 0);
    ~QPushButtonGrid();
    int row;
    int column;
    int realNumber;
    int assignedNumber;
    int color;

private:
    Ui::QPushButtonGrid *ui;
};

#endif // QPUSHBUTTONGRID_H
