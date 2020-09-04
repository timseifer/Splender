
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
//This is our Card class that stores all necessary information for
//a card and all the getters and setters.
class Card{
  public:
  //constructor
  Card();
  //helper function.
  bool ReadCard(stringstream *infile);
  //getters and setters
  void setPrestige();
  string getPrice(int i);
  string getPrestiege();
  string getGemColor();
  void setGemColor();
  string getType();

private:
  //rupee const
string discountcolor;
  //prestiege points
string prestiege;
  //discount color
string white;

string red;

string pink;

string blue;

string green;
  //vendor, transport, or mine
string type;

};
