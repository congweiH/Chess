#include "board.h"

Board::Board(QWidget *parent) : QWidget(parent)
{
    for(int i=0;i<32;i++){
        _s[i].init(i);
    }
    _selected = -1;
    _bRedTurn = true;
}
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 画棋盘
    int d =40;   //格子的长度
    _d = d;

    // 1.画10条横线
    for(int i=1;i<=10;i++){
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    // 2.画9条竖线
    for(int i=1;i<=9;i++){
        if(i==1 || i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }

    // 画田字格
    painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(4*d,3*d),QPoint(6*d,d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));

    // 画棋子
    for(int i=0;i<32;i++)
    {
        drawStone(painter, i);
    }
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    int row, col;
    if(getRowCol(pt, row, col)==false)
        return;

    int clickedId = -1;
    for(int i=0;i<32;i++)
    {
        if(_s[i]._dead==false && _s[i]._row==row && _s[i]._col == col){
            clickedId = i;
            break;
        }
    }
    if(_selected==-1)
    {
        if(clickedId != -1){
            if(_bRedTurn == _s[clickedId]._red){
                _selected = clickedId;
                update();
            }
        }
    }else {  //移动棋子
        if(canMove(_selected, row, col, clickedId)){
            _s[_selected]._row = row;
            _s[_selected]._col = col;
            if(clickedId != -1){
                _s[clickedId]._dead = true;
            }
            _selected = -1;
            _bRedTurn = !_bRedTurn;
            update();
        }
    }

}
bool Board::canMoveJIANG(int moveid, int row, int col, int )
{
    if(_s[moveid]._red){
        if(row>2) return false;
    }else {
        if(row<7) return false;
    }
    if(col<3 || col>5) return false;

    int dy = abs(_s[moveid]._row - row);
    int dx = abs(_s[moveid]._col - col);
    if(dx + dy == 1) return true;

    return false;
}
bool Board::canMoveSHI(int moveid, int row, int col, int ){
    if(_s[moveid]._red){
        if(row>2) return false;
    }else {
        if(row<7) return false;
    }
    if(col<3 || col>5) return false;

    int dy = abs(_s[moveid]._row - row);
    int dx = abs(_s[moveid]._col - col);
    if(dx == 1 && dy == 1) return true;

    return false;
}
bool Board::canMoveXIANG(int moveid, int row, int col, int ){
    if(_s[moveid]._red){
        if(row>4) return false;
    }else {
        if(row<5) return false;
    }

    int dy = abs(_s[moveid]._row - row);
    int dx = abs(_s[moveid]._col - col);
    if(dx == 2 && dy == 2){
        int r = (_s[moveid]._row + row)/2;
        int c = (_s[moveid]._col + col)/2;
        if(hasStone(r,c)) return false;
        return true;
    }

    return false;
}
bool Board::canMoveMA(int moveid, int row, int col, int ){
    int dy = abs(_s[moveid]._row - row);
    int dx = abs(_s[moveid]._col - col);
    if((dx==1 && dy==2) || (dx==2 && dy==1)){
        int r, c;
        if(dx==2){
            r = _s[moveid]._row;
            c = (_s[moveid]._col + col)/2;
        }
        else {
            r = (_s[moveid]._row + row)/2;
            c = _s[moveid]._col;
        }
        if(hasStone(r,c)) return false;
        return true;
    }

    return false;
}
bool Board::canMoveCHE(int moveid, int row, int col, int ){
    if(_s[moveid]._row == row){
        if(hasStone(_s[moveid]._col,col,true,row,col)) return false;
        return true;
    }
    else if(_s[moveid]._col == col){
        if(hasStone(_s[moveid]._row,row,false,row,col)) return false;
        return true;
    }
    else {
        return false;
    }
}
bool Board::canMovePAO(int moveid, int row, int col, int killid){
    if(killid == -1){
        return canMoveCHE(moveid,row,col,killid);
    }else{
        if(_s[moveid]._row == row){
            if(hasStone(_s[moveid]._col, col,true,row,col)==1) return true;
            return false;
        }
        else if(_s[moveid]._col == col){

            if(hasStone(_s[moveid]._row, row,false,row,col)==1) return true;
            return false;
        }
        else {
            return false;
        }
    }
}
bool Board::canMoveBING(int moveid, int row, int col, int ){
    if(_s[moveid]._red){
        if(row<_s[moveid]._row) return false;
        if(_s[moveid]._row == 3 || _s[moveid]._row == 4){
            if(_s[moveid]._col != col) return false;
        }
    }else{
        if(row>_s[moveid]._row) return false;
        if(_s[moveid]._row == 5 || _s[moveid]._row == 6){
            if(_s[moveid]._col != col) return false;
        }
    }

    int dy = abs(_s[moveid]._row - row);
    int dx = abs(_s[moveid]._col - col);
    if(dx+dy == 1) return true;

    return false;

}

bool Board::canMove(int moveid, int row, int col, int killid)
{
    if(killid==-1){}
    else {
        if(_s[moveid]._red == _s[killid]._red)
        {
            _selected = killid;
            update();
            return false;
        }
    }

    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMoveJIANG(moveid,row,col,killid);

    case Stone::SHI:
        return canMoveSHI(moveid,row,col,killid);

    case Stone::XIANG:
        return canMoveXIANG(moveid,row,col,killid);

    case Stone::MA:
        return canMoveMA(moveid,row,col,killid);

    case Stone::CHE:
        return canMoveCHE(moveid,row,col,killid);

    case Stone::PAO:
        return canMovePAO(moveid,row,col,killid);

    case Stone::BING:
        return canMoveBING(moveid,row,col,killid);

    }


    return true;
}


bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<10;row++)
        for(col=0;col<9;col++){
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx+dy*dy;
            if(dist<_d/2*_d/2)
                return true;
        }
    return false;
}

QPoint Board::center(int row, int col)
{
    QPoint res;
    res.rx() = (col+1)*_d;
    res.ry() = (row+1)*_d;
    return res;
}

void Board::drawStone(QPainter& painter, int id)
{
    if(_s[id]._dead)
        return;
    QPoint c = center(_s[id]._row,_s[id]._col);
    QRect rect = QRect(c.x()-_d/2, c.y()-_d/2, _d, _d);
    if(_selected!=id)
        painter.setBrush(QColor(Qt::yellow));
    else
        painter.setBrush(QColor(Qt::gray));
    painter.setPen(QColor(Qt::black));

    painter.drawEllipse(c, _d/2, _d/2);

    if(_s[id]._red)
        painter.setPen(QColor(Qt::red));

    painter.setFont(QFont("宋体", _d/2, 700));

    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
}
bool Board::hasStone(int row, int col){
    for(int i=0;i<32;i++)
        if(_s[i]._dead==false && _s[i]._row == row && _s[i]._col == col)
            return true;
    return false;
}
int Board::hasStone(int a, int b, bool bRow, int row,int col)
{
    int t = 0;
    int mn = min(a,b);
    int mx = max(a,b);
    for(int i=mn+1;i<mx;i++){
        if(bRow){
            if(hasStone(row,i)) t++;
        }
        else{
            if(hasStone(i,col)) t++;
        }
    }
    return t;
}
