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

//构造函数
two_players::two_players(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    //固定窗口
    this->resize(wwidth,wheight);
    this->setFixedSize(wwidth,wheight);

    //初始化蛇身
    QRectF rect(600,180,nodeWidth,nodeHeight);
    snake.append(rect);
    for(int i = 0; i < s ;++i)
        addTop();

    QRectF rect1(300,180,nodeWidth,nodeHeight);
    snake1.append(rect1);
    for(int i = 0; i < s ;++i)
        addTop1();


    //开启定时器
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),SLOT(timeout()));

    //获取随机数
    qsrand(randtime.msec()+randtime.second()*1000); //以当前时间ms为随机种子

}
//析构函数
two_players::~two_players()
{
    delete ui;
}
//按键控制
void two_players::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Up:
        if(moveFlag != DIR_DOWN && gameStart == 1)
            moveFlag = DIR_UP;
        break;
    case Qt::Key_Down:
        if(moveFlag != DIR_UP && gameStart == 1)
            moveFlag = DIR_DOWN;
        break;
    case Qt::Key_Left:
        if(moveFlag != DIR_RIGHT && gameStart == 1)
            moveFlag = DIR_LEFT;
        break;
    case Qt::Key_Right:
        if(moveFlag != DIR_LEFT && gameStart == 1)
            moveFlag = DIR_RIGHT;
        break;
    case Qt::Key_W:
        if(moveFlag1 != DIR_S && gameStart == 1)
            moveFlag1 = DIR_W;
        break;
    case Qt::Key_S:
        if(moveFlag1 != DIR_W && gameStart == 1)
            moveFlag1 = DIR_S;
        break;
    case Qt::Key_A:
        if(moveFlag1 != DIR_D && gameStart == 1)
            moveFlag1 = DIR_A;
        break;
    case Qt::Key_D:
        if(moveFlag1 != DIR_A && gameStart == 1)
            moveFlag1 = DIR_D;
        break;
    case Qt::Key_Space:
        if(gameStart == false){
            gameStart = true;
            timer->start(time);
        }else{
            gameStart = false;
            timer->stop();
        }
        break;
    default:
        break;
    }

}
//定时器
void two_players::timeout(){
    if(count % 50 + 1 != 50){
        crash_head(snake,snake1);
        if(eaten(snake[0]))
            eaten_flag = 1;
        if(eaten(snake1[0]))
            eaten_flag1 = 1;
        if(dead(snake) && dead_flag == 0)
            dead_flag = 1;
        if(dead(snake1) && dead_flag1 == 0)
            dead_flag1 = 1;
        bite_tie(snake,snake1);
        crash(snake[0],snake1[0]);
        if(dead_flag || dead_flag1)
        {
            timer->stop();
            QMessageBox box(QMessageBox::Question,"","again?");
            if(dead_flag == 1)
                box.setText("右方阵亡！");
            if(dead_flag1 == 1)
                box.setText("左方阵亡！");
            box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.setButtonText (QMessageBox::Cancel,QString("取 消"));
            // 弹出对话框
            int ret = box.exec();
            switch (ret) {
                case QMessageBox::Ok:
                    {
                    moveFlag = DIR_UP;
                    moveFlag1 = DIR_W;

                    QRectF rect(600,180,nodeWidth,nodeHeight);
                    QList<QRectF> shadow;
                    shadow.append(rect);
                    int zanshi = s;
                    while(zanshi--){
                        QPointF leftTop;
                        QPointF rightBotom;
                        if(shadow[0].y() - nodeHeight < 0){
                            leftTop = QPointF(shadow[0].x(),this->height() - nodeHeight);
                            rightBotom = QPointF(shadow[0].x() + nodeWidth,this->height());
                            shadow.insert(0,QRectF(leftTop,rightBotom));
                        }else{
                            leftTop = QPointF(shadow[0].x(),shadow[0].y()-nodeHeight);
                            rightBotom = shadow[0].topRight();
                            shadow.insert(0,QRectF(leftTop,rightBotom));
                        }
                    }
                    snake = shadow;

                    QRectF rect1(300,180,nodeWidth,nodeHeight);
                    QList<QRectF> shadow1;
                    shadow1.append(rect1);
                    int zanshi1 = s;
                    while(zanshi1--){
                        QPointF leftTop1;
                        QPointF rightBotom1;
                        if(shadow1[0].y() - nodeHeight < 0){
                            leftTop1 = QPointF(shadow1[0].x(),this->height() - nodeHeight);
                            rightBotom1 = QPointF(shadow1[0].x() + nodeWidth,this->height());
                            shadow1.insert(0,QRectF(leftTop1,rightBotom1));
                        }else{
                            leftTop1 = QPointF(shadow1[0].x(),shadow1[0].y()-nodeHeight);
                            rightBotom1 = shadow1[0].topRight();
                            shadow1.insert(0,QRectF(leftTop1,rightBotom1));
                        }
                    }
                    snake1 = shadow1;
                    gameStart = false;
                    timer->stop();
                    break;
                    }
                case QMessageBox::Cancel:
                    {
                    this->close();
                    break;
                    }
                }
            dead_flag = 0;
            dead_flag1 = 0;
        }
    }else{
        count = 0;
        int cnt = 1;
        int cnt1 = 1;
        if(eaten_flag == 1)
            cnt = 2;
            while(cnt--){
                switch (moveFlag) {
                    case DIR_UP:
                        addTop();
                        break;
                    case DIR_DOWN:
                        addDown();
                        break;
                    case DIR_LEFT:
                        addLeft();
                        break;
                    case DIR_RIGHT:
                        addRight();
                        break;
                    default:
                        break;
                }
            }
            if(eaten_flag1 == 1)
                cnt1 = 2;
                while(cnt1--){
                    switch (moveFlag1) {
                        case DIR_W:
                            addTop1();
                            break;
                        case DIR_S:
                            addDown1();
                            break;
                        case DIR_A:
                            addLeft1();
                            break;
                        case DIR_D:
                            addRight1();
                            break;
                        default:
                            break;
                    }
                }
        deleteLast();
        deleteLast1();
        update();
    }
    count ++;
}
//绘画函数
void two_players::paintEvent(QPaintEvent *event){
    //背景图片与右蛇
    QPixmap pix;
    pix.load(":/new/prefix1/resource/dessert.png");
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    painter.drawPixmap(0,0,wwidth,wheight,pix);
    pen.setColor(Qt::black);
    brush.setColor(Qt::darkMagenta);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    for(int i = 0;i<snake.length();++i){
        painter.drawRect(snake[i]);
    }
    //左蛇
    QPainter painter3(this);
    QPen pen3;
    QBrush brush3;
    pen3.setColor(Qt::black);
    brush3.setColor(Qt::green);
    brush3.setStyle(Qt::SolidPattern);
    painter3.setPen(pen3);
    painter3.setBrush(brush3);
    for(int i = 0;i<snake1.length();++i){
        painter3.drawRect(snake1[i]);
    }
    //绘制障碍物
    QPainter painter0(this);
    QPen pen0;
    QBrush brush0;
    pen0.setColor(Qt::gray);
    brush0.setColor(Qt::gray);
    brush0.setStyle(Qt::Dense3Pattern);
    painter0.setPen(pen0);
    painter0.setBrush(brush0);
    QRect a = QRect(0,0,bian1,bian1);
    QRect b = QRect(wwidth - bian1,0,bian1,bian1);
    QRect c = QRect(0,wheight - bian1,bian1,bian1);
    QRect d = QRect(wwidth - bian1,wheight - bian1,bian1,bian1);
    QRect e = QRect((wwidth - bian2)/2,(wheight - bian2)/2,bian2,bian2);
    painter0.drawRect(a);
    painter0.drawRect(b);
    painter0.drawRect(c);
    painter0.drawRect(d);
    painter0.drawRect(e);
    //文字提示
    if(!timer->isActive()){
    QPainter painter5(this);
    QPen pen5;
    pen5.setColor(Qt::black);
    painter5.setFont(QFont("楷体",20));
    painter5.drawText(250,50,"按空格键开始/暂停游戏");
    }
    //食物
    QPainter painter2(this);
    QPen pen2;
    QBrush brush2;
    pen2.setColor(Qt::red);
    brush2.setColor(Qt::red);
    brush2.setStyle(Qt::SolidPattern);
    painter2.setPen(pen2);
    painter2.setBrush(brush2);
    if(eaten_flag || eaten_flag1){
        eaten_flag = 0;
        eaten_flag1 = 0;
        fx = qrand() % 940 + 10;    //产生10-920的随机整数
        fy = qrand() % 700 + 10;    //产生10-710的随机整数
        while((fx>0&&fx<bian1&&fy>0&&fy<bian1) ||
              (fx>wwidth - bian1&&fx<wwidth&&fy>0&&fy<bian1) ||
              (fx>0&&fx<bian1&&fx>wheight - bian1&&fy<wheight) ||
              (fx>wwidth - bian1&&fx<wwidth&&fy>wheight - bian1&&fy<wheight) ||
              (fx>(wwidth - bian2)/2&&fx<(wwidth - bian2)/2 + bian2&&fy>(wheight - bian2)/2&&fy<(wheight - bian2)/2 +bian2))
        {
            fx = qrand() % 940 + 10;    //产生10-920的随机整数
            fy = qrand() % 700 + 10;    //产生10-710的随机整数
        }
    }
    QRect food(fx,fy,fw,fh);
    painter2.drawEllipse(food);
}
//判断是否吃到食物
bool two_players::eaten(QRectF a){
    int distance = pow(pow(fx - a.x(),2) + pow(fy - a.y(),2),0.5);
    if(distance <= 10)
        return true;
    else
        return false;
}
//判断是否咬尾
bool two_players::dead(QList<QRectF> a){
    for(int i = 1;i<a.length();++i)
        if(a[0].x() == a[i].x() && a[0].y() == a[i].y())
               return true;
    return false;
}
//判断哪方咬尾
void two_players::bite_tie(QList<QRectF> a,QList<QRectF> b){
    for(int i = 1;i<a.length();++i)
        if(b[0].x() == a[i].x() && b[0].y() == a[i].y())
            dead_flag1 = 1;
    for(int i = 1;i<b.length();++i)
        if(a[0].x() == b[i].x() && a[0].y() == b[i].y())
            dead_flag = 1;
}
//判断是否撞到障碍物
void two_players::crash(QRectF a,QRectF b){
    if((a.x()>0&&a.x()<bian1&&a.y()>0&&a.y()<bian1) ||
       (a.x()>=wwidth - bian1&&a.x()<wwidth&&a.y()>0&&a.y()<bian1) ||
       (a.x()>0&&a.x()<bian1&&a.y()>=wheight - bian1&&a.y()<wheight) ||
       (a.x()>=wwidth - bian1&&a.x()<wwidth&&a.y()>=wheight - bian1&&a.y()<wheight) ||
       (a.x()>=(wwidth - bian2)/2&&a.x()<(wwidth - bian2)/2 + bian2&&a.y()>(wheight - bian2)/2&&a.y()<(wheight - bian2)/2 +bian2))
        dead_flag = 1;

    if((b.x()>0&&b.x()<bian1&&b.y()>0&&b.y()<bian1) ||
       (b.x()>=wwidth - bian1&&b.x()<wwidth&&b.y()>0&&b.y()<bian1) ||
       (b.x()>0&&b.x()<bian1&&b.y()>=wheight - bian1&&b.y()<wheight) ||
       (b.x()>=wwidth - bian1&&b.x()<wwidth&&b.y()>=wheight - bian1&&b.y()<wheight) ||
       (b.x()>=(wwidth - bian2)/2&&b.x()<(wwidth - bian2)/2 + bian2&&b.y()>(wheight - bian2)/2&&b.y()<(wheight - bian2)/2 +bian2))
        dead_flag1 = 1;
}
//判断是否头相撞
void two_players::crash_head(QList<QRectF> a,QList<QRectF> b){
    if(a[0].x() == b[0].x() && a[0].y() == b[0].y())
    {
        if(a.length()>b.length())
            dead_flag1 = 1;
        if(a.length()<b.length())
            dead_flag = 1;
    }
}
