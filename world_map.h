#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <QMainWindow>
#include <QWidget>
#include "level1.h"
class world_map : public QMainWindow
{
    Q_OBJECT
public:
    explicit world_map(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    level1 *lev1_map;
};

#endif // WORLD_MAP_H
