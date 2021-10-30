
#ifndef CELLS_H
#define CELLS_H

class Cell;

#include <map>


//***
// This class serves as a data structure containing the cells which is used to
// lookup adjacent cells in order to determine liveliness.
//***
class Cells
{
public:

    Cells();
    ~Cells();

    void add(Cell* cell);

    // This method updates all the cells in the map.
    void updateAll();

    // This method is used to retrieve the adjacent cells.
    Cell* get(std::pair<unsigned int, unsigned int> idx) const;

protected:

    // This method is used to update the liveliness based upon
    // the neighboring cells.
    void updateCell(Cell* cell);

private:
    // The data structure of cells which is a map of indices to cell pointers.
    std::map<std::pair<unsigned int, unsigned int> , Cell*> m_cells;
};

#endif // CELLS_H
