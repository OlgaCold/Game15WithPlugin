#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>

class Block : public QObject
{
    Q_OBJECT

public:
    explicit Block( QObject *parent = nullptr);
    Block(int number, bool state);

    int getNumber() ;
    void setNumber(int num);
    bool getState() ;
    void setState(bool state);
signals:


public slots:

private:
    int number;
    bool isVoid;
};

#endif // BLOCK_H
