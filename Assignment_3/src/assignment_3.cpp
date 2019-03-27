//============================================================================
// Name        : assignment_3.cpp
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
   string airline,trip;
   double distance,cost,avg_cost,estimate,total_mileage;

   cout << "What airline are you analyzing? ";
   cin >> airline;

   cout << "\n-------------------- Trip 1 ---------------------\n";
   cout << "Description and flight number of any leg? ";
   getline(cin,trip);
   cout << "How many miles is the trip (round trip)? ";
   cin >> distance;
   cout << "Cost of round trip flight? ";
   cin >> cost;
   cout << airline << " flight: " << trip << endl;
   cout << "price: " << cost << " distance: " << distance
         << ".0 miles." << endl;

   avg_cost = cost;
   total_mileage = distance;

   if ( (airline.length() < 2) || (trip.length() < 4)
      || (distance < 20) || (cost < 1) )
   {
      cout << "\nError\n";
      return 0;
   }

   cout << "\n-------------------- Trip 2 ---------------------\n";
   cout << "Description and flight number of any leg? ";
   cin >> trip;
   cout << "How many miles is the trip (round trip)? ";
   cin >> distance;
   cout << "Cost of round trip flight? ";
   cin >> cost;
   cout << airline << " flight: " << trip << endl;
   cout << "price: " << cost << " distance: " << distance
         << ".0 miles." << endl;

   avg_cost = avg_cost + cost;
   total_mileage = total_mileage + distance;

   if ( (airline.length() < 2) || (trip.length() < 4)
      || (distance < 20) || (cost < 1) )
   {
      cout << "\nError\n";
      return 0;
   }

   cout << "\n-------------------- Trip 3 ---------------------\n";
   cout << "Description and flight number of any leg? ";
   cin >> trip;
   cout << "How many miles is the trip (round trip)? ";
   cin >> distance;
   cout << "Cost of round trip flight? ";
   cin >> cost;
   cout << airline << " flight; " << trip << endl;
   cout << "price: " << cost << " distance: " << distance << ".0 miles"
         << endl;

   avg_cost = avg_cost + cost;
   total_mileage = total_mileage + distance;
   avg_cost = avg_cost / total_mileage;

   if ( (airline.length() < 2) || (trip.length() < 4)
      || (distance < 20) || (cost < 1) )
   {
      cout << "\nError\n";
      return 0;
   }

   cout << "\n\n------------------- Result ----------------------\n";
   cout << "Average dollars per mile for " << airline << ": " << avg_cost
         << endl << endl;

   estimate = avg_cost * 2958;
   cout << "If a route between Monterey, CA and Monterrey, Mexico were added,"
         "\nthe estimated cost would be " << estimate << endl;

   return 0;
}

/*---------------------- paste of run (no error) ----------------------------

What airline are you analyzing? Delta

-------------------- Trip 1 ---------------------
Description and flight number of any leg? SFO/LAX-DL4600
How many miles is the trip (round trip)? 676
Cost of round trip flight? 224.80
Delta flight: SFO/LAX-DL4600
price: 224.8 distance: 676.0 miles.

-------------------- Trip 2 ---------------------
Description and flight number of any leg? PHL/MIA-DL161
How many miles is the trip (round trip)? 2026
Cost of round trip flight? 509.60
Delta flight: PHL/MIA-DL161
price: 509.6 distance: 2026.0 miles.

-------------------- Trip 3 ---------------------
Description and flight number of any leg? HOU/JFK-DL2334
How many miles is the trip (round trip)? 2856
Cost of round trip flight? 394.10
Delta flight; HOU/JFK-DL2334
price: 394.1 distance: 2856.0 miles


------------------- Result ----------------------
Average dollars per mile for Delta: 0.203041

If a route between Monterey, CA and Monterrey, Mexico were added,
the estimated cost would be 600.594

---------------------------------------------------------------------------*/

/*----------------------- paste of run (with error) -------------------------

What airline are you analyzing? D

-------------------- Trip 1 ---------------------
Description and flight number of any leg? SFO/LAX-DL4600
How many miles is the trip (round trip)? 676
Cost of round trip flight? 224.80
D flight: SFO/LAX-DL4600
price: 224.8 distance: 676.0 miles.

Error

---------------------------------------------------------------------------*/

/*----------------------- paste of run (with error) -------------------------

What airline are you analyzing? Delta

-------------------- Trip 1 ---------------------
Description and flight number of any leg? SFO/LAX-DL4600
How many miles is the trip (round trip)? 19
Cost of round trip flight? 224.80
Delta flight: SFO/LAX-DL4600
price: 224.8 distance: 19.0 miles.

Error

---------------------------------------------------------------------------*/



