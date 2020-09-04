#include "player.h"
#include <vector>
Player::Player(){
  prestiege = 0;

}
int carduse = 0;
//functions merely serve as an access to private
//data members.
void Player::setGemCount(int color, int i){
  gemcount[color] = gemcount[color] + i;
}

void Player::setDiscount(int color, int i){
  discount[color] = discount[color] + i;
}

int Player::getGemCount(int i){
  return gemcount[i];
}
void Player::setPrestige(Card c){
   prestiege = prestiege + stoi(c.getPrestiege());
}
int Player::totalPrestige(){
  return prestiege;
}

int Player::getDiscount(int i){
  return discount[i];
}

Card Player::getReserve(int i){
  return reserve[i];
}
void Player::ResetReserve(int i){
  reserve[i] = Card();
}

Card Player::setReserve(int i, vector<Card> cards, int carduse){
  if(reserve[0].getGemColor() == "null"){
  reserve[0] = cards[cards.size()-i];
  // cards.erase(cards.size()-4+i);
  // cards.erase(cards.size()-4-carduse);
  return cards[cards.size()-5-carduse];
}else if(reserve[1].getGemColor() == "null"){
reserve[1] = cards[cards.size()-i];
// cards.erase(cards.size()-4+i);
// cards.erase(cards.size()-4-carduse);
return cards[cards.size()-5-carduse];
}else if(reserve[2].getGemColor() == "null"){
reserve[2] = cards[cards.size()-i];
// cards.erase((cards.size()-4+i));

// cards.erase(cards.size()-4-carduse);
return cards[cards.size()-5-carduse];
}else{
  return Card();
}
// else{
//   return card();
// }
// else if(reserve[3]->getGemCount() == "null"){
// reserve[3] = cards[cards.size()-4+i];
// // cards.erase((cards.size()-4+i));
// cards[cards.size()-4+i] = cards[cards.size()-4-carduse];
// // cards.erase(cards.size()-4-carduse);
// return carduse++;
// }

}
