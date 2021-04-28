/*
===============================================================
>Submission 3.1 CPP_CS_Ariel University 2021 Year_2 Semester_2 
>Author <Nathanael Benichou>
>number-with-units-b
================================================================
*/
#include <string>
#include <map>
using namespace std;

namespace ariel{

const double EPSILON = 0.001;
    
    class NumberWithUnits{

    string unity;
    double number;

    public:

		//===========
    	/* METHODS */
    	//===========

        NumberWithUnits(double, const string&);
        static void read_units(ifstream&);
        friend int compar(const NumberWithUnits&, double);

        //======================
    	/* OPERATORS OVERLOAD */
    	//======================


       //(+)
        NumberWithUnits operator+() const;
        NumberWithUnits operator+(const NumberWithUnits&) const; 
        //(-)
        NumberWithUnits operator-() const; 
        NumberWithUnits operator-(const NumberWithUnits&) const; 
        //(*)
        friend NumberWithUnits operator*(const double&, const NumberWithUnits&);
        NumberWithUnits operator*(const double&) const;
        //(+=)
        NumberWithUnits &operator+=(const NumberWithUnits&); 
        //(-=)
        NumberWithUnits &operator-=(const NumberWithUnits&); 

        //========================
    	/* OPERATORS COMPARAISON */
    	//=========================

        //(<)
        bool operator<(const NumberWithUnits&) const;
        //(<=)
        bool operator<=(const NumberWithUnits&) const;
        //(>)
        bool operator>(const NumberWithUnits&) const;
        //(>=)
        bool operator>=(const NumberWithUnits&) const;
        //(==)
        bool operator==(const NumberWithUnits&) const;
        //(!=)
        bool operator!=(const NumberWithUnits&) const;
        
        //===========================
    	/* OPERATORS INCREMENTATION*/
    	//===========================
        //(++)
        NumberWithUnits &operator++();
        NumberWithUnits operator++(int); 
        //(--)
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int); 

        //==========================
    	/* INPUT & OUTPUT OVERLOAD*/
    	//==========================
        //(<<)
        friend ostream &operator<<(ostream&, const NumberWithUnits&);
        //(>>)
        friend istream &operator>>(istream&, NumberWithUnits&);
    };
}