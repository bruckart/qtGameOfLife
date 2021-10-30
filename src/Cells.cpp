
#include "Cell.h"
#include "Cells.h"

#include <QPainter>

#include <utility>
#include <iostream>


Cells::Cells()
:
    m_cells()
{
}

Cells::~Cells()
{
    // std::map<std::pair<unsigned int, unsigned int>, Cell*>::iterator it = 
    //     m_cells.begin();
    // if (it != m_cells.end())
    // {
    //     Cell* cell = it->second;
    //     delete cell;
    // }
    // m_cells.clear();
}

void Cells::add(Cell* cell)
{
    m_cells[cell->index()] = cell;
}

void Cells::updateAll()
{
    std::map<std::pair<unsigned int, unsigned int>, Cell*>::const_iterator it = m_cells.begin();
    for (; it != m_cells.end(); ++it)
    {
        // std::pair<int, int> idx  = it->first;
        Cell*               cell = it->second;
        updateCell(cell);
    }
}

void Cells::updateCell(Cell* cell)
{
    if (cell->isNone()) return;

    unsigned int numAliveNeighbors = 0;
    unsigned int numDeadNeighbors = 0;

    // Retrieve the adjacent cells.
    std::pair<unsigned int, unsigned int> northIndex(cell->x(),    cell->y() - 1);
    std::pair<unsigned int, unsigned int> southIndex(cell->x(),    cell->y() + 1);
    std::pair<unsigned int, unsigned int> eastIndex(cell->x() + 1, cell->y());
    std::pair<unsigned int, unsigned int> westIndex(cell->x() - 1, cell->y());

    Cell* northCell = get(northIndex);
    Cell* southCell = get(southIndex);
    Cell* eastCell = get(eastIndex);
    Cell* westCell = get(westIndex);

    if (northCell)
    {
        if (northCell->isAlive())
        {
            numAliveNeighbors++;
        }
        else if (northCell->isDead())
        {
            numDeadNeighbors++;
        }
    }

    if (southCell)
    {
        if (southCell->isAlive())
        {
            numAliveNeighbors++;
        }
        else if (southCell->isDead())
        {
            numDeadNeighbors++;
        }
    }
    if (eastCell)
    {
        if (eastCell->isAlive())
        {
            numAliveNeighbors++;
        }
        else if (eastCell->isDead())
        {
            numDeadNeighbors++;
        }
    }
    if (westCell)
    {
        if (westCell->isAlive())
        {
            numAliveNeighbors++;
        }
        else if (westCell->isDead())
        {
            numDeadNeighbors++;
        }
    }

    // Rule 1: Any live cell with fewer than two live neighbors dies, as from
    // under-population.
    if (numAliveNeighbors == 1)
    {
        cell->setDead();
    }
    // Rule 2: Any live cell with two or three live neighbors lives on 
    // to the next generation.
    else if ((numAliveNeighbors == 2) || numAliveNeighbors == 3)
    {
        cell->setAlive();
    }
    // Rule 3: Any live cell with more than three live neighbors dies,
    // as if by overcrowding.
    else if (numAliveNeighbors > 3)
    {
        cell->setDead();
    }
    // Rule 4: Any dead cell with exactly three live neighbors becomes alive,
    // as if by overcrowding.
    else if (numAliveNeighbors == 3)
    {
        cell->setAlive();
    }
    cell->update();
}

Cell* Cells::get(std::pair<unsigned int, unsigned int> index) const
{
    std::map<std::pair<unsigned int, unsigned int>, Cell*>::const_iterator it = 
        m_cells.find(index);
    if (it != m_cells.end())
    {
        Cell* cell = it->second;
        return cell;
    }
    return NULL;
}
