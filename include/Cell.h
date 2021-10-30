
#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <utility>


//***
// This class contains all the properties of a cell. It is a QGraphicsItem so 
// that it is drawn via the paint() method. The depiction of the cell depends upon
// it's liveliness.
//***
class Cell : public QGraphicsItem
{
public:
    enum Liveliness
    {
        ALIVE,
        DEAD, 
        NONE
    };

    Cell(std::pair<int, int> index);
    Cell(int row, int col);

    virtual ~Cell();

    void setAlive();
    void setDead();
    void setNone();

    bool isAlive() const;
    bool isDead() const;
    bool isNone() const;

    unsigned int x() const;
    unsigned int y() const;

    std::pair<unsigned int, unsigned int> index() const;

    QRectF boundingRect() const;

    QPainterPath shape() const;

    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* item, QWidget* widget);


    // This method prints the overall grid in ASCII format.
    std::ostream& print(std::ostream& os) const;

private:

    typedef std::pair<int, int> CellIndex;
    CellIndex m_index;

    Liveliness m_liveliness;
};

inline std::ostream& operator<<(std::ostream& os, const Cell& c)
{
    return c.print(os);
}

#endif // CELL_H
