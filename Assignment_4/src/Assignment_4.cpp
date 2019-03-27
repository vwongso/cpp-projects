//============================================================================
// Name        : Assignment_4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main()
{
   double used_data,add_data,data,cost;
   string choice;
   bool validated;

   data = 2048;
   cost = 20;
   cout << "Initial Account Settings:" << endl;
   cout << "  Unused data: " << data << " MB" << endl;
   cout << "  Cost (so far) this month: $" << cost << endl;
   validated = false;
   while (!validated)
   {
      cout << "Menu:";
      cout << "\n   B (show Bill and starts new month)";
      cout << "\n   U (show Usage data for current month)";
      cout << "\n   D (consume Data now -- browse web, watch video, etc.)";
      cout << "\n   A (buy Additional gigabytes for current month)";
      cout << "\n   Q (show bill and Quit)";
      cout << "\n\n   Your Choice: ";
      cin >> choice;
         if ( choice[0] == 'a' || choice[0] == 'A' )
         {
            cout << "   Additional data to purchase in GB (1-5): ";
            cin >> add_data;
            if ( add_data >= 1 && add_data <= 5 )
            {
               data = (add_data * 1024) + data;
               cout << "   Available data: " << data << " MB" << endl;
               cost = cost + ( add_data * 10);
            }
            else
               cout << "   Error. Please enter a number between 1 and 5."
                  << endl;
         }
         else if ( choice[0] == 'd' || choice[0] == 'D' )
         {
            cout << "   Amount of data you are using now: ";
            cin >> used_data;
            if ( used_data >= 1 && used_data <= 1024)
            {
               data = data - used_data;
               cout << "   Available data: " << data << " MB" << endl;
               if ( data < 0 )
               {
                  cost = cost + 15;
                  data = data + 1000;
               }
            }
            else
               cout << "   Error. Please enter a number between 1 and 1024."
                  << endl;
         }

         else if ( choice[0] == 'u' || choice[0] == 'U' )
         {
            cout << "  Amount of unused data: " << data << " MB" << endl;
         }
         else if ( choice[0] == 'b' || choice[0] == 'B' )
         {
            cout << "   Closing bill for month:" << endl;
            cout << "   Unused data (lost): " << data << " MB" << endl;
            cout << "   Initial amount due immediately: $" << cost << endl;
            cost = 20;
            data = 2048;
            cout << "\n  Starting new month ...Available data: " << data
                  << " MB" << endl;
         }
         else if ( choice[0] == 'q' || choice[0] == 'Q' )
         {
            cout << "   Final monthly bill: $" << cost;
            validated = true;
         }
         else
            cout << "   Error. Invalid input." << endl;
   }
   return 0;
}

/*------------------------------ paste of run -------------------------------

Initial Account Settings:
  Unused data: 2048 MB
  Cost (so far) this month: $20
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: a
   Additional data to purchase in GB (1-5): 4
   Available data: 6144 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: bill
   Closing bill for month:
   Unused data (lost): 6144 MB
   Initial amount due immediately: $60

  Starting new month ...Available data: 2048 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: data
   Amount of data you are using now: 1000
   Available data: 1048 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: d
   Amount of data you are using now: 1000
   Available data: 48 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: D
   Amount of data you are using now: 1000
   Available data: -952 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: B
   Closing bill for month:
   Unused data (lost): 48 MB
   Initial amount due immediately: $35

  Starting new month ...Available data: 2048 M                B
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: Additional
   Additional data to purchase in GB (1-5): 3
   Available data: 5120 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: u
  Amount of unused data: 5120 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: a
   Additional data to purchase in GB (1-5): 7
   Error. Please enter a number between 1 and 5.
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: d
   Amount of data you are using now: 2000
   Error. Please enter a number between 1 and 1024.
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: b
   Closing bill for month:
   Unused data (lost): 5120 MB
   Initial amount due immediately: $50

  Starting new month ...Available data: 2048 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: violet
   Error. Invalid input.
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: a
   Additional data to purchase in GB (1-5): 2
   Available data: 4096 MB
Menu:
   B (show Bill and starts new month)
   U (show Usage data for current month)
   D (consume Data now -- browse web, watch video, etc.)
   A (buy Additional gigabytes for current month)
   Q (show bill and Quit)

   Your Choice: Quit
   Final monthly bill: $40

 --------------------------------------------------------------------------*/
