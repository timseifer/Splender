#include <string>
#include "termfuncs.h"
#include "card.h"
#include <vector>

using namespace std;
//Class player that includes all necessary getters and setters as
//well as the data.
class Player{
  public:
    Player();
    //getters and setters
    void setGemCount(int color, int i);
    int getGemCount(int i);
    void setDiscount(int color, int i);
    int getDiscount(int i);
    void setPrestige(Card c);
    int totalPrestige();
    void ResetReserve(int i);
    Card getReserve(int i);
    Card setReserve(int i, vector<Card> cards, int carduse);
private:
  //c++11 allows for data to be initialized in the class.
    int discount[6] = {0, 0, 0, 0, 0, 0};
    int gemcount[6] = {0, 0, 0, 0, 0, 0};
    int prestiege;
    Card reserve[3] = {Card(), Card(), Card()};

};
