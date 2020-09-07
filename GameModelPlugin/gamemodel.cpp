#include "gamemodel.h"

GameModel::GameModel(QObject *parent)
    : QAbstractListModel(parent), m_gridSize(GRID_SIZE)
{
    for(int i = 0; i < m_gridSize*m_gridSize; i++){
        m_data.append(new Block(nullptr, i + 1, false));
    }
    m_data.at(m_gridSize*m_gridSize - 1)->setState(true);
    mix();
}

GameModel::~GameModel()
{
    for (int i = 0; i < m_data.size(); i++){
        delete (m_data.takeAt(i));
    }
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.count();
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if (!index.isValid())
        return QVariant();

    switch(role) {
    case DisplayRole:
        return m_data.at(row)->getNumber();
    case IsVoidRole:
        return m_data.at(row)->getState();
    }
    return QVariant();
}


QHash<int, QByteArray> GameModel::roleNames() const
{
    return { { DisplayRole, "display" },
        { IsVoidRole, "isvoid" },
    };
}

void GameModel::mix()
{
    do{ shuffle(); }
    while( !checkIsValid() );
}


bool GameModel::move(int oldP)
{
    int newP;

    if(findVoidCellId(oldP) != -1) {

        newP = findVoidCellId(oldP);

        int min = oldP < newP ? oldP : newP;
        int max = oldP < newP ? newP : oldP;

        emit beginMoveRows(QModelIndex(), min, min, QModelIndex(), max + 1);
        m_data.move(min, max);
        emit endMoveRows();

        if(max - 1 != min) {
            emit beginMoveRows(QModelIndex(), max - 1, max - 1, QModelIndex(), min);
            m_data.move(max - 1, min);
            emit endMoveRows();
        }

        return checkWin();
    }
    return false;
}

bool GameModel::checkWin()
{
    int gridSqrdSize = m_gridSize * m_gridSize;

    for(int i = 0; i < gridSqrdSize; i++) {
        if(i != m_data.at(i)->getNumber() - 1){
            return false;
        }
    }
    return true;
}

int GameModel::findVoidCellId(int oldPos)
{
    int newPos = -1;
    int gridSqrdSize = m_gridSize * m_gridSize;
    int tempL = oldPos - 1;
    int tempR = oldPos + 1;
    int tempD = oldPos - m_gridSize;
    int tempU = oldPos + m_gridSize;

    if(tempL > -1 && tempL < gridSqrdSize && m_data.at(tempL)->getNumber() == gridSqrdSize) {
        newPos = tempL;
    }
    if(tempR > -1 && tempR < gridSqrdSize && m_data.at(tempR)->getNumber() == gridSqrdSize) {
        newPos = tempR;
    }
    if(tempD > -1 && tempD < gridSqrdSize && m_data.at(tempD)->getNumber() == gridSqrdSize) {
        newPos = tempD;
    }
    if(tempU > -1 && tempU < gridSqrdSize && m_data.at(tempU)->getNumber() == gridSqrdSize) {
        newPos = tempU;
    }

    return newPos;
}

bool GameModel::checkIsValid()
{   
    int e = 0;
    int summ = 0;
    int gridSqrdSize = m_gridSize * m_gridSize;


    for(int i = 0; i < gridSqrdSize; i++){
        if(m_data.at(i)->getNumber() == gridSqrdSize){
            e = m_gridSize - floor(i / m_gridSize);
            continue;
        }
        for(int j = i + 1; j < gridSqrdSize; j++){
            if(m_data.at(i)->getNumber() > m_data.at(j)->getNumber()){
                summ += 1;
            }
        }
    }
    summ += e;

    return m_gridSize % 2 ? !((summ - e) % 2) : (summ % 2);
}


void GameModel::shuffle()
{
    int temporaryValue;
    int gridSqrdSize = m_gridSize * m_gridSize;

    int min;
    int max;

    emit beginResetModel();

    for(int ind = gridSqrdSize - 1; ind > 0; ind--){
        temporaryValue = ceil(rand() % (ind + 1));
        min = ind < temporaryValue ? ind : temporaryValue;
        max = ind < temporaryValue ? temporaryValue : ind;

        m_data.move(min, max);
        if(max - 1 != min) {
            m_data.move(max - 1, min);
        }
    }
    emit endResetModel();
}
