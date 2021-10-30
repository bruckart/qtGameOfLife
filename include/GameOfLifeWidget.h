
#ifndef GAMEOFLIFEWIDGET_H
#define GAMEOFLIFEWIDGET_H


#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Cells.h"

class MyGraphicsScene;


//***
// This widget draws cells in accordance to John Conway's Game of Life.
//***
class GameOfLifeWidget : public QWidget
{
    Q_OBJECT

public:

    GameOfLifeWidget(QWidget* parent=0);
    virtual ~GameOfLifeWidget();

public slots:

    void timerEvent();

private:

    void keyPressEvent(QKeyEvent* event);

    void populateScene();

    Cells m_cells;

    QTimer* m_timer;

    QGraphicsView*   m_view;
    MyGraphicsScene* m_scene;
};


//***
// This QGraphicsScene class is used to draw a grid background for which the cells
// are drawn.
//***
class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    MyGraphicsScene(QObject *parent);
    virtual ~MyGraphicsScene();

protected:

   void drawBackground(QPainter * painter, const QRectF & rect) override;

};

#endif // GAMEOFLIFEWIDGET_H