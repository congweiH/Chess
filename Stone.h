#ifndef STONE_H
#define STONE_H

#include <QString>

class Stone
{
public:
    Stone();

    enum TYPE{JIANG, CHE, PAO, SHI, MA, XIANG, BING};

    int _id;
    int _row;
    int _col;
    bool _dead;
    bool _red;
    TYPE _type;

    void init(int id);
    QString getText();
};

#endif // STONE_H
