#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include "Stone.h"
#include <algorithm>
using namespace std;

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    int _d;
    Stone _s[32];
    int _selected;
    bool _bRedTurn;

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void drawStone(QPainter& painter, int id);
    QPoint center(int row, int col);

    bool getRowCol(QPoint pt, int& row, int& col);

    bool canMove(int moveid, int row,int col, int killid);
    bool canMoveJIANG(int moveid, int row,int col, int killid);
    bool canMoveSHI(int moveid, int row,int col, int killid);
    bool canMoveXIANG(int moveid, int row,int col, int killid);
    bool canMoveMA(int moveid, int row,int col, int killid);
    bool canMoveCHE(int moveid, int row,int col, int killid);
    bool canMovePAO(int moveid, int row,int col, int killid);
    bool canMoveBING(int moveid, int row,int col, int killid);

    bool hasStone(int row,int col);
    int hasStone(int a, int b, bool bRow, int row,int col);

signals:

public slots:
};

#endif // BOARD_H
