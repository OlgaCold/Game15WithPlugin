#include "block.h"

Block::Block( QObject *parent) : QObject(parent)
{
}

void Block::setNumber(int num)
{
    number = num;
}

void Block::setState(bool state)
{
    isVoid = state;
}

Block::Block(int number, bool state) : number(number), isVoid(state)
{
}

int Block::getNumber()
{
    return number;
}

bool Block::getState()
{
    return isVoid;
}
