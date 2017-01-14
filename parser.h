#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include <QDebug>

const QString safeAt(QStringList *sList, int i);
void simplifiedList(QStringList *s1);

class Parser
{
public:
    QString file_path;
    QString text;       //text
    QString buttons;    //b#b#b#None
    QString progress;   //1#2#-3#0
    QString image;      //img.png
    QString sound;      //sound.ogg
    QString skills;     //0#f.1#0#0
    QString moreButtons;//уровень скилла необходимый для того
                        //что бы вариант ответа был активный
    int pointer;
    QStringList transientList;

    Parser();
    Parser(QString path);
    // Чтение текущей сцены
    void readScen();
    // Возвращает текст кнопки, прогресс или скилл
    QStringList returnElement(QString *element);
    QStringList returnElementDot(QString *element);
};

#endif // PARSER_H
