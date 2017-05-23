#ifndef ORGADD_H
#define ORGADD_H


#include <QDir>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDebug>

#include <stdio.h>
#include <Windows.h>


#define MAX_SIZE_PACKET 1024*10


class orgadd
{
public:

    orgadd(char* parpall);



private:

    void loadoui();
    QString orglib;

};

#endif // ORGADD_H
