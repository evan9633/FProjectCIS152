#ifndef FITAPP_H
#define FITAPP_H
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * @brief The meal struct organizes nutritional information and contains
 * the string that records what the inputted food is.
 */
struct meal{
    string food;
     int calories;
     int carbs;
     int protein;
     int fats;
};
/**
 * @brief The calorie contains a reference to the meal that created the calorie that is represented by this struct.
 * also used to represent the daily meal by the GUI-half of the program.
 */
struct calorie{
    struct meal m = {"empty",0,0,0,0};
};


//tried to use enum here but it didn't fall through and a map is (apparently) simpler when handling user input.
class fitApp
{
public:
    vector<meal> v;
    int calories=0;
    /**
     * @brief fitApp constructor -- used to be used to default the array but just there for organizational sake.
     */
    fitApp(){
       /** for(int i=0;i<51*41;i++){
            struct calorie c;
            c.m.food="empty";
            cList[i] = c;
        }**/
    };
    ~fitApp(){

    };
    /**
     * @brief haveMeal workhorse of the backend.  Inputs a meal, and organizes the data accordingly into calories.
     * @param meal struct containing nutritional value
     * @param cal calorie count, not calorie pointer.
     * @param carbs
     * @param fats
     * @param protein
     */
    void haveMeal(string meal, int cal, int carbs, int fats, int protein){
        if(cal <=0||carbs<0||fats<0||protein<0){
            //throw "Nothing you eat is free!  Negative Calories only come through exercise.";exit(-1);
        }
        struct meal me;
        me.food = meal;
        me.calories = cal;
        me.carbs = carbs;
        me.fats = fats;
        me.protein = protein;
        daily.push(me);
        v.push_back(me);

       // struct meal* ptr;
        //ptr = &daily.top();

        for(int i=calories;i<calories+cal;i++){
            struct calorie ca;
            struct meal mea;
            mea.calories=cal;
            mea.carbs = carbs;
            mea.fats = fats;
            mea.protein=protein;
            mea.food=meal;
            ca.m=mea;
            cList[i] = ca;
        }
        calories+=cal;
        calorieSort(cList,0,calories); // sorted by calories by default.  Tests are run with this as the option.
        //IMPORTANT: To change which macro it is sorted by, simply comment out calorieSort and replace the function
        //Call with the corresponding method.
        //proteinSort(cList,0,calories);
        //carbSort(cList,0,calories);
        //fatSort(cList,0,calories);


    }
    /**
     * @brief workout nominally a function for removing calories.  Somewhat deprecated as the direction
     * of the project shifted.
     * @param s string corresponding to an exercise.  Pre-made.
     */
    void workout(string s){
        map<int,string> m = getMap();
        map<int,string>::iterator it;// This is kind of a hack, but accessing map objects is a little more complex
        //than I had intended.

         // if scaled would simply search for corresponding map strings.  AS it is this is minimalistic for functionality.
           if(s=="jog_1h"){//laid out for accessing an itemized list of food sorted by name.  Simplified for functionality and (temporary) simplicity.
                calories-=800;
           }else if(s=="jog_30m"){
               calories-=300;
           }else if(s=="jjacks"){
               calories-=80;
           }else if(s=="weighttrain"){
               calories-=150;
           }else{
               //throw "incorrect exercise inputted.  Recheck guidelines and try again."; exit(-1);
           }

    };
    /**
     * @brief calorieSort
     * @param list, list of calorie objects to be sorted from largest to smallest.
     * @param st start point, should always be the index 0 -- i.e the start of the array.
     * @param en end point, should be the highest calorie inputted; the last referenced calorie in the array.
     */
    void calorieSort(calorie list[], int st, int en){
        if (st >= en) {
                return;
            }
        int pivot = SortC(list, st, en);
        calorieSort(list, st, pivot - 1);
        calorieSort(list, pivot + 1, en);

    }
    void fatSort(calorie list[], int st, int en){
        if (st >= en) {
                return;
            }
        int pivot = SortF(list, st, en);
        fatSort(list, st, pivot - 1);
        fatSort(list, pivot + 1, en);

    }
    void carbSort(calorie list[], int st, int en){
        if (st >= en) {
                return;
            }
        int pivot = SortCa(list, st, en);
        carbSort(list, st, pivot - 1);
        carbSort(list, pivot + 1, en);

    }
    void proteinSort(calorie list[], int st, int en){
        if (st >= en) {
                return;
            }
        int pivot = SortP(list, st, en);
        proteinSort(list, st, pivot - 1);
        proteinSort(list, pivot + 1, en);

    }
    /**

      Partitioning function acting via the quick-sort algorithm.
      Sorts a list of calorie objects ( containing a reference to the originating meal)
      from greatest to smallest.
**/
    int SortC(calorie list[], int st, int en){
        int piv = list[en].m.calories;
        int pIndex = st;
        for (int i = st; i < en; i++)
        {
            if (list[i].m.calories >= piv)
            {
                swap(list[i], list[pIndex]);
                pIndex++;
            }
        }
        swap (list[pIndex], list[en]);
        return pIndex;
    }
    int SortCa(calorie list[], int st, int en){
        int piv = list[en].m.carbs;
        int pIndex = st;
        for (int i = st; i < en; i++)
        {
            if (list[i].m.carbs >= piv)
            {
                swap(list[i], list[pIndex]);
                pIndex++;
            }
        }
        swap (list[pIndex], list[en]);
        return pIndex;
    }
    int SortF(calorie list[], int st, int en){
        int piv = list[en].m.fats;
        int pIndex = st;
        for (int i = st; i < en; i++)
        {
            if (list[i].m.fats >= piv)
            {
                swap(list[i], list[pIndex]);
                pIndex++;
            }
        }
        swap (list[pIndex], list[en]);
        return pIndex;
    }
    int SortP(calorie list[], int st, int en){
        int piv = list[en].m.protein;
        int pIndex = st;
        for (int i = st; i < en; i++)
        {
            if (list[i].m.protein >= piv)
            {
                swap(list[i], list[pIndex]);
                pIndex++;
            }
        }
        swap (list[pIndex], list[en]);
        return pIndex;
    }
    /**
     * @brief getMap
     * @return returns selected exercise -- semi-defunct legacy code
     * from an earlier phase of this project.
     */
    map<int,string> getMap(){
        return exercise;
    }
    /**
     * @brief getCal
     * @return returns calorie count as know by the fitApp.
     */
    int getCal(){
        return calories;
    }
    /**
     * @brief getList
     * @param i
     * @return returns the indexed calorie at the specificed position, i.
     */
    calorie getList(int i){
        calorie tmp;
        tmp = cList[i];
        return tmp;
    }
    /**
     * @brief addFood: basic user-inputted food option.  Due to QT, does not work without preparation.
     */
    void addFood(){
        cout << "Enter a food item: "<<endl;
        string s;
        cin >> s;
        cout << "Enter the calories in said item: "<<endl;
        int cal=0;
        cin >> cal;
        int carbs, fats, protein;
        cout << "Enter the carbs, fats, and Protein in that order: "<<endl;
        cin >> carbs;
        cin >> fats;
        cin >> protein;
        haveMeal(s,cal,carbs,fats,protein); // ensure this is using the terminal, which is specified through your env.  cin does not work when
        //run through the IDE.
    }


private:
    stack<meal> daily;
    map<int,string> exercise{{800,"jog_1h"}
                             ,{300, "jog_30m"}
                             ,{80, "jjacks"}
                             ,{150, "weighttrain"}};
    calorie cList[3500];

};

#endif // FITAPP_H
