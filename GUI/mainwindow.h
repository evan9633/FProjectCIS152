#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include "QLabel"
#include <QMessageBox>
#include <../Final_Project/fitapp.h>
#include <sstream>
/**
 * Max element constants -- can be updated from here.
 * */
#define MAXX 41
#define MAXY 51
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    fitApp* f;
    int index =0;
    /**
     * @brief buildButtonGrid Builds the grid of buttons used by the GUI.  Each button
     * corresponds to a calorie in an array of calories.  Each calorie contains a reference to the meal
     * that 'created' it.
     * @param fit pointer to the fitApp object created in fitapp_H.  Contains all relevent information.
     */
    void buildButtonGrid(fitApp* fit){
        QWidget *centralWidget = new QWidget;
            int count=1,i,j;
            f = fit;
            //QPushButton *button[10][10];
            QGridLayout *controlsLayout = new QGridLayout;
            QList<QPushButton*> buttons;
            QLabel *one=new QLabel;
            QLabel *two=new QLabel;

            one->setText("one");
            two->setText("two");
            /**
             *
             * Loop that creates a button array of a max size of 3000. Attemps to change button size aesthetics in the main widget but unsuccessfully.
             * */
            for(i=0;i<3000;++i){
                QPushButton* q = new QPushButton;
                buttons.append(q);
                buttons[i]->setMaximumSize(2,2);
                //buttons[i]->show(); do NOT use

            }
            /**
             *
             * Loop that links the buttons and uniquely indexes each one in order to correspond it with a calorie.
             * */
            for(i=0;i<MAXX;i++){
                for(j=0;j<MAXY;j++){
                    index = i*MAXY+j;
                    controlsLayout->addWidget(buttons[i*MAXY+j],j,i);
                    buttons[i*MAXY+j]->setMaximumSize(35,15);
                    QPalette pal = buttons[i*MAXY+j]->palette();
                    /**
                     * logic chain that colors the corresponding buttons.
                     * Buttons that contain no calorie are Grey
                     * BUttons that contain a calorie and reside under the 2k limit are green.
                     * Buttons that contain a calorie but fall over the 2k limit are red.
                     * */
                    if(fit->getList(i*MAXY+j).m.calories>=1){
                        pal.setColor(QPalette::Button, QColor(Qt::green));
                    }else{
                        pal.setColor(QPalette::Button, QColor(Qt::gray));

                    }
                    if(i*MAXY+j>1999&&fit->getList(index).m.food!="empty"){
                        pal.setColor(QPalette::Button, QColor(Qt::red));

                    }
                    buttons[i*MAXY+j]->setAutoFillBackground(true);

                    buttons[i*MAXY+j]->setPalette(pal);
                    //hack.  Labels each button with a unique integer associated with the calorie count.
                    string str = to_string(i*MAXY+j);

                    QString qstr = QString::fromStdString(str);

                    buttons[i*MAXY+j]->setText(qstr);
                    //linking function that associates a click function with each button.
                    QObject::connect(buttons[i*MAXY+j], SIGNAL(clicked()),this, SLOT(clickedSlot()));
                    buttons[i*MAXY+j]->update();

                }
            }



                   // buttons[i][j]->setMaximumSize(1,1);
                   // buttons[i][j]->show();
                   // controlsLayout->addWidget(buttons[i][j], i, j);

            controlsLayout->setSpacing(0);
            centralWidget->setLayout(controlsLayout);
            //controlsLayout->addWidget(centralWidget);
            setCentralWidget(centralWidget);
            //this->setWindowTitle("Caloric Layout");
            //centralWidget->show();
           // this->layout()->addWidget(centralWidget);




    }
    //To be determined
    void colorSlots(){

    }
public slots:
    //function activated when each button is clicked.
    void clickedSlot()
    {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Individual Caloric Detail");
      /**if(f->getList(index).m. == nullptr){
          msgBox.setText("Something has gone wrong. ");
          msgBox.exec();
          return;
      }**/

      /**
      * @brief hack elaboration:
      * needed to connect each button, and the way most resources said how to
      * was connecting the coordinates of the mouse cursor and interpreting from there.
      *
      * Luckily that takes too long and sucks to implement, so I created a numerical label which
      * can be accessed by the buttenSender pointer.  From there, I simply converted the QString to a Std::string
      * then to an integer which worked.
      */
     QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
     QString buttonText = buttonSender->text(); //This is a HACK
     string s = buttonText.toStdString();
     //cout << s;
     stringstream hack(s);
     int z =0;
     hack >> z;

      string str = "associated food: "+f->getList(z).m.food+
              "\n"+"calories : "+to_string(f->getList(z).m.calories)+
              "\n"+"carbs : "+to_string(f->getList(z).m.carbs)+
              "\n"+"fats : "+to_string(f->getList(z).m.fats)+
              "\n"+"protein : "+to_string(f->getList(z).m.protein);
      QString qstr = QString::fromStdString(str);
      msgBox.setText(qstr);
      //msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
      msgBox.exec();
    }

};

#endif // MAINWINDOW_H
