



#include "Cell.h"
#include "Cells.h"
#include "GameOfLifeWidget.h"

#include "gtest/gtest.h"



class CellsWrapper : public Cells
{
public:
    // Allow public access to protected function.
    using Cells::updateCell;
};


class GameofLifeTestFixture : public testing::Test
{

public:

    void SetUp() override
    {
        
    }
    void TearDown() override
    {
    }

    CellsWrapper m_cells;
};



TEST_F(GameofLifeTestFixture, CellLifecycle)
{
    Cell* c = new Cell(1, 2);
    // std::clog << *c << std::endl;

    // Test that the cell defaults to NONE.
    EXPECT_TRUE(c->isNone());

    c->setAlive();
    EXPECT_TRUE(c->isAlive());

    c->setDead();
    EXPECT_TRUE(c->isDead());

    EXPECT_EQ(c->x(), 1U);
    EXPECT_EQ(c->y(), 2U);

    std::pair<unsigned int, unsigned int> idx = c->index();
    EXPECT_EQ(idx.first, 1U);
    EXPECT_EQ(idx.second, 2U);
}

TEST_F(GameofLifeTestFixture, Cells)
{
    Cell* c00 = new Cell(0, 0);
    c00->setAlive();

    Cell* c10 = new Cell(1, 0);
    c10->setDead();

    m_cells.add(c00);
    m_cells.add(c10);
    
    c00 = m_cells.get(std::pair<unsigned int, unsigned int>(0, 0));
    EXPECT_TRUE(c00->isAlive());
    EXPECT_EQ(c00->x(), 0);
    EXPECT_EQ(c00->y(), 0);

    c10 = m_cells.get(std::pair<unsigned int, unsigned int>(1, 0));
    EXPECT_TRUE(c10->isDead());
    EXPECT_EQ(c10->x(), 1);
    EXPECT_EQ(c10->y(), 0);
}


// Rule 1: Any live cell with fewer than two live neighbors dies, as from
// under-population.
TEST_F(GameofLifeTestFixture, RuleOne)
{
    // Create a cell (center) with two live neighbors, update, and check
    // that it died.

    // -------------
    // | L | X | D |
    // -------------

    Cell* c1 = new Cell(0, 0);
    c1->setAlive();
    Cell* c2 = new Cell(1, 0);
    c2->setAlive();
    Cell* c3 = new Cell(2, 0);
    c3->setDead();


    m_cells.add(c1);
    m_cells.add(c2);
    m_cells.add(c3);

    m_cells.updateCell(c2);

    EXPECT_TRUE(c2->isDead());
}

// Rule 2: Any live cell with two or three live neighbors lives on to the next
// generation.
TEST_F(GameofLifeTestFixture, RuleTwo)
{
    // _____________
    // |   | L |   |
    // -------------
    // | L | X | L |
    // -------------
    // |   |   |   |
    // -------------

    Cell* c1 = new Cell(0, 0);
    Cell* c2 = new Cell(1, 0);
    c2->setAlive();
    Cell* c3 = new Cell(2, 0);

    Cell* c4 = new Cell(0, 1);
    c4->setAlive();
    Cell* c5 = new Cell(1, 1);
    c5->setDead();
    Cell* c6 = new Cell(2, 1);
    c6->setAlive();

    Cell* c7 = new Cell(0, 2);
    Cell* c8 = new Cell(1, 2);
    Cell* c9 = new Cell(2, 2);

    m_cells.add(c1);
    m_cells.add(c2);
    m_cells.add(c3);

    m_cells.add(c4);
    m_cells.add(c5);
    m_cells.add(c6);

    m_cells.add(c7);
    m_cells.add(c8);
    m_cells.add(c9);

    m_cells.updateCell(c5);
    
    EXPECT_TRUE(c5->isAlive());
}

// Rule 3: Any live cell with more than three live enighbors dies, as if by
// overcrowding
TEST_F(GameofLifeTestFixture, RuleThree)
{
    // _____________
    // |   | L |   |
    // -------------
    // | L | X | L |
    // -------------
    // |   | L |   |
    // -------------

    Cell* c1 = new Cell(0, 0);
    Cell* c2 = new Cell(1, 0);
    c2->setAlive();
    Cell* c3 = new Cell(2, 0);

    Cell* c4 = new Cell(0, 1);
    c4->setAlive();
    Cell* c5 = new Cell(1, 1);
    c5->setAlive();
    Cell* c6 = new Cell(2, 1);
    c6->setAlive();

    Cell* c7 = new Cell(0, 2);
    Cell* c8 = new Cell(1, 2);
    c8->setAlive();
    Cell* c9 = new Cell(2, 2);

    m_cells.add(c1);
    m_cells.add(c2);
    m_cells.add(c3);

    m_cells.add(c4);
    m_cells.add(c5);
    m_cells.add(c6);

    m_cells.add(c7);
    m_cells.add(c8);
    m_cells.add(c9);

    m_cells.updateCell(c5);
    
    EXPECT_TRUE(c5->isDead());
}

// Rule 4: Any dead cell with exactly three live neighbors becomes a live cell,
// as if by overcrowding.
TEST_F(GameofLifeTestFixture, RuleFour)
{
    // _____________
    // |   | L |   |
    // -------------
    // | L | X | L |
    // -------------
    // |   | D |   |
    // -------------

    Cell* c1 = new Cell(0, 0);
    Cell* c2 = new Cell(1, 0);
    c2->setAlive();
    Cell* c3 = new Cell(2, 0);

    Cell* c4 = new Cell(0, 1);
    c4->setAlive();
    Cell* c5 = new Cell(1, 1);
    c5->setDead();
    Cell* c6 = new Cell(2, 1);
    c6->setAlive();

    Cell* c7 = new Cell(0, 2);
    Cell* c8 = new Cell(1, 2);
    c8->setDead();
    Cell* c9 = new Cell(2, 2);

    m_cells.add(c1);
    m_cells.add(c2);
    m_cells.add(c3);

    m_cells.add(c4);
    m_cells.add(c5);
    m_cells.add(c6);

    m_cells.add(c7);
    m_cells.add(c8);
    m_cells.add(c9);

    m_cells.updateCell(c5);
    
    EXPECT_TRUE(c5->isAlive());
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}