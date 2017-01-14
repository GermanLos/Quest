#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QStringList>
#include <QMessageBox>
#include <QFont>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(640, 480);
    player = new Player();
    scen = new Parser();
    QFont font = ui->textBrowser->font();
    font.setPixelSize(13);
    font.setFamily("Tahoma");
    QFont fontMenue = ui->textBrowser->font();
    fontMenue.setPixelSize(12);
    fontMenue.setFamily("Tahoma");
    ui->textBrowser->setFont(font);
    ui->action_1->setFont(font);
    ui->action_2->setFont(font);
    ui->action_3->setFont(font);
    ui->action_4->setFont(font);
    ui->action_load->setFont(fontMenue);
    ui->action_newGame->setFont(fontMenue);
    ui->action_options->setFont(fontMenue);
    ui->action_quit->setFont(fontMenue);
    ui->action_save->setFont(fontMenue);
    ui->ico_hp->hide();
    ui->ico_money->hide();
    ui->label_hp->hide();
    ui->label_money->hide();

    // Нижний бар с РПГ элементами.
    ui->label_hp->setText(QString::number(player->hp));
    ui->label_hp->setAlignment(Qt::AlignCenter);
    ui->label_money->setText(QString::number(player->money));
    ui->label_money->setAlignment(Qt::AlignCenter);

    scen->pointer = player->pointer;
    scen->file_path = "./room.dat";

    scen->readScen();
    showAll();

    connect(ui->action_1, SIGNAL(clicked()), this, SLOT(clicked_b1()));
    connect(ui->action_2, SIGNAL(clicked()), this, SLOT(clicked_b2()));
    connect(ui->action_3, SIGNAL(clicked()), this, SLOT(clicked_b3()));
    connect(ui->action_4, SIGNAL(clicked()), this, SLOT(clicked_b4()));
    connect(ui->action_save, SIGNAL(clicked(bool)), this, SLOT(clicked_save()));
    connect(ui->action_load, SIGNAL(clicked(bool)), this, SLOT(clicked_load()));
    connect(ui->action_newGame, SIGNAL(clicked(bool)), this, SLOT(clicked_newG()));
    connect(ui->action_options, SIGNAL(clicked(bool)), this, SLOT(clicked_options()));
    connect(ui->action_quit, SIGNAL(clicked(bool)), this, SLOT(close()));
}

Widget::~Widget()
{
    delete ui;
    delete player;
    delete scen;
}

//PUBLIC SIGNALS:
void Widget::clicked_b1()
{
    QStringList sl = scen->returnElement(&scen->progress);
    QStringList sl2 = scen->returnElement(&scen->skills);

    // Увеличиваем один из скиллов
    skillUp(&sl2, 0);
    // Увеличиваем указатель(текущее положение на линии сюжета)
    scen->pointer += safeAt(&sl, 0).toInt();
    scen->readScen();
    showAll();
    qDebug() << "clicked_b1 is clicked" << player->hp << player->money <<
            player->force << player->oratory << scen->pointer;
}

void Widget::clicked_b2()
{
    QStringList sl = scen->returnElement(&scen->progress);
    QStringList sl2 = scen->returnElement(&scen->skills);

    // Увеличиваем один из скиллов
    skillUp(&sl2, 2);
    // Увеличиваем указатель(текущее положение на линии сюжета)
    scen->pointer += safeAt(&sl, 1).toInt();
    scen->readScen();
    showAll();
    qDebug() << "clicked_b2 is clicked" << player->hp << player->money <<
            player->force << player->oratory << scen->pointer;
}

void Widget::clicked_b3()
{
    QStringList sl = scen->returnElement(&scen->progress);
    QStringList sl2 = scen->returnElement(&scen->skills);

    // Увеличиваем один из скиллов
    skillUp(&sl2, 4);
    // Увеличиваем указатель(текущее положение на линии сюжета)
    scen->pointer += safeAt(&sl, 2).toInt();
    scen->readScen();
    showAll();
    qDebug() << "clicked_b3 is clicked" << player->hp << player->money <<
            player->force << player->oratory << scen->pointer;
}

void Widget::clicked_b4()
{
    QStringList sl = scen->returnElement(&scen->progress);
    QStringList sl2 = scen->returnElement(&scen->skills);

    // Увеличиваем один из скиллов
    skillUp(&sl2, 6);
    // Увеличиваем указатель(текущее положение на линии сюжета)
    scen->pointer += safeAt(&sl, 3).toInt();
    scen->readScen();
    showAll();
    qDebug() << "clicked_b4 is clicked" << player->hp << player->money <<
            player->force << player->oratory << scen->pointer;
}

void Widget::clicked_save()
{
    player->pointer = scen->pointer;
    player->saveProgress();
}

void Widget::clicked_load()
{
    player->loadProgress();
    scen->pointer = player->pointer;
    scen->readScen();
    ui->label_hp->setText(QString::number(player->hp));
    ui->label_money->setText(QString::number(player->money));
    showAll();
}

