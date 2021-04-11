# PyDracula - Modern GUI using Qt5 instead of PySide6 / PyQt6

## This is a C++ port of Wanderson's PyDracula - Modern GUI PySide6 / PyQt6

It is a direct port. The following has been changed to make it work in C++
 - Using Python, it is possible to simple assign a virtual function to a function, e.g. `mouseMoveEvent` of a GUI element can be assigned to any function. In C++, I have installed an eventFilter instead on the GUI class.
 - Using Python, it is possible to inherit a class and a parent can simply address these functions. To keep the same design, I have introduced static classes for e.g. UIFunctions, where an additional pointer argument is added.

## Running
> git clone git@github.com:JensMunkHansen/Modern_GUI_PyDracula_CPP.git
> cd Modern_GUI_PyDracula_CPP
> mkdir build
> cd build
> cmake .. -DQT_DIR="[location of Qt]/lib/cmake/Qt5"
> make -j4