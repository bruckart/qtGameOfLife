

#include "GameOfLifeWidget.h"
#include "Cell.h"

#include <QPainter>
#include <QRandomGenerator>

#include <iostream>






const unsigned int NUM_ROWS = 72;
const unsigned int NUM_COLS = 96;

static const int GRID_STEP = 8;


inline qreal round(qreal val, int step)
{
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}


GameOfLifeWidget::GameOfLifeWidget(QWidget* parent)
:
    QWidget(parent),
    m_timer(new QTimer(this))
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setFixedSize(QSize(768, 576));

    m_scene = new MyGraphicsScene(this);
    m_scene->setSceneRect(0, 0, 768, 576);

    m_view = new QGraphicsView(this);
    m_view->setScene(m_scene);

    populateScene();

    // setWindowTitle(tr("John Conway's Game of Life"));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerEvent()));

    m_timer->start(500);
}

GameOfLifeWidget::~GameOfLifeWidget()
{
    m_timer->stop();

    delete m_timer;

    delete m_scene;

    delete m_view;
}

void GameOfLifeWidget::timerEvent()
{
    m_cells.updateAll();
}


void GameOfLifeWidget::keyPressEvent(QKeyEvent* event)
{
    std::clog << "GameOfLifeWidget::keyPressEvent" << std::endl;
    // if (event->key() == Qt::Key_Space)
    // {
    //     std::clog << "REGENERON" << std::endl;
    //     for (int y = 0; y < NUM_ROWS; y++)
    //     {
    //         for (int x = 0; x < NUM_COLS; x++)
    //         {
    //             CellIndex index(x, y);
    //             Cell* cell = m_cells.get(index);

    //             // Randomly assign the cells as alive or dead.
    //             (rand() %2) ? cell->setAlive() : cell->setDead();
    //         }
    //     }
    //     update();
    // }
}

void GameOfLifeWidget::populateScene()
{
    std::clog << "GameOfLifeWidget::populateScene()" << std::endl;

    // Create a grid that contains cells on a 2D grid with a random assignment
    // of alive or dead.

    for (int y = 0; y < NUM_ROWS; ++y)
    {
        for (int x = 0; x < NUM_COLS; ++x)
        {
            auto index = std::make_pair(x, y);
            Cell* cell = new Cell(index);

            // Assign 33% of the cells as ALIVE, 33% as DEAD, and 33% as NONE.
            // Generate a random number between 0 
            quint32 n = QRandomGenerator::global()->bounded(0, 100);
            if (n >= 0 && n < 34)
            {
                cell->setAlive();
            }
            else if (n >=34 && n < 67)
            {
                cell->setDead();
            }
            else if (n >= 67)
            {
                cell->setNone();
            }

            // Add the cell to the data structure of the cells.
            // m_cells.add(index, cell);
            m_cells.add(cell);

            m_scene->addItem(cell);
        }
    }
}


MyGraphicsScene::MyGraphicsScene(QObject *parent)
:
    QGraphicsScene(parent)
{
}

MyGraphicsScene::~MyGraphicsScene()
{
}

void MyGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    int step = GRID_STEP;
    painter->setPen(QPen(QColor(220, 220, 255, 125)));

    // draw horizontal grid
    qreal start = round(rect.top(), step);
    if (start > rect.top())
    {
        start -= step;
    }
    for (qreal y = start - step; y < rect.bottom(); )
    {
        y += step;
        painter->drawLine(rect.left(), y, rect.right(), y);
    }

    // now draw vertical grid
    start = round(rect.left(), step);
    if (start > rect.left())
    {
        start -= step;
    }
    for (qreal x = start - step; x < rect.right(); ) 
    {
        x += step;
        painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}