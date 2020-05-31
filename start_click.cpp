#include "start_click.h"
#include <QPixmap>
#include <QIcon>
start_click::start_click(QString button):QPushButton(0){
    QPixmap btn(button);
    this->setFixedSize(btn.width(),btn.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(btn);
    this->setIconSize(QSize(btn.width(),btn.height()));
}
