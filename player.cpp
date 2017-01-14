#include "player.h"

#include <QFile>
#include <QTextStream>

Player::Player()
{
    loadProgress();
}

void Player::saveProgress()
{
    QFile f("./save.dat");

    if(f.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&f);
        ts << hp << ";" << money << ";" << force << ";" << oratory << ";" << pointer;
        f.close();
    }
    qDebug() << hp << money << force << oratory << pointer;
}

void Player::loadProgress()
{
    QFile f("./save.dat");
    QStringList sl;

    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&f);
        ts.setAutoDetectUnicode(true);
        ts.setGenerateByteOrderMark(false);
        QString s = ts.readAll();
        sl = s.split(QRegExp(";"), QString::SkipEmptyParts);
        f.close();
    }

    qDebug() << sl;

    hp = safeAt(&sl, 0).toInt();
    money = safeAt(&sl, 1).toInt();
    force = safeAt(&sl, 2).toInt();
    oratory = safeAt(&sl, 3).toInt();
    pointer = safeAt(&sl, 4).toInt();
}

