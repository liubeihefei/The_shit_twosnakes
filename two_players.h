#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <qtimer.h>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class two_players : public QWidget
{
    Q_OBJECT

public:
    two_players(QWidget *parent = nullptr);
    ~two_players();

protected:
    //渲染绘图
    void paintEvent(QPaintEvent *event);
    //按键控制
    void keyPressEvent(QKeyEvent *event);
    //删除块
    void deleteLast();
    void deleteLast1();
    //蛇身运动基本逻辑
    void addTop();
    void addDown();
    void addLeft();
    void addRight();
    void addTop1();
    void addDown1();
    void addLeft1();
    void addRight1();
    //判断食物是否被吃掉
    bool eaten(QRectF a);
    //判断是否咬尾
    bool dead(QList<QRectF> a);
    void bite_tie(QList<QRectF> a,QList<QRectF> b);
    //判断是否撞到障碍物
    void crash(QRectF a,QRectF b);
    //判断是否头相撞
    void crash_head(QList<QRectF> a,QList<QRectF> b);

private:
    //定义方向枚举
    enum Direct{
        DIR_LEFT,
        DIR_RIGHT,
        DIR_UP,
        DIR_DOWN,
    };
    enum Direct1{
        DIR_W,
        DIR_S,
        DIR_A,
        DIR_D
    };
    Ui::Widget *ui;
    //蛇的表示
    QList<QRectF> snake;
    QList<QRectF> snake1;
    int s = 10;
    //方块宽高
    int nodeWidth = 10;
    int nodeHeight = 10;
    //方向标志位
    int moveFlag = DIR_UP;
    int moveFlag1 = DIR_W;
    //游戏开始位
    bool gameStart = false;
    //定时器
    QTimer* timer;
    int time = 1;
    int count = 0;
    //窗口宽高
    int wwidth = 960;
    int wheight = 720;
    //食物外界矩形的长宽,位置,是否吃完的标志位
    int fx = 450;
    int fy = 100;
    int fw = 10;
    int fh = 10;
    int eaten_flag = 0;
    int eaten_flag1 = 0;
    //随机数
    QTime randtime = QTime::currentTime();
    //死亡标志位
    int dead_flag = 0;
    int dead_flag1 = 0;
    //障碍物
    int bian1 = 50;
    int bian2 = 100;




protected slots:
    void timeout();
};
#endif // WIDGET_H
