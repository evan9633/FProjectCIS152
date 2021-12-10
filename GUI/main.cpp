#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <../Final_Project/fitapp.h>
fitApp initializeFitApp();
int main(int argc, char *argv[])
{
    /**
     * @brief GUI: Obviously tests with a GUI product are harder to do.
     *
     * Let me start off by saying this is currently compiled and running foremost on Windows 10, up-to-date system,
     * compiled using cmake in the QT IDE env.  It is compiled using the 'Release' option, and
     * for reasons unbeknownst to me, crashes when compiled using the 'Debug' version.
     *
     *TESTS:
     *Using the current settings, the inputted food items are sorted according to calorie count.
     *
     *Clicking on the zero-calorie button should output food: Noodles, and the relevent information.
     *
     *Clicking on the 250 calorie button should output food: apple and the relevent information.  It has been tested with both more and less items
     *successfully.
     *
     *Both options should be green in color, with the majority of the grid squares being gray.
     * @
     */
    QApplication a(argc, argv);
    MainWindow w;
    fitApp f;
    fitApp* f1;
    f.haveMeal("apple",100,1,2,3);
    f.haveMeal("noodles",200,0,0,0);
    f1 = &f;
    w.buildButtonGrid(f1);


   // qDebug() << QCoreApplication::arguments();
    w.show(); // crash handled if not building for release for some reason.
    //changing qt env to release and rebuilding solved and it runs perfectly again.
    return a.exec();
}

