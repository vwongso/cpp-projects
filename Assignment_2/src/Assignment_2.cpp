//============================================================================
// Name        : Assignment_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//============================================================================
// Name        : Assignment2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

int main()
{
   int n;
   int answer;

   cout << "n = 4," << endl;
   n = 4;
   answer = 4 + (n+1);
   cout << "4 + (" << n << "+1) = " << answer << endl;
   answer = ((n+1)*(n+2)/2)-5;
   cout << "((" << n << "+1)*(" << n << "+2))/2) - 5"
         << " = " << answer << endl;
   answer = 3 + 5 + (2*n-1);
   cout << "3 + 5 + " << "(2*" << n << "-1) = " << answer << endl;
   answer = n * n - 2;
   cout << n << "^2" << " - 2" << " = " << answer << endl << endl;

   cout << "n = 7," << endl;
   n = 7;
   answer = 4 + 5 + 6 + 7 + (n+1);
   cout << "4 + 5 + 6 + 7 + (" << n << "+1) = " << answer << endl;
   answer = ((n+1)*(n+2)/2)-5;
   cout << "((" << n << "+1)*(" << n << "+2))/2) - 5"
         << " = " << answer << endl;
   answer = 3 + 5 + 7 + 9 + 11 + (2*n-1);
   cout << "3 + 5 + 7 + 9 + 11 + " << "(2*" << n << "+1) = " << answer << endl;
   answer = n * n - 2;
   cout << n << "^2" << " - 2" << " = " << answer << endl << endl;

   cout << "n = 10," << endl;
   n = 10;
   answer = 4 + 5 + 6 + 7 + 8 + 9 + 10 + (n+1);
   cout << "4 + 5 + 6 + 7 + 8 + 9 + 10 + ("
         << n << "+1) = " << answer << endl;
   answer = ((n+1)*(n+2)/2)-5;
   cout << "((" << n << "+1)*(" << n << "+2))/2) - 5"
         << " = " << answer << endl;
   answer = 3 + 5 + 7 + 9 + 11 + 13 + 15 + 17 + (2*n-1);
   cout << "3 + 5 + 7 + 9 + 11 + 13 + 15 + 17 + " << "(2*"
         << n << "-1) = " << answer << endl;
   answer = n * n - 2;
   cout << n << "^2" << " - 2" << " = " << answer << endl;
   return 0;
}

/*--------------- paste of run -----------------

n = 4,
4 + (4+1) = 9
((4+1)*(4+2))/2) - 5 = 10
3 + 5 + (2*4-1) = 15
4^2 - 2 = 14

n = 7,
4 + 5 + 6 + 7 + (7+1) = 30
((7+1)*(7+2))/2) - 5 = 31
3 + 5 + 7 + 9 + 11 + (2*7+1) = 48
7^2 - 2 = 47

n = 10,
4 + 5 + 6 + 7 + 8 + 9 + 10 + (10+1) = 60
((10+1)*(10+2))/2) - 5 = 61
3 + 5 + 7 + 9 + 11 + 13 + 15 + 17 + (2*10-1) = 99
10^2 - 2 = 98

---------------------------------------------- */


