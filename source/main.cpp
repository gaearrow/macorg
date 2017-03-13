#include <QCoreApplication>

#include "llcadd.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc != 2){
        printf("Usage: %s arp-all.txt \n", argv[0]);
        return 0;
    }

    llcadd la(argv[1]);
    return a.exec();
}
