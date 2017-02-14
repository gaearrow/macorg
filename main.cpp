#include <QCoreApplication>

#include "llcadd.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc != 2){
        printf("Usage: \n"
               "     macllc.exe c:\\xxx\\arp-all.txt\n"
               "     macllc.exe arp-all.txt\n");
        return 0;
    }

    llcadd la(argv[1]);
    return a.exec();
}
