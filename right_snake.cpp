#include "two_players.h"
#include "ui_widget.h"
#include <qpainter.h>
#include <math.h>
#include <qdebug.h>
#include <qthread.h>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qcolor.h>

void two_players::addTop(){
    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].y() - nodeHeight < 0){
        leftTop = QPointF(snake[0].x(),this->height() - nodeHeight);
        rightBotom = QPointF(snake[0].x() + nodeWidth,this->height());
        snake.insert(0,QRectF(leftTop,rightBotom));
    }else{
        leftTop = QPointF(snake[0].x(),snake[0].y()-nodeHeight);
        rightBotom = snake[0].topRight();
        snake.insert(0,QRectF(leftTop,rightBotom));
    }
}
void two_players::addDown(){
    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].y() + nodeHeight > wheight ){
        leftTop = QPointF(snake[0].x(),0);
        rightBotom = QPointF(snake[0].x() + nodeWidth,nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }else{
        leftTop = QPointF(snake[0].x(),snake[0].y()+nodeHeight);
        rightBotom = QPointF(leftTop.x()+nodeWidth,leftTop.y()+nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }
}
void two_players::addLeft(){
    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].x() - nodeWidth < 0 ){
        leftTop = QPointF(wwidth - nodeWidth,snake[0].y());
        rightBotom = QPointF(leftTop.x()+nodeWidth,leftTop.y()+nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }else{
        leftTop = QPointF(snake[0].x()-nodeWidth,snake[0].y());
        rightBotom = QPointF(leftTop.x()+nodeWidth,leftTop.y()+nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }
}
void two_players::addRight(){
    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].x() + nodeWidth > wwidth ){
        leftTop = QPointF(0,snake[0].y());
        rightBotom = QPointF(leftTop.x()+nodeWidth,leftTop.y()+nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }else{
        leftTop = QPointF(snake[0].x()+nodeWidth,snake[0].y());
        rightBotom = QPointF(leftTop.x()+nodeWidth,leftTop.y()+nodeHeight);
        snake.insert(0,QRectF(leftTop,rightBotom));
    }
}

void two_players::deleteLast(){
    snake.removeLast();
}
