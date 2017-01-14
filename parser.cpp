#include "parser.h"

#include <QFile>
#include <QTextStream>
#include <QRegExp>

Parser::Parser()
{
    file_path = "NONE";
}

Parser::Parser(QString path)
{
    file_path = path;
    readScen();
}

// Методы
void Parser::readScen()
{
    QFile f(file_path);

    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&f);
        ts.setAutoDetectUnicode(true);
        ts.setGenerateByteOrderMark(false);
        QString s = ts.readAll();
        transientList = s.split(QRegExp("\\[scen[0-9]{1,2}\\]"), QString::SkipEmptyParts);
        f.close();
    }
    transientList =
        safeAt(&transientList, pointer).split(QRegExp("\\[[a-z]{1,20}\\]"),
                                                       QString::SkipEmptyParts);

    simplifiedList(&transientList);

    text = safeAt(&transientList, 1);
    buttons = safeAt(&transientList, 2);
    progress = safeAt(&transientList, 3);
    image = safeAt(&transientList, 4);
    sound = safeAt(&transientList, 5);
    skills = safeAt(&transientList, 6);
    moreButtons = safeAt(&transientList, 7);

    text.replace(QRegExp("_"), "\n");
}

QStringList Parser::returnElement(QString *element)
{
    QStringList sl = element->split(QRegExp(";"), QString::SkipEmptyParts);
    simplifiedList(&sl);
    return sl;
}

QStringList Parser::returnElementDot(QString *element)
{
    QStringList sl = element->split(QRegExp("."), QString::SkipEmptyParts);
    simplifiedList(&sl);
    return sl;
}

// Функции
void simplifiedList(QStringList *sl)
{
    for(int i = 0; i < sl->length(); i++)
        sl->replace(i, QString(safeAt(sl, i)).simplified());
}

const QString safeAt(QStringList *sList, int i)
{
    if(i < sList->length())
        return sList->at(i);
    else
        qDebug() << "Выход за пределы QStringList";
        return "NONE";
}
