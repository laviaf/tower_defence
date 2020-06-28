#ifndef TOWER_H
#define TOWER_H

#include "bullet.h"
#include "enemy.h"
#include "level1.h"

#include <QPoint>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QObject>

class level1;
class enemy;

class tower : public QObject
{
    Q_OBJECT
public:
    explicit tower(QPoint pos, int t_num,level1 *game_1);
    void draw(QPainter *painter);
    void is_enemy_can_attack();
    void get_attacked_enemy(enemy *ene);
    void attack();
    void enemy_killed();
    void lose_sight();
    void upgrade();
    void removed();
    int get_updatecost();
    int get_destruct_bonus();
private slots:
    void shoot_bullet();

private:
    int fire_rate;
    int attack_range;
    int damage;
    int choose;
    int grade;
    QPoint t_pos;
    QImage t_img;
    QTimer *shoot_timer;
    enemy *attacked_enemy;
    level1* game;

    int update_cost;
    int destruct_bonus;
signals:

public slots:
};

#endif // TOWER_H
