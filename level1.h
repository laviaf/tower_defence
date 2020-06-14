#ifndef LEVEL1_H
#define LEVEL1_H

#include "way_point.h"
#include "enemy.h"
#include "tower_position.h"
#include "tower.h"

#include <QMainWindow>
#include <QList>

class level1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit level1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    //������˲���
    void loadwave(int ene_num);
    //���һ������
    void get_enemy(QList<way_point *> route);
    void updateScene();
    //�趨��һ��·��
    void set_route();
    //����¼�
    void mousePressEvent(QMouseEvent *event);
    bool can_buy_tower();
signals:

public slots:

private:
    QList<tower_position*> tow_base_list;
    //����λ��
    QList<enemy*> enemy_list;
    int base_Hp;
    QList<way_point*> route;
    //���˺���
    QList<tower*> tower_list;
    int money;
};

#endif // LEVEL1_H
