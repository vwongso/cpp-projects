//============================================================================
// Name        : Assignment_8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class DateProfile
{
private:
   char gender;
   char searchGender;
   int romance;
   int finance;
   string name;
   double determineGenderFit(DateProfile partner);
   double determineRomanceFit(DateProfile partner);
   double determineFinanceFit(DateProfile partner);
public:
   DateProfile();
   DateProfile(char gender, char searchGender,
         int romance, int finance, string name);
   static const char DEFAULT_GENDER = 'M';
   static const char DEFAULT_SEARCHGENDER = 'F';
   static int const DEFAULT_ROMANCE = 0.0;
   static int const DEFAULT_FINANCE = 0.0;
   static int const MIN_VALUE = 1;
   static int const MAX_VALUE = 10;
   static const string DEFAULT_NAME;
   bool setGender(char theGender);
   bool setSearchGender(char theSearchGender);
   bool setRomance(int theRomance);
   bool setFinance(int theFinance);
   bool setName(string theName);
   char getGender();
   char getSearchGender();
   int getRomance();
   int getFinance();
   string getName();
   double fitValue(DateProfile partner);
};
const string DateProfile::DEFAULT_NAME = "unknown";
int main()
{
   DateProfile applicant1 ('M','F',7,4,"Hugh Hefner");
   DateProfile applicant2 ('F','M',8,5,"Carmen Miranda");
   DateProfile applicant3 ('M','F',9,3,"Brad Pitt");
   DateProfile applicant4 ('F','M',6,9,"Mary Lynn Rajskub");

   cout << applicant1.getName() << endl;
   cout << "   " << applicant1.getName()
         << " fit " << applicant1.fitValue(applicant1) << endl;
   cout << "   " << applicant2.getName()
         << " fit " << applicant1.fitValue(applicant2) << endl;
   cout << "   " << applicant3.getName()
         << " fit " << applicant1.fitValue(applicant3) << endl;
   cout << "   " << applicant4.getName()
         << " fit " << applicant1.fitValue(applicant4) << endl;

   cout << applicant2.getName() << endl;
   cout << "   " << applicant1.getName()
         << " fit " << applicant2.fitValue(applicant1) << endl;
   cout << "   " << applicant2.getName()
         << " fit " << applicant2.fitValue(applicant2) << endl;
   cout << "   " << applicant3.getName()
         << " fit " << applicant2.fitValue(applicant3) << endl;
   cout << "   " << applicant4.getName()
         << " fit " << applicant2.fitValue(applicant4) << endl;

   cout << applicant3.getName() << endl;
   cout << "   " << applicant1.getName()
         << " fit " << applicant3.fitValue(applicant1) << endl;
   cout << "   " << applicant2.getName()
         << " fit " << applicant3.fitValue(applicant2) << endl;
   cout << "   " << applicant3.getName()
         << " fit " << applicant3.fitValue(applicant3) << endl;
   cout << "   " << applicant4.getName()
         << " fit " << applicant3.fitValue(applicant4) << endl;

   cout << applicant4.getName() << endl;
   cout << "   " << applicant1.getName()
         << " fit " << applicant4.fitValue(applicant1) << endl;
   cout << "   " << applicant2.getName()
         << " fit " << applicant4.fitValue(applicant2) << endl;
   cout << "   " << applicant3.getName()
         << " fit " << applicant4.fitValue(applicant3) << endl;
   cout << "   " << applicant4.getName()
         << " fit " << applicant4.fitValue(applicant4) << endl;
}
DateProfile::DateProfile()
{
   gender = DEFAULT_GENDER;
   searchGender = DEFAULT_SEARCHGENDER;
   romance = DEFAULT_ROMANCE;
   finance = DEFAULT_FINANCE;
   name = DEFAULT_NAME;
}
double DateProfile::determineGenderFit(DateProfile partner)
{
   if ( searchGender != partner.gender)
   {
      return 0;
   }
   else if ( partner.searchGender != gender)
   {
      return 0;
   }
   else
   {
   return 1;
   }
}
double DateProfile::determineRomanceFit(DateProfile partner)
{
   int myRomance,partnerRomance,difference;
   double romanceFit;

   myRomance = romance;
   partnerRomance = partner.romance;
   difference = abs(myRomance - partnerRomance);
   romanceFit = ((MAX_VALUE - 1) - (difference)) / ((double)(MAX_VALUE - 1));
   return romanceFit;
}
double DateProfile::determineFinanceFit(DateProfile partner)
{
   int myFinance,partnerFinance,difference;
   double financeFit;

   myFinance = finance;
   partnerFinance = partner.finance;
   difference = abs (myFinance - partnerFinance);
   financeFit = ((MAX_VALUE - 1) - (difference)) / ((double)(MAX_VALUE - 1));
   return financeFit;
}
double DateProfile::fitValue(DateProfile partner)
{
   return determineGenderFit(partner) * determineRomanceFit(partner) *
         determineFinanceFit(partner);
}
DateProfile::DateProfile(char gender, char searchGender,
      int romance, int finance, string name)
{
   if ( gender == 'M' || gender == 'F' )
   {
      this->gender = gender;
   }
   if ( searchGender == 'F' || searchGender == 'M')
   {
      this->searchGender = searchGender;
   }
   if ( romance > MIN_VALUE && romance < MAX_VALUE )
   {
      this->romance = romance;
   }
   if ( finance > MIN_VALUE && finance < MAX_VALUE )
   {
      this->finance = finance;
   }
      this->name = name;
}
bool DateProfile::setGender(char theGender)
{
   if ( theGender != 'M' && theGender != 'F' )
   {
      return false;
   }
   else
   {
      gender = theGender;
      return true;
   }
}
bool DateProfile::setSearchGender(char theSearchGender)
{
   if ( theSearchGender != 'F' && theSearchGender != 'M' )
   {
      return false;
   }
   else
   {
      searchGender = theSearchGender;
      return true;
   }
}
bool DateProfile::setRomance(int theRomance)
{
   if ( theRomance < MIN_VALUE || theRomance > MAX_VALUE )
   {
      return false;
   }
   else
   {
      romance = theRomance;
      return true;
   }
}
bool DateProfile::setFinance(int theFinance)
{
   if ( theFinance < MIN_VALUE || theFinance > MAX_VALUE )
   {
      return false;
   }
   else
   {
      finance = theFinance;
      return true;
   }
}
bool DateProfile::setName(string theName)
{
      name = theName;
      return true;
}
char DateProfile::getGender()
{
   return gender;
}
char DateProfile::getSearchGender()
{
   return searchGender;
}
int DateProfile::getRomance()
{
   return romance;
}
int DateProfile::getFinance()
{
   return finance;
}
string DateProfile::getName()
{
   return name;
}

/*------------------------------ paste of run ---------------------------------
 *
Hugh Hefner
   Hugh Hefner fit 0
   Carmen Miranda fit 0.790123
   Brad Pitt fit 0
   Mary Lynn Rajskub fit 0.395062
Carmen Miranda
   Hugh Hefner fit 0.790123
   Carmen Miranda fit 0
   Brad Pitt fit 0.691358
   Mary Lynn Rajskub fit 0
Brad Pitt
   Hugh Hefner fit 0
   Carmen Miranda fit 0.691358
   Brad Pitt fit 0
   Mary Lynn Rajskub fit 0.222222
Mary Lynn Rajskub
   Hugh Hefner fit 0.395062
   Carmen Miranda fit 0
   Brad Pitt fit 0.222222
   Mary Lynn Rajskub fit 0

-----------------------------------------------------------------------------*/
