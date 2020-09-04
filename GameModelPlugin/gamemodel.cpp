#include "gamemodel.h"

GameModel::GameModel(QObject *parent)
    : QAbstractListModel(parent), gridSize(GRID_SIZE)
{
    for(int i = 0; i < gridSize*gridSize; i++){
        m_data.append(new Block(i + 1, false));
    }
    m_data.at(gridSize*gridSize - 1)->setState(true);
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
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
    QHash<int, QByteArray> blocks;
    blocks[DisplayRole] = "display";
    blocks[IsVoidRole] = "isvoid";
    return blocks;
}

void GameModel::mix()
{
    do{ GameModel::shuffle(); }
    while( !GameModel::checkIsValid() );
}

bool GameModel::move(int oldP)
{
    int newP;

    if(GameModel::findVoidCellId(oldP) != -1) {

        newP = findVoidCellId(oldP);

        int min = oldP < newP ? oldP : newP;
        int max = oldP < newP ? newP : oldP;

        emit beginMoveRows(QModelIndex(), min, min, QModelIndex(), max + 1);//max + 1
        m_data.move(min, max);
        emit endMoveRows();

        if(max - 1 != min) {
            emit beginMoveRows(QModelIndex(), max - 1, max - 1, QModelIndex(), min);//max - 1
            m_data.move(max - 1, min);
            emit endMoveRows();
        }

        if(GameModel::checkWin()){
            return true;
        }
    }
    return false;
}

bool GameModel::checkWin()
{
    int gridSqrdSize = gridSize * gridSize;

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
    int gridSqrdSize = gridSize * gridSize;
    int tempL = oldPos - 1;
    int tempR = oldPos + 1;
    int tempD = oldPos - gridSize;
    int tempU = oldPos + gridSize;

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
    int summ = 0;
    int e = gridSize;
    int gridSqrdSize = gridSize * gridSize;

    for(int i = 0; i < gridSqrdSize - 1; i++){
        for(int j = i + 1; j < gridSqrdSize - 1; j++){
            if(m_data.at(i)->getNumber() > m_data.at(j)->getNumber()){
                summ += 1;
            }
        }
    }
    summ += e;

    return !(summ % 2);
}

void GameModel::shuffle()
{
    int temporaryValue;
    int gridSqrdSize = gridSize * gridSize;

    int min;
    int max;

    emit beginResetModel();

    for(int ind = gridSqrdSize - 1; ind > 0; ind--){
        temporaryValue = ceil(rand() % (ind + 1));//ind?
        min = ind < temporaryValue ? ind : temporaryValue;
        max = ind < temporaryValue ? temporaryValue : ind;

        m_data.move(min, max);
        if(max - 1 != min) {
            m_data.move(max - 1, min);
        }
    }
    emit endResetModel();
}

/*bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}*/

/*Qt::ItemFlags GameModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}*/

/*bool GameModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool GameModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}*/
