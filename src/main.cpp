


#include <QApplication>

#include "GameOfLifeWidget.h"



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    GameOfLifeWidget w;
    // The size of the widget is a functino of the grid size and the number of cells.
    w.resize(768, 576);

    w.setWindowTitle(QApplication::translate("Game of Life",
        "Game of Life"));
    w.show();

    return app.exec();
}

