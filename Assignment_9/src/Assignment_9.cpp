#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class PizzaOrder
{
public:
   PizzaOrder();
   PizzaOrder(int pizzaSize);
   static const string toppingsOffered[] ;
   static const double toppingsBaseCost= 3.00;
   static const double basePrice = 10.00;
   static int const LIMIT_CHOICE = 4;
   static int const MAX_TOPPINGS = 5;
   bool setSize(int size);
   bool addTopping(string topping);
   bool addTopping(int n);
   double getPrice();
   int getSize();
   string stringizeSize();
   string getToppings();
   void displayPizza();
   void resetTopping();
private:
   int size;
   int numToppings;
   string toppings[MAX_TOPPINGS];
};
   const string PizzaOrder::toppingsOffered[] =
   {"Onions", "Bell Peppers", "Olives", "Pepperoni"};
   static void displayMainMenu();
   static char getSizeFromUser();

int main()
{
   PizzaOrder pizza;
   string input;
   char initial;
   bool check = true;
   double price;
   int selection_choice;

   while ( true )
   {
      initial = getSizeFromUser();

      if ( initial == 'S' || initial == 's' )
      {
         pizza.setSize(0);
      }
      else if ( initial == 'M' || initial == 'm' )
      {
         pizza.setSize(1);
      }
      else if ( initial == 'L' || initial == 'l' )
      {
         pizza.setSize(2);
      }
      else if ( initial == 'Q' || initial == 'q')
      {
         cout << "Thank You for your visit.";
         return 0;
      }

      while ( true )
      {
         cout << "Current Pizza: ";
         pizza.displayPizza();
         displayMainMenu();
         cout << "Selection: ";
         getline(cin,input);
         istringstream(input) >> selection_choice;

         if ( selection_choice == 0)
         {
            check = true;
            cout << "Your Order: ";
            pizza.displayPizza();
            price = pizza.getPrice();
            cout << "Total Price: $"<< price << endl << endl;
            pizza.resetTopping();
            break;
         }

         pizza.addTopping(selection_choice);

      }
   }
}
PizzaOrder::PizzaOrder()
{
   size = 0.0;
   numToppings = 0;
}
PizzaOrder::PizzaOrder(int size)
{
   if ( size == 0 )
   {
      this->size = size;
   }
   else if ( size == 1 )
   {
      this->size = size;
   }
   else if ( size == 2 )
   {
      this->size = size;
   }
   numToppings = 0;
}
bool PizzaOrder::setSize(int size)
{
   if ( size < 0 || size > 2 )
   {
      return false;
   }
   else
      this->size = size;
   return true;
}
string PizzaOrder::getToppings()
{
   string addedtoppings;
   addedtoppings = "";
   for (int k = 0; k < numToppings; k++)
      addedtoppings = addedtoppings + " + " + toppings[k];
   return addedtoppings;

}
bool PizzaOrder::addTopping(string topping)
{
   if ( numToppings < MAX_TOPPINGS)
   {
      toppings[numToppings] = topping;
      numToppings++;
      return true;
   }
   else
      return false;
}
bool PizzaOrder::addTopping(int n)
{
   if (numToppings < MAX_TOPPINGS && n< LIMIT_CHOICE)
   {
      toppings[numToppings] = toppingsOffered[n-1];
      numToppings++;
      return true;
   }
   else
      return false;
}
string PizzaOrder::stringizeSize()
{
   string sizepizza;

   if ( size == 0 )
   {
      sizepizza = "Small";
   }
   else if ( size == 1 )
   {
      sizepizza = "Medium";
   }
   else
   {
      sizepizza = "Large";
   }

   return sizepizza;
}
double PizzaOrder::getPrice()
{
   double bill ;

   if (size == 0)
   {
      bill = basePrice + (numToppings*toppingsBaseCost);
   }
   if (size == 1)
   {
      bill = (basePrice + (numToppings*toppingsBaseCost)) * 1.15;
   }
   if (size == 2)
   {
      bill = (basePrice + (numToppings*toppingsBaseCost)) * 1.25;
   }

   return bill;
}
 static char getSizeFromUser()
{
   char input;
   string choice;
   bool check = true;

   while( check == true)
   {
      cout << "Size of pizza ('s', 'm', 'l') or 'q' to quit: ";
      getline(cin,choice);
      input = choice[0];
      if ( choice[0] == 'S' || choice[0] == 's' )
      {
         input = choice[0];
         check = false;
      }
      else if ( choice[0] == 'M' || choice[0] == 'm' )
      {
         input = choice[0];
         check = false;
      }
      else if ( choice[0] == 'L' || choice[0] == 'l' )
      {
         input = choice[0];
         check = false;
      }
      else if ( choice[0] == 'Q' || choice[0] == 'q' )
      {
         input = choice[0];
         check = false;
      }
      else
         check = true;
   }
    return input;
}
int PizzaOrder::getSize()
{
   return size;
}
static void displayMainMenu()
{
   cout << "Select an item by number (0 when done):\n";
   for (int k = 0;  k <PizzaOrder::LIMIT_CHOICE; k++)
         cout << "  " << k+1 << ". " << PizzaOrder::toppingsOffered[k] << endl;
}
void PizzaOrder::displayPizza()
{
   cout << stringizeSize() << getToppings() << endl;
}
void PizzaOrder::resetTopping()
{
   for(int k = 0; k < numToppings; k++)
      toppings[k] = "";

   numToppings = 0 ;
   size = 0;
}
/* ---------------------------- paste of run ------------------------------
 *
Size of pizza ('s', 'm', 'l') or 'q' to quit: e
Size of pizza ('s', 'm', 'l') or 'q' to quit: 9
Size of pizza ('s', 'm', 'l') or 'q' to quit: jump
Size of pizza ('s', 'm', 'l') or 'q' to quit: M
Current Pizza: Medium
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 1
Current Pizza: Medium + Onions
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 2
Current Pizza: Medium + Onions + Bell Peppers
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 3
Current Pizza: Medium + Onions + Bell Peppers + Olives
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 4
Current Pizza: Medium + Onions + Bell Peppers + Olives
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 0
Your Order: Medium + Onions + Bell Peppers + Olives
Total Price: $21.85

Size of pizza ('s', 'm', 'l') or 'q' to quit: l
Current Pizza: Large
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 1
Current Pizza: Large + Onions
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 3
Current Pizza: Large + Onions + Olives
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 2
Current Pizza: Large + Onions + Olives + Bell Peppers
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 2
Current Pizza: Large + Onions + Olives + Bell Peppers + Bell Peppers
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 0
Your Order: Large + Onions + Olives + Bell Peppers + Bell Peppers
Total Price: $27.5

Size of pizza ('s', 'm', 'l') or 'q' to quit: small
Current Pizza: Small
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 3
Current Pizza: Small + Olives
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 2
Current Pizza: Small + Olives + Bell Peppers
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 2
Current Pizza: Small + Olives + Bell Peppers + Bell Peppers
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 1
Current Pizza: Small + Olives + Bell Peppers + Bell Peppers + Onions
Select an item by number (0 when done):
  1. Onions
  2. Bell Peppers
  3. Olives
  4. Pepperoni
Selection: 0
Your Order: Small + Olives + Bell Peppers + Bell Peppers + Onions
Total Price: $22

Size of pizza ('s', 'm', 'l') or 'q' to quit: Q
Thank You for your visit.

----------------------------------------------------------------------- */
