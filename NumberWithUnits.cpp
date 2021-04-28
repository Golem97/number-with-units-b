#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

namespace ariel{
    
    //Stock the available unity and their conversions
    static map<string, map<string, double>> map_unity;


    //================
    /* CONSTRUCTORS */
    //================

    NumberWithUnits::NumberWithUnits(double number, const string &unity){
        
        //Check unity is available 
        if (map_unity.count(unity) == 0) {
            throw invalid_argument("There's no unity called " + unity + " !");
        }

        //Initialize units
        this->number = number;
        this->unity = unity;
    }


    //===========
    /* METHODS */
    //===========
    void convert_map(const string &u1, const string &u2){

        //Pass all over  the map
        for (const auto &key1 : map_unity[u1]){
            for (const auto &key2 : map_unity[u2]) {

                //Use the ratio of the unit to change 
                double ratio = map_unity[key1.first][u1] * map_unity[u1][u2] * map_unity[u2][key2.first];
                map_unity[key1.first][key2.first] = ratio;
                map_unity[key2.first][key1.first] = 1 / ratio;
            }
        }
    }

   int compar(const NumberWithUnits &n1, double n2) {
        double delta = n1.number - n2;
        int ans = 0;
        
        //If the difference is negativ i use abs from <math>
        if (!(abs(delta) < EPSILON)) {
            if (delta > EPSILON) {
                ans = 1;
            }
            else{
            ans = -1;
            }
        }
        return ans;
    }

    void NumberWithUnits::read_units(ifstream &units_file){
        
        double n1 = 0;
        double n2 = 0;
        
        string u1;
        string u2;

        string equal;  

        while (units_file >> n1 >> u1 >> equal >> n2 >> u2) {

            //Insert new units to units list :
            map_unity[u1][u2] = n2;
            map_unity[u1][u1] = 1;
            map_unity[u2][u1] = 1 / n2;
            map_unity[u2][u2] = 1;

            //Now we will merge the conversion lists between both units.
            convert_map(u1, u2);
        }
    }

    double unity_convert(const string &frome, const string &to, const double &n){
        //If no conversion ratio found between the units
        if (map_unity.at(frome).count(to) == 0)
        {
            throw invalid_argument("Cannot do convertion of units - [" + frome + "] to unit : [" + to + "]");
        }

        return n * map_unity[frome][to];
    }

     //======================
     /* OPERATORS OVERLOAD */
     //======================

    //(+)
    NumberWithUnits NumberWithUnits::operator+() const{
        return NumberWithUnits{this->number, this->unity};
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &n2) const{
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        return NumberWithUnits(this->number + conv_num, this->unity);
    }
    
     //(-)
    NumberWithUnits NumberWithUnits::operator-() const{
        return NumberWithUnits(-this->number, this->unity);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n2) const{
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        return NumberWithUnits(this->number - conv_num, this->unity);
    }
    
    //(*)
    //double * NumberWithUnits
    NumberWithUnits operator*(const double &numDouble, const NumberWithUnits &num){
        return NumberWithUnits{num.number * numDouble, num.unity};
    }
    // NumberWithUnits * double
    NumberWithUnits NumberWithUnits::operator*(const double &n2) const{
        return NumberWithUnits{this->number * n2, this->unity};
    }

    //(+=)  
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n2){
        //Convert the number to match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        this->number += conv_num;

        //return n1 after the modification
        return *this;
    }
    //(-=)
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n2){
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        this->number -= conv_num;
        return *this;
    }


    //=========================
    /* OPERATORS COMPARAISON */
    //=========================

    //(<)
    bool NumberWithUnits::operator<(const NumberWithUnits &n2) const{
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is  negatif/postif
        return compar(*this, conv_num) < 0;
    }
    //(<=)
    bool NumberWithUnits::operator<=(const NumberWithUnits &n2) const{
         //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is  negatif/postif
        return compar(*this, conv_num) <= 0;
    }
    //(>)
    bool NumberWithUnits::operator>(const NumberWithUnits &n2) const{
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is  negatif/postif
        return compar(*this, conv_num) > 0;
    }
    //(>=)
    bool NumberWithUnits::operator>=(const NumberWithUnits &n2) const {
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is  negatif/postif
        return compar(*this, conv_num) >= 0;
    }
    //(==)
    bool NumberWithUnits::operator==(const NumberWithUnits &n2) const{
        //Covert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is equal
        return compar(*this, conv_num) == 0;
    }
    //(!=)
    bool NumberWithUnits::operator!=(const NumberWithUnits &n2) const{
        //Convert the number to the match unity
        double conv_num = unity_convert(n2.unity, this->unity, n2.number);
        //Use compar to check if the difference is  negatif/postif
        return compar(*this, conv_num) != 0;
    }

    //===========================
    /* OPERATORS INCREMENTATION*/
    //===========================

    //(++)
    NumberWithUnits &NumberWithUnits::operator++(){
        //Incerement only the number of the object (Number With Unit)
        this->number++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) {
        //Increment the number part as a copy 
        NumberWithUnits ci = *this;
        this->number++;
        return ci;
    }

     //(--)
    NumberWithUnits &NumberWithUnits::operator--(){
        //Decrement number part of the object(NumberWithUnits)
        this->number--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        //Decrement the number part as copy
        NumberWithUnits t = *this;
        this->number--;
        return t;
    }

   
    //==========================
    /* INPUT & OUTPUT OVERLOAD*/
    //==========================

    //(<<)
    ostream &operator<<(ostream &out, const NumberWithUnits &num){
        return out << num.number << "[" << num.unity << "]";
    }

    //(>>)
    istream &operator>>(istream &in, NumberWithUnits &num){
       
        double number = 0;
        string unity;

        //Recieve number and unity
        in >> number >> unity;

        //Enter the unit don't stop add char "]" 
        //If unity part of the entry is not empty
        while (unity.at(unity.length() - 1) != ']' && !unity.empty()){
            
            string u;
            //reciev the char of the unity 
            in >> u;
            //Add all chars of unity add the "]"
            unity += u;
        }

       //Removing "[]"
        unity.erase(remove(unity.begin(), unity.end(), '['), unity.end());
        unity.erase(remove(unity.begin(), unity.end(), ']'), unity.end());

        //Check if unity is available
        if (map_unity.count(unity) == 0) {
            throw invalid_argument("Unit " + unity + " not available ");
        }

        //Enter the number
        num.unity = unity;
        num.number = number;
        return in;
    }
}
