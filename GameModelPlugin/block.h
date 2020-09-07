#pragma once

#include <QObject>

class Block : public QObject
{
    Q_OBJECT

public:
    explicit Block(QObject *parent = nullptr, int m_number = 0, bool state = false);

    int getNumber() ;
    void setNumber(int num);
    bool getState() ;
    void setState(bool state);

private:
    int m_number;
    bool m_isVoid;
};
