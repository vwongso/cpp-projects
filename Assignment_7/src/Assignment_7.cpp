#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class iTunes
{
private:
   string name;
   string artist;
   int bitrate;
   int totalTime;
public:
   iTunes();
   iTunes(string song_name, string artist_name,
         int song_bitrate, int song_totalTime);
   static int const MIN_BITRATE = 64;
   static int const MAX_BITRATE = 705;
   static int const MIN_STR_LENGTH = 1;
   static int const MAX_STR_LENGTH = 80;
   static int const MIN_PLAY_TIME = 1000;
   static int const MAX_PLAY_TIME = 1000*60*60;
   static int const DEFAULT_BITRATE = 64;
   static int const DEFAULT_PLAY_TIME = 1000;
   static const string DEFAULT_STRING;
   bool setName(string theName);
   bool setArtist(string artistName);
   bool setBitrate(int theBitrate);
   bool setTotalTime(int theTotalTime);
   string getName();
   string getArtist();
   int getBitrate();
   int getTotalTime();
   string toString();
   void display();
};
const string iTunes::DEFAULT_STRING = "(undefined)";
int main()
{
   iTunes song_1,song_2,song_3;
   iTunes song_4( "Fix You","Coldplay",256,295000);
   iTunes song_5( "The Call","Regina Spektor",153,188000 );
   iTunes song_6( "Somewhere Only We Know","Keane",192,239000 );

   cout << "Default Info: \n";
   song_1.display();
   song_2.display();
   song_3.display();

   cout << "Song Info: \n";
   song_1.setName("You Were Never Mine");
   song_1.setArtist("Janiva Magness");
   song_1.setBitrate(128);
   song_1.setTotalTime(276000);
   song_1.display();

   song_2.setName("Just the Girl");
   song_2.setArtist("The Click Five");
   song_2.setBitrate(128);
   song_2.setTotalTime(235000);
   song_2.display();

   song_3.setName("Saving My Face");
   song_3.setArtist("KT Tunstall");
   song_3.setBitrate(192);
   song_3.setTotalTime(216000);
   song_3.display();

   song_4.display();

   song_5.display();

   song_6.display();

   cout << "Modified Info of Second Song: \n";
   song_3.setTotalTime(999);
   song_3.display();

   cout << "Modified Info of Fourth Song: \n";
   song_4.setName("Test123");
   song_4.display();

   cout << "Artist's name is set to (""): ";
   if ( !song_1.setArtist(""))
   {
      cout << "Unknown Artist " << endl;
   }

   cout << "BitRate set to (23): ";
   if ( !song_6.setBitrate(23))
   {
      cout << "Bit Rate Error " << endl;
   }
   cout << "Title of first song: ";
   cout << song_1.getName() << endl;
   cout << "Artist name of second song: ";
   cout << song_2.getArtist();

}

string iTunes::toString()
{
   int bitRate,TotalTime;
   string bitRate_string, TotalTime_string;
   ostringstream cnvrt;

   bitRate = getBitrate();
   cnvrt << bitRate;
   bitRate_string = cnvrt.str();

   cnvrt.str("");
   cnvrt.clear();

   TotalTime = getTotalTime()/1000;
   cnvrt << TotalTime;
   TotalTime_string = cnvrt.str();

   string output_string;
   output_string = "Title: " + getName() + "\nArtist: " + getArtist() +
         "\nBit Rate: " + bitRate_string + "kbps" + "\nDuration: " +
         TotalTime_string + "s\n\n";
   return output_string;
}
void iTunes::display()
{
   cout << toString();
}


iTunes::iTunes()
{
   name = DEFAULT_STRING;
   artist = DEFAULT_STRING;
   bitrate = DEFAULT_BITRATE;
   totalTime = DEFAULT_PLAY_TIME;
}

iTunes::iTunes(string song_name, string artist_name,
      int song_bitrate, int song_totalTime)
{
   if ( song_name.length() > MIN_STR_LENGTH ||
         song_name.length() < MAX_STR_LENGTH )
   {
      name = song_name;
   }
   else
   {
      name = DEFAULT_STRING;
   }
   if ( artist_name.length() > MIN_STR_LENGTH ||
         artist_name.length() < MAX_STR_LENGTH )
   {
      artist = artist_name;
   }
   else
   {
      artist = DEFAULT_STRING;
   }
   if ( song_bitrate > MIN_BITRATE || song_bitrate < MAX_BITRATE )
   {
      bitrate = song_bitrate;
   }
   else
   {
      bitrate = DEFAULT_BITRATE;
   }
   if ( song_totalTime > MIN_PLAY_TIME || song_totalTime < MAX_PLAY_TIME )
   {
      totalTime = song_totalTime;
   }
   else
   {
      totalTime = DEFAULT_PLAY_TIME;
   }
}

bool iTunes::setName(string theName)
{
   if ( theName.length() < MIN_STR_LENGTH  ||
         theName.length() > MAX_STR_LENGTH )
   {
      return false;
   }
   else
   {
      name = theName;
      return true;
   }
}

bool iTunes::setArtist(string artistName)
{
   if ( artistName.length() < MIN_STR_LENGTH ||
         artistName.length() > MAX_STR_LENGTH )
   {
      return false;
   }
   else
   {
      artist = artistName;
      return true;
   }
}

bool iTunes::setBitrate(int theBitrate)
{
   if ( theBitrate < MIN_BITRATE || theBitrate > MAX_BITRATE )
   {
      return false;
   }
   else
   {
      bitrate = theBitrate;
      return true;
   }
}

bool iTunes::setTotalTime(int theTotalTime)
{
   if ( theTotalTime < MIN_PLAY_TIME && theTotalTime > MAX_PLAY_TIME )
   {
      return false;
   }
   else
   {
      totalTime = theTotalTime;
      return true;
   }
}

string iTunes::getName()
{
   return name;
}

string iTunes::getArtist()
{
   return artist;
}

int iTunes::getBitrate()
{
   return bitrate;
}

int iTunes::getTotalTime()
{
   return totalTime;
}

/*------------------------------ paste of run --------------------------------
 *
Default Info:
Title: (undefined)
Artist: (undefined)
Bit Rate: 64kbps
Duration: 1s

Title: (undefined)
Artist: (undefined)
Bit Rate: 64kbps
Duration: 1s

Title: (undefined)
Artist: (undefined)
Bit Rate: 64kbps
Duration: 1s

Song Info:
Title: You Were Never Mine
Artist: Janiva Magness
Bit Rate: 128kbps
Duration: 276s

Title: Just the Girl
Artist: The Click Five
Bit Rate: 128kbps
Duration: 235s

Title: Saving My Face
Artist: KT Tunstall
Bit Rate: 192kbps
Duration: 216s

Title: Fix You
Artist: Coldplay
Bit Rate: 256kbps
Duration: 295s

Title: The Call
Artist: Regina Spektor
Bit Rate: 153kbps
Duration: 188s

Title: Somewhere Only We Know
Artist: Keane
Bit Rate: 192kbps
Duration: 239s

Modified Info of Second Song:
Title: Saving My Face
Artist: KT Tunstall
Bit Rate: 192kbps
Duration: 0s

Modified Info of Fourth Song:
Title: Test123
Artist: Coldplay
Bit Rate: 256kbps
Duration: 295s

Artist's name is set to (): Unknown Artist
BitRate set to (23): Bit Rate Error
Title of first song: You Were Never Mine
Artist name of second song: The Click Five

--------------------------------------------------------------------------- */
