#include "card.h"
int counter = 0;
int colorcounter = 0;
Card::Card(){
  //constructor, inializing some values.
discountcolor = "null";
prestiege = "0";
white = "0";
red = "0";
pink = "0";
blue = "0";
green = "0";
type = "p";
}
void Card::setPrestige(){
  prestiege = "0";
}
void Card::setGemColor(){
  discountcolor = "null";
}
string Card::getType(){
  return type;
}
//Just returning a color given an index.
string Card::getPrice(int i){
  if(i == 0){
    return white;
    }
  if(i == 1){
    return red;
  }
  if(i == 2){
    return pink;
  }
  if(i == 3){
    return blue;
  }
  if(i == 4){
    return green;
  }else{
    return "";
  }
}
//straighforward data return.
string Card::getGemColor(){
  return discountcolor;
}
string Card :: getPrestiege(){
  return prestiege;
}
bool Card::ReadCard(stringstream *infile){
      string data_type;
      //We need the old position ocaasionally to go
      //back one in the data file for the boolean expression.
      //If we read in a t data type we have to tell the program to
      //stop and go to a new vector. We exit this function but still want
      //the type for later so we go back one with opos.
      streampos opos = (*infile).tellg();
      (*infile) >> data_type;

      if((!(*infile).eof()) && (data_type == "m")) {
        //Read in all the good data to the card.
        type = data_type;
         *infile >> prestiege;
         *infile >> discountcolor;
        *infile >> white >> red >> pink >> blue >> green;
        //ignore the last character we don't need.
         (*infile).ignore();
         //keep on reading into the vecotr if we have the same data type.
      return true;

  }else if((!(*infile).eof()) && (data_type == "t")) {
        if(counter == 0){
          (*infile).clear();
          (*infile).seekg(opos, ios::beg);
          counter++;
          return false;
        }
        type = data_type;
       (*infile) >> prestiege;
       (*infile) >> discountcolor;
       (*infile) >> white >> red >> pink >> blue >> green;
       (*infile).ignore();

    return true;

  }else if((!(*infile).eof()) && (data_type == "v")) {

        if(counter == 1){
          (*infile).clear();
          (*infile).seekg(opos, ios::beg);
          counter++;
          return false;
        }

        type = data_type;
       (*infile) >> prestiege;

       (*infile) >> discountcolor;
       (*infile) >> white >> red >> pink >> blue >> green;
       (*infile).ignore();

    return true;

  }else if((!(*infile).eof()) && (data_type == "n")){
        if(counter == 2){
          (*infile).clear();
          (*infile).seekg(opos, ios::beg);
          counter++;
          return false;
        }
        type = data_type;
       (*infile) >> prestiege;
       (*infile) >> discountcolor;
       (*infile) >> white >> red >> pink >> blue >> green;
       (*infile).ignore();

    return true;
  }else{
    return false;
  }


}