void Widget::clicked_newG()
{
    player->hp = 0;
    player->force = 0;
    player->money = 0;
    player->oratory = 0;
    player->pointer = 0;
    ui->label_hp->setText(QString::number(player->hp));
    ui->label_money->setText(QString::number(player->money));
    scen->pointer = player->pointer;
    scen->readScen();
    showAll();
    clicked_save();
    QMessageBox::about(this, "Предупреждение!", "Помните, Ваши мысли и действия важны. "
                                                "Большинство из них определят Вас как личность, "
                                                "некоторые повлияют на происходящее, а какие-то "
                                                "вообще могут оказаться фатальными — но об этом "
                                                "Вы узнаете не сразу.\n"
                                                "Как и в реальной жизни.\n"
                                                "Будьте внимательны. Оставайтесь собой.");
}

void Widget::clicked_options()
{
    QMessageBox::about(this, "Авторы", "Программист:\tВадим Герман\n"
                                          "(vk.com/id326323831)\n\n"
                                          "Сценарист:\t\tВладимир Рогозин\n"
                                          "(vk.com/id101114864)\n\n"
                                          "Художник:\t\tАля Чадская\n"
                                          "(vk.com/80infinity08)\n\n"
                                          "Редактор:\t\tИрина Лютикова\n"
                                          "(vk.com/paulo_doctor)");
}

//PARSE, CALCULATE AND SHOW:
void Widget::showButtons()
{
    QStringList sl = scen->returnElement(&scen->buttons);
    QStringList slAvalible = scen->returnElement(&scen->moreButtons);

    if(safeAt(&sl, 0) != "None" && buttonIsAvalible(&slAvalible, 0))
    {
        ui->action_1->setText(safeAt(&sl, 0));
        ui->action_1->show();
    }
    else
        ui->action_1->hide();

    if(safeAt(&sl, 1) != "None" && buttonIsAvalible(&slAvalible, 2))
    {
        ui->action_2->setText(safeAt(&sl, 1));
        ui->action_2->show();
    }
    else
        ui->action_2->hide();

    if(safeAt(&sl, 2) != "None" && buttonIsAvalible(&slAvalible, 4))
    {
        ui->action_3->setText(safeAt(&sl, 2));
        ui->action_3->show();
    }
    else
        ui->action_3->hide();

    if(safeAt(&sl, 3) != "None" && buttonIsAvalible(&slAvalible, 6))
    {
        ui->action_4->setText(safeAt(&sl, 3));
        ui->action_4->show();
    }
    else
        ui->action_4->hide();
}

void Widget::showAll()
{
    player->force = player->hp - player->money;
    player->oratory = player->hp + player->money;

    if(scen->image != "None")
    {
        ui->label_img->show();
        ui->label_img->setPixmap(QPixmap(scen->image));
    }
    else
        ui->label_img->hide();
    ui->textBrowser->setText(scen->text);
    showButtons();
// Sound пока не юзаем
//    if(scen->sound != "None")
//    {
//        sound = new QSound(scen->sound);
//        sound->play();
    //    }
}

void Widget::skillUp(QStringList *element, int i)
{
    // Читаем символ
    QChar ch = safeAt(element, i)[0];
    // Переводим в целочисленное
    int x = ch.toLatin1();
    switch(x)
    {
        case 104: player->hp += safeAt(element, i + 1).toInt();
                  ui->label_hp->setText(QString::number(player->hp));
        break;
        case 109: player->money += safeAt(element, i + 1).toInt();
                  ui->label_money->setText(QString::number(player->money));
        break;
        case 102: // now nothing
        break;
        case 111: // now nothing
        break;
        default: qDebug() << "Никакой скил не был изменён";
        break;
    }
}

bool Widget::buttonIsAvalible(QStringList *element, int i)
{
    // Читаем символ
    QChar ch = safeAt(element, i)[0];
    // Переводим в целочисленное
    int firstElement = ch.toLatin1();
    int secondElement = safeAt(element, i + 1).toInt();

    /* Если элемент равен идентификатору одного из скиллов
     * то проверям следующий элемент. Если он меньше или равен
     * соответствующего скилла игрока то возвращаем false.
     **/
    switch(firstElement)
    {
        case 104: if(secondElement >= 0)
                  {
                      qDebug() << "Crazy >= 0";
                      if(secondElement <= player->hp)
                          return true;
                      else
                          return false;
                  }
                  else
                  {
                      qDebug() << "Crazy < 0";
                      if(secondElement * -1 > player->hp)
                          return true;
                      else
                          return false;
                  }

        break;
        case 109: if(secondElement >= 0)
                    {
                        qDebug() << "paranoya >= 0";
                        if(secondElement <= player->money)
                            return true;
                        else
                            return false;
                    }
                    else
                    {
                        qDebug() << "paranoya < 0";
                        if(secondElement * -1 > player->money)
                            return true;
                        else
                            return false;
                    }

        break;
        case 102: if(secondElement >= 0)
                    {
                        qDebug() << "paraoya - crazy < 0";
                        if(secondElement <= player->force)
                            return true;
                        else
                            return false;
                    }
                    else
                    {
                        qDebug() << "paraoya - crazy < 0";
                        if(secondElement * -1 > player->force)
                            return true;
                        else
                            return false;
                    }

        break;
        case 111: if(secondElement >= 0)
                    {
                        qDebug() << "paraoya + crazy > 0";
                        if(secondElement <= player->oratory)
                            return true;
                        else
                            return false;
                    }
                    else
                    {
                        qDebug() << "paraoya + crazy < 0";
                        if(secondElement * -1 > player->oratory)
                            return true;
                        else
                            return false;
                    }

        break;
        default: return true;
        break;
    }
}
