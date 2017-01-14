#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <parser.h>
#include <QDebug>
#include <player.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    Parser *scen;
//    QSound *sound;
    Player *player;

    void showButtons();
    void showAll();
    // Проверяет, повышает ли какой либо скил данное действие
    void skillUp(QStringList *element, int i);
    // Возвращает доступен ли вариант ответа
    bool buttonIsAvalible(QStringList *element, int i);

private slots:
    void clicked_b1();
    void clicked_b2();
    void clicked_b3();
    void clicked_b4();
    void clicked_save();
    void clicked_load();
    void clicked_newG();
    void clicked_options();
};

#endif // WIDGET_H
