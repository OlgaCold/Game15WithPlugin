#include "block.h"

Block::Block(QObject *parent, int number, bool state) :
    QObject(parent), m_number(number), m_isVoid(state)
{
}

int Block::getNumber() const
{
    return m_number;
}

void Block::setState(bool state)
{
    m_isVoid = state;
}

bool Block::getState() const
{
    return m_isVoid;
}



