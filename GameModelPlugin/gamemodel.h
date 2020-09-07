#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <cmath>

#include "block.h"

#define GRID_SIZE 4

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qint32 gridSize MEMBER m_gridSize CONSTANT)

public:
    explicit GameModel(QObject *parent = nullptr);
    ~GameModel();

    enum {
        DisplayRole,
        IsVoidRole = Qt::UserRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void mix();
    bool move(int oldP); //return true, if win

private:
    int m_gridSize;
    QList<Block*> m_data;

    bool checkWin() const;
    bool checkIsValid() const;
    int findVoidCellId(int oldPos) const;
    void shuffle();
};
