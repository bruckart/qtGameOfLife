

#include "Cell.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>


Cell::Cell(std::pair<int, int> index)
:
    m_index(index),
    m_liveliness(Cell::NONE)
{
}

Cell::Cell(int row, int col)
:
    m_index(std::pair<int, int>(row, col)),
    m_liveliness(Cell::NONE)
{
}

Cell::~Cell()
{
}

std::ostream& Cell::print(std::ostream& os) const
{
    os << "Cell (" << m_index.first << "," << m_index.second << ") | ";
    if (m_liveliness == 0)
    {
        os << "ALIVE";
    }
    else if (m_liveliness == 1)
    {
        os << "DEAD";
    }
    else if (m_liveliness == 2)
    {
        os << "NONE";
    }
    else
    {
        os << "?";
    }

    return os;
}

unsigned int Cell::x() const
{
    return m_index.first;
}

unsigned int Cell::y() const
{
    return m_index.second;
}

void Cell::setAlive()
{
    m_liveliness = Cell::ALIVE;
}

void Cell::setDead()
{
    m_liveliness = Cell::DEAD;
}

void Cell::setNone()
{
    m_liveliness = Cell::NONE;
}

bool Cell::isAlive() const
{
    return (m_liveliness == Cell::ALIVE ? true : false);
}

bool Cell::isDead() const
{
    return (m_liveliness == Cell::DEAD ? true : false);
}

bool Cell::isNone() const
{
    return (m_liveliness == Cell::NONE ? true : false);
}

std::pair<unsigned int, unsigned int> Cell::index() const
{
    return m_index;
}

QRectF Cell::boundingRect() const
{
    return QRectF(m_index.first*8, m_index.second*8, 8, 8);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(m_index.first*8, m_index.second*8, 8, 8);
    return path;
}


void Cell::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    if (m_liveliness == 2) return;

    QColor color;

    painter->setRenderHint(QPainter::Antialiasing);

    if (m_liveliness == 0) // ALIVE
    {
        color = QColorConstants::Svg::palegreen;
    }
    else if (m_liveliness == 1) // DEAD
    {
        color = QColorConstants::Svg::pink;
    }
    // else if (m_liveliness == 2) // NONE
    // {
    //     color = QColor(255, 255, 255);
    // }

    QPainterPath path;
    path.addRoundedRect(QRectF(m_index.first*8, m_index.second*8, 8, 8), 1, 1);
    
    QPen pen(QColorConstants::Svg::lightslategray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    // QPen pen(Qt::black, 1);
    painter->setPen(pen);

    painter->fillPath(path, color);
    painter->drawPath(path);
}
