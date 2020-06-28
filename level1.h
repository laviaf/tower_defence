#ifndef LEVEL1_H
#define LEVEL1_H

#include "world_map.h"
#include "way_point.h"
#include "enemy.h"
#include "tower_position.h"
#include "tower.h"
#include "bullet.h"
#include "func_button.h"
#include "lose_window.h"
#include "win_window.h"

#include <QMainWindow>
#include <QList>

class world_map;
class tower_position;
class bullet;
class tower;
class enemy;
class func_button;
class lose_window;
class win_window;

class level1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit level1(world_map *map);

    void paintEvent(QPaintEvent *event);
    void play_music();
    void load_tower_position();

    //构造敌人波次
    bool loadwave();
    void remove_enemy(enemy* ene);
    //设定第一关路线
    void set_route();
    //鼠标事件
    void mousePressEvent(QMouseEvent *event);

    bool can_buy_tower(int s);
    void add_bullet(bullet *bul);
    void remove_bullet(bullet *bul);
    void remove_func_btn(func_button *btn);
    void remove_tower(tower *t);
    void money_reward();
    void restruct_money_reward(tower *t);
    void draw_WaveMoneyLife(QPainter *painter);
    void damage_life();
    QList<enemy*> get_ene_list();

signals:

public slots:
    void updateScene();
    void start_game();//加载首波敌人
private:
    QList<tower_position> tow_base_list;
    //塔基位置
    QList<enemy*> enemy_list;
//    int base_Hp;
    QList<way_point*> route;
    //敌人航线
    QList<tower*> tower_list;
    QList<bullet*> bullet_list;
    QList<func_button*> func_btn_list;

    int money;
    int life;
    int cur_wave;
    int wave_total;
    bool game_win;
    bool game_end;

    QImage life_;
    QImage gold_;
    QImage wave_;
    world_map *w_map;

    lose_window *lose;
    win_window *win;
};

#endif // LEVEL1_H
