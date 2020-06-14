#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QVector2D>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QList>

#include "way_point.h"
//�����������躽��

class enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint enemy_pos_current READ get_ene_pos WRITE set_ene_pos)
public:
    explicit enemy(QList<way_point *> route, int _num);
    void draw(QPainter *painter);
    void move();
    QPoint get_ene_pos();
    void set_ene_pos(QPoint _pos);
    bool is_dead();//�жϹ����������Ƿ�����
    ~enemy();
    //δʵ�ֺ���
    void ene_de_blood();//����Ѫ��
signals:

public slots:
private:
    way_point* enemy_dest_point;//������˵��н�
    QPoint enemy_pos_current;//���˵�ǰλ��
    QImage enemy_img;
    double walk_speed;
    int Hp_max;
    int Hp_current;
    int num;//�����л���ͬ�ؿ�����

};

#endif // ENEMY_H
