#include "llcadd.h"

llcadd::llcadd()
{
    Init();

    QStringList NameFilter;
    NameFilter << "*.txt";
    QDir CurDir = QDir::current();
    CurDir.setFilter(QDir::Files|QDir::NoDotAndDotDot);
    CurDir.setNameFilters(NameFilter);
    for(uint i=0;i<CurDir.count();i++)
    {
        QString baseName = CurDir.entryInfoList().at(i).baseName();
        if(!baseName.compare("oui") || baseName.contains("llc")) continue;
        Add(baseName);
    }
}

//Load oui.txt
void llcadd::Init()
{
    //New Version Check
    QString OuiName;
    if(QFile("oui.txt").exists()){
        OuiName = "oui.txt";
    }else{
        OuiName = ":/lib/oui.txt";
    }
    //Open
    QFile OuiFile(OuiName);
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

void llcadd::Add(QString baseName)
{

    QFile SrcFile(baseName + ".txt");
    if(!SrcFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        printf("%s\n","Can't Open arp result");
        system("pause");
        return;
    }
    QFile DstFile(baseName + "_llc.txt");
    if(!DstFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        printf("%s\n","Can't Open arp result");
        system("pause");
        return;
    }
    char *ip = new char[20];
    char *mac = new char[20];
    char *macllc = new char[10];
    QTextStream in(&SrcFile);
    QTextStream out(&DstFile);
    while (!in.atEnd()) {
        //Read line
        QString line = in.readLine();
        //Process line(line);
        if(line.contains("Interface:")){
            out << line << endl;
            continue;
        }
        if(line.contains("Internet Address") && line.contains("Physical Address")){
            line.append("        LLC");
            out << line << endl;
            continue;
        }

        if(line.contains("static") || line.contains("dynamic")){

            sscanf(line.toLocal8Bit().constData(),"%s%s", ip, mac);
            sscanf(mac,"%8s",macllc);
            QString ml(macllc);
            int start = llclib.indexOf(ml.toUpper(),Qt::CaseInsensitive);
            if (start < 0){
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
            line.append("  ");
            line.append(Dstline);
            out << line << endl;
            continue;
        }

    }
    printf("Success Add LLC to [%s_llc.txt]\n",baseName.toLocal8Bit().constData());

    delete(ip);
    delete(mac);
    delete(macllc);
    SrcFile.close();
    DstFile.close();
}

