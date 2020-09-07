#include "block.h"

Block::Block(QObject *parent, int number, bool state) :
    QObject(parent), m_number(number), m_isVoid(state)
{
}

void Block::setNumber(int num)
{
    m_number = num;
}

void Block::setState(bool state)
{
    m_isVoid = state;
}

int Block::getNumber()
{
    return m_number;
}

bool Block::getState()
{
    return m_isVoid;
}
