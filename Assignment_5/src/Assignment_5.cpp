//============================================================================
// Name        : Assignment_5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
using namespace std;

char getKeyCharacter();
string getString();
string maskLetter(string phrase, char choice);
string removeCharacter(string phrase, char choice);
int countKey(string phrase, char choice);


int main()
{
   char choice = getKeyCharacter();
   string phrase = getString();
   cout << maskLetter(phrase,choice);
   cout << countKey(phrase,choice);
   cout << removeCharacter(phrase,choice);
}

char getKeyCharacter()
{
   string input;
   char choice;
   bool check;
   check = false;

   while (check == false)
   {
      cout << "Please enter a SINGLE character to act as a key: ";
      getline(cin,input);
      if ( input.length() > 1 || input.length() < 1 )
         check = false;
      else
      {
         choice = input[0];
         check = true;
      }
   }
   return choice;
}

string getString()
{
   string phrase;
   bool check;
   check = false;

   while (check == false)
   {
      cout << "Please enter a phrase or sentence >= 4 characters: \n";
      getline(cin,phrase);
      if ( phrase.length() >= 4 )
         check = true;
   }
   return phrase;
}

string maskLetter(string phrase, char choice)
{
   int integer;
   int number = phrase.length();

   cout << "String with key character, '" << choice << "' masked: \n";
   for ( integer = 0 ; integer < number ; integer++ )
   {
      if ( phrase[integer] == choice )
         phrase[integer] = '-';
   }
   return phrase;
}

int countKey(string phrase, char choice)
{
   string myStr;
   int integer;
   int number = phrase.length();
   int sum = 0;

   cout << "\n\n# of occurence, '" << choice << "' masked: ";
   for ( integer = 0 ; integer < number ; integer++ )
   {
      if ( phrase[integer] == choice)
         sum = sum + 1;
   }
   return sum;
}

string removeCharacter(string phrase, char choice)
{
   int integer;
   string myStr;
   int number = phrase.length();

   cout << "\n\nString with key character, '" << choice << "' removed: \n";
   for ( integer = 0 ; integer < number ; integer++ )
   {
      if ( phrase[integer] != choice)
         myStr = myStr + phrase[integer];
   }
   return myStr;
}

/*------------------------------ sample run ---------------------------------

Please enter a SINGLE character to act as a key: abc
Please enter a SINGLE character to act as a key:
Please enter a SINGLE character to act as a key: a
Please enter a phrase or sentence >= 4 characters:
cat
Please enter a phrase or sentence >= 4 characters:
He who laughs last, laughs fast, faster, FASTEST.
String with key character, 'a' masked:
He who l-ughs l-st, l-ughs f-st, f-ster, FASTEST.

# of occurence, 'a' masked: 5

String with key character, 'a' removed:
He who lughs lst, lughs fst, fster, FASTEST.

---------------------------------------------------------------------------*/

/*------------------------ sample run ( no error ) --------------------------

Please enter a SINGLE character to act as a key: e
Please enter a phrase or sentence >= 4 characters:
There are five trees and three flowers in the meadow of TEXAS.
String with key character, 'e' masked:
Th-r- ar- fiv- tr--s and thr-- flow-rs in th- m-adow of TEXAS.

# of occurence, 'e' masked: 11

String with key character, 'e' removed:
Thr ar fiv trs and thr flowrs in th madow of TEXAS.

---------------------------------------------------------------------------*/

/*------------------------------ sample run ---------------------------------

Please enter a SINGLE character to act as a key: efgh
Please enter a SINGLE character to act as a key:
Please enter a SINGLE character to act as a key: e
Please enter a phrase or sentence >= 4 characters:
There are five trees and three flowers in the meadow of TEXAS.
String with key character, 'e' masked:
Th-r- ar- fiv- tr--s and thr-- flow-rs in th- m-adow of TEXAS.

# of occurence, 'e' masked: 11

String with key character, 'e' removed:
Thr ar fiv trs and thr flowrs in th madow of TEXAS.

---------------------------------------------------------------------------*/

/*------------------------------ sample run ---------------------------------

Please enter a SINGLE character to act as a key: e
Please enter a phrase or sentence >= 4 characters:
red
Please enter a phrase or sentence >= 4 characters:
There are five trees and three flowers in the meadow of TEXAS.
String with key character, 'e' masked:
Th-r- ar- fiv- tr--s and thr-- flow-rs in th- m-adow of TEXAS.

# of occurence, 'e' masked: 11

String with key character, 'e' removed:
Thr ar fiv trs and thr flowrs in th madow of TEXAS.

---------------------------------------------------------------------------*/




