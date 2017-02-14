#ifndef LLCADD_H
#define LLCADD_H


#include <QDir>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDebug>

#include <stdio.h>
#include <Windows.h>


#define MAX_SIZE_PACKET 1024*10


class llcadd
{
public:

    llcadd(char* parpall);



private:

    void loadoui();
    QString llclib;

};

#endif // LLCADD_H
