#include <fitapp.h>
int main(int argc, char *argv[])
{
    /**
     * TESTS
     * FitApp is created and 'fed' several meals.  The output should correspond with the listed values.
     *
     * These are run by switching the primary program to the 'Final_Project' folder and running the main.cpp file.
     */
    fitApp a;
    a.haveMeal("apple",1,1,2,3);
    /**
     * list is sorted after every pass of haveMeal, with respect to calories.
     * */
    cout << a.getCal()<<" Should be 1"<<endl;
    a.haveMeal("noodles",3,3,2,1);
    cout << a.getCal()<<" Should be 4"<<endl;
    a.haveMeal("banana",2,2,1,3);
    cout << a.getCal()<<" Should be 6"<<endl;

    fitApp* a1;
    a1 = &a;
    //a.workout("jog_1h");
    cout << "Outputted list should be: \n"
            "noodles\n"
            "noodles\n"
            "noodles\n"
            "banana\n"
            "banana\n"
            "apple"<<endl;

    for(int i=0;i<6;i++){
        cout << a1->getList(i).m.food<<endl;
    }
    a.haveMeal("twinkie",1000,5,4,3);
    a.workout("jog_1h");
    cout << a.getCal()<<" Should be 206"<<endl;
    return 1;
}
