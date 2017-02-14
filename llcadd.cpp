#include "llcadd.h"

llcadd::llcadd(char *parpall)
{
    //Load oui.txt
    loadoui();

    //Open&Create File
    QFile SrcFile(parpall);
    if(!SrcFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        printf("%s\n","Can't Open Arp-All File!");
        system("pause");
        return;
    }
    QFile DstFile(SrcFile.fileName().append("-llc.txt"));
    if(!DstFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        printf("%s\n","Can't Create Result File!");
        system("pause");
        return;
    }
    QTextStream in(&SrcFile);
    QTextStream out(&DstFile);

    //Init
    char *ip = new char[100]; //Maybe IPv6
    char *mac = new char[100];
    char *macllc = new char[10];

    /* arp-all.txt
     *
     * Interface: 192.168.102.135 --- 0xe
     * Internet Address      Physical Address      Type
     * 192.168.102.2         00-50-56-f3-b8-2d     dynamic
     * 192.168.102.255       ff-ff-ff-ff-ff-ff     static
     * 255.255.255.255       ff-ff-ff-ff-ff-ff     static
     */
    while (!in.atEnd()) {
        //Read line
        QString line = in.readLine();
        //Process line(line);
        if(line.contains("Interface:")){
            out << line << endl;
            continue;
        }
        if(line.contains("Internet Address") && line.contains("Physical Address")){
            line.append("             LLC");
            out << line << endl;
            continue;
        }
        if(line.contains("static") || line.contains("dynamic")){
            sscanf(line.toLocal8Bit().constData(),"%s%s", ip, mac);
            sscanf(mac,"%8s",macllc);
            QString ml(macllc);
            int start = llclib.indexOf(ml.toUpper(),Qt::CaseInsensitive);
            if (start < 0){
                line.append("         Not Found");
                out << line << endl;
                continue;
            }
            start = start + 18;
            int end = start;
            QString Dstline;
            while(llclib.mid(end,1).compare("\n"))
            {
                Dstline.append(llclib.mid(end,1));
                end++;
            }
            line.append("        ");
            line.append(Dstline);
            out << line << endl;
            continue;
        }

    }
    printf("Success Add LLC to [%s]\n",DstFile.fileName().toLocal8Bit().constData());

    delete(ip);
    delete(mac);
    delete(macllc);
    SrcFile.close();
    DstFile.close();

}

//Load oui.txt
//Download URL: http://standards-oui.ieee.org/oui/oui.txt
void llcadd::loadoui()
{
    //Open oui.txt
    QFile OuiFile(":/lib/oui.txt");
    if(!OuiFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        printf("%s\n","Can't Open oui.txt");
        system("pause");
        return;
    }
    //Format Check & Output Oui Version
    QString OuiVer = OuiFile.readLine();
    if(!OuiVer.contains("Generated:")){
        printf("%s\n","oui.txt Format Error!");
        system("pause");
        return;
    }else{
        printf("Oui Version =%s\n",OuiVer.toLocal8Bit().constData());
    }
    //Load oui.txt
    llclib = OuiFile.readAll();
    OuiFile.close();
}
