#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QString>
#include <QList>

class enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint enemy_pos READ get_ene_pos WRITE set_ene_pos)
public:
    explicit enemy(QList<QPoint*> way,QString img);
    void draw(QPainter *painter);
    void move();
    QPoint get_ene_pos();
    void set_ene_pos(QPoint _pos);

    //δʵ�ֺ���
    void ene_de_blood();//����Ѫ��
    void ene_dead();//����
signals:

public slots:
private:
    QList<QPoint*> enemy_way;
    QPoint enemy_pos;
    QPixmap enemy_img;
    int ene_blood;
};

#endif // ENEMY_H
