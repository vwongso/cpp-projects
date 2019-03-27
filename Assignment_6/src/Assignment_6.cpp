#include <iostream>
#include <string>

using namespace std;

class TripleString
{
private:
   string string1;
   string string2;
   string string3;
   bool validString( string str );
public:
   TripleString();
   static int const MAX_LEN = 20;
   bool setString1(string string1);
   bool setString2(string string2);
   bool setString3(string string3);
   string getString1();
   string getString2();
   string getString3();
};

int getBet();
   TripleString thePull();
   void display(TripleString thePull, int winnings);
   string randString();
   int getPayMultiplier(TripleString thePull);

int main()
{
   while(true)
   {
      TripleString Pull = thePull();
      int winnings;
      double bet;
      bet = getBet();
      winnings = bet * getPayMultiplier (Pull);
      if ( bet == 0 )
      {
         cout << "Thank You. Have a nice day.";
         return 0;
      }
      display (Pull,winnings);
   }
}
int getBet()
{

   int bet;
   bool check;
   check = false;

   while ( check == false )
   {
      cout << "How much would you like to bet (1-100) or 0 to quit? ";
      cin >> bet;
      if ( bet < 0 || bet > 100 )
      {
         check = false;
      }
      else
         check = true;
   }
   return bet;
}

TripleString thePull()
{
   TripleString thePull;

   thePull.setString1(randString());
   thePull.setString2(randString());
   thePull.setString3(randString());

   return thePull;
}

string randString()
{
   string string;
   int hold;

   hold = 1 + rand() % 100;
   if ( hold <= 50 )
   {
      return "BAR";
   }
   else if ( hold <= 75 )
   {
      return "cherries";
   }
   else if ( hold <= 87.5 )
   {
      return "[space]";
   }
   else if ( hold <= 100 )
   {
      return "seven";
   }
   return string;

}

int getPayMultiplier (TripleString Pull)
{
   int prize;
   string cherries, BAR, space, seven;
   cherries = "cherries";
   BAR = "BAR";
   space = "[space]";
   seven = "7";


   if ( Pull.getString1() == cherries &&
         Pull.getString2() != cherries )
   {
      prize = 5;
   }
   else if ( Pull.getString1() == cherries &&
         Pull.getString2() == cherries && Pull.getString3() != cherries )
   {
      prize = 15;
   }
   else if ( Pull.getString1() == cherries && Pull.getString2()
         == cherries && Pull.getString3() == cherries )
   {
   prize = 30;
   }
   else if ( Pull.getString1() == BAR &&
         Pull.getString2() == BAR && Pull.getString3() == BAR )
   {
      prize = 50;
   }
   else if ( Pull.getString1() == seven &&
         Pull.getString2() == seven && Pull.getString3() == seven )
   {
      prize = 100;
   }
   else if ( Pull.getString1() == BAR && Pull.getString2() == BAR &&
         Pull.getString3() != BAR)
   {
      prize = 0;
   }
   else if ( Pull.getString1() == BAR && Pull.getString2() != BAR)
   {
      prize = 0;
   }
   else if ( Pull.getString1() == seven && Pull.getString2() == seven &&
         Pull.getString3() != seven)
   {
      prize = 0;
   }
   else if ( Pull.getString1() == seven && Pull.getString2() != seven)
   {
      prize = 0;
   }
   else if ( Pull.getString1() == space)
   {
      prize = 0;
   }
   else
      prize = 0;

   return prize;
}

TripleString::TripleString()
{
   string1 = "";
   string2 = "";
   string3 = "";
}

bool TripleString :: validString (string str)
{
   if(str.length() < MAX_LEN)
      return true;
   return false;
}

bool TripleString :: setString1(string string)
{
   if (validString (string))
   {
      string1 = string;
      return true;
   }
   else
      return false;
}
bool TripleString :: setString2(string string)
{
   if (validString (string))
   {
      string2 = string;
      return true;
   }
   else
      return false;
}
bool TripleString :: setString3(string string)
{
   if (validString (string))
   {
      string3 = string;
      return true;
   }
   else
      return false;
}

string TripleString :: getString1()
{
   return string1;
}

string TripleString :: getString2 ()
{
   return string2;
}

string TripleString :: getString3 ()
{
   return string3;
}

void display(TripleString Pull, int winnings)
{
   cout << "whirrrrrr .... and your pull is ... \n";
   cout << Pull.getString1() << " " << Pull.getString2() << " "
      << Pull.getString3() << endl;
   if ( winnings == 0 )
   {
      cout << "sorry, you lose.\n\n";
   }
   else
      cout << "congratulations, you win: " << winnings << endl << endl;
}

/*------------------------- paste of run --------------------------------
 *
How much would you like to bet (1-100) or 0 to quit? 999
How much would you like to bet (1-100) or 0 to quit? 12
whirrrrrr .... and your pull is ...
BAR BAR cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR cherries
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR [space] BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR seven
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR BAR
congratulations, you win: 250

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR BAR
congratulations, you win: 250

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR cherries
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR seven
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
[space] BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR BAR
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
[space] BAR [space]
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR cherries cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR [space]
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR seven
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven cherries BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR BAR
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries seven BAR
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR cherries BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
[space] BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR seven [space]
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR cherries BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR cherries BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR seven BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR cherries seven
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
[space] cherries cherries
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR BAR
congratulations, you win: 250

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR seven
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries BAR BAR
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
cherries [space] seven
congratulations, you win: 25

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
seven BAR BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR BAR [space]
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 5
whirrrrrr .... and your pull is ...
BAR seven BAR
sorry, you lose.

How much would you like to bet (1-100) or 0 to quit? 0
Thank You. Have a nice day.

--------------------------------------------------------------------*/

