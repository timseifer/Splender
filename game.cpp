/*
 * game.cpp
 * COMP11 Splendor
 Edited: Tim Seifert tseife01
 Part 1 focuses on getting the data types right for the game splendor.
 Part 2 focuses on game mechanics.
 */

#include "game.h"
#include <vector>


vector<Card> Mines;
vector<Card> Transport;
vector<Card> Vendors;
vector<Card> nobles;
int num_cards_m = 0;
int num_cards_t = 0;
int num_cards_v = 0;
int num_cards_n = 0;
int gem_bank[8] = {4, 4, 4, 4, 4, 5, 4, 4};
Player *player_1 = new Player();
Player *player_2 = new Player();
int counterusem = 0;
int counteruset = 0;
int counterusev = 0;
int counterusen = 0;

//constructor
Game::Game(string filename, string play_nobles){
   //include nobles or not
   if(play_nobles == "true"){
        this->play_nobles = true;
   }else{
        this->play_nobles = false;
   }

   //initialize the board
   for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }

setupGame(filename);

    /*-----------------------------------------------*/
    /*          FINISH SETTING UP THE GAME           */
    /*-----------------------------------------------*/
}



//main game loop
void Game::playGame(){
    screen_bg("black");
    screen_fg("white");

    bool game_over = false;
    bool player1_turn = true;
    bool wentwong = false;
    while(!game_over){
        //reset the screen

        string move;
        
        if(nobleloyalty(player_1, nobles) != -1){
          nobles[nobleloyalty(player_1, nobles)].setGemColor();
          player_1->setPrestige(nobles[nobleloyalty(player_1, nobles)]);
          nobles[nobleloyalty(player_1, nobles)].setPrestige();
        }
        if(nobleloyalty(player_2, nobles) != -1){
          nobles[nobleloyalty(player_2, nobles)].setGemColor();
          player_1->setPrestige(nobles[nobleloyalty(player_1, nobles)]);
          nobles[nobleloyalty(player_1, nobles)].setPrestige();
        } 
        if(player_1->totalPrestige() == 15){
          game_over = true;
        }else if(player_2->totalPrestige() == 15){
          game_over = true;
        }
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        
        drawBoard();
        
        int p = 0;
        int g = 0;
        for(int i = 0; i < 6; i++){
        p = p + player_1->getGemCount(i);
        g = g + player_2->getGemCount(i);
      }
        if(p > 10){
          string l;
          cout << " PLAYER 1, you have more than 10 gems! Name one gem you would like to return: ";
          cin >> l;

          int v = colortonum(l);
          player_1->setGemCount(v, -1);
          setgembank(v, 1);
          p--;
           wentwong = true;
           player1_turn = !player1_turn;
        }else if(g > 10){
         string l;
         cout << " PLAYER 2, you have more than 10 gems! Name one gem you would like to return: ";
         cin >> l;

         int v = colortonum(l);
         player_2->setGemCount(v, -1);
         setgembank(v, 1);
         g--;
          wentwong = true;
          player1_turn = !player1_turn;
       }else{
         wentwong = false;
         if(!wentwong){
         if(player1_turn == true){
           cout << " PLAYER 1, ";
         }else{
           cout << " PLAYER 2, ";
         }
          cout << "enter your next move: ";
          cin >> move;
        }
        
                     Player* arg;
                     if(player1_turn == true){
                      arg = player_1;
                     }else{
                      arg = player_2;
                     }
            
                     if(move == "q"){
                       game_over = true;
                       // cout << endl;

                     }else if(move == "p2"){
                       string color;
                       int coln;
                       cin >> color;
                       coln = colortonum(color);
                       if(getgembank(coln) == 4 && coln != 5){
                       arg->setGemCount(coln, 2);
                       setgembank(coln, -2);
                     }else{
                       wentwong = true;
                      cout<<  " Invalid move (unavailable gems) - enter a valid move: ";
                      player1_turn = !player1_turn;
                     }
                   }else if(move == "p3"){
                       string color;
                       int coln;
                       cin >> color;
                       coln = colortonum(color);
                       arg->setGemCount(coln, 1);
                       setgembank(coln, -1);
                       cin >> color;
                       coln = colortonum(color);
                       arg->setGemCount(coln, 1);
                       setgembank(coln, -1);
                       cin >> color;
                       coln = colortonum(color);
                       arg->setGemCount(coln, 1);
                       setgembank(coln, -1);
                     }else if(move == "r"){
                       string rt;
                       int val;
                       cin >> rt;
                       cin >> val;
                       bool t = false;
                       for(int i = 0; i < 3; i++){
                          if(arg->getReserve(i).getGemColor() == "null"){
                            t = true;
                          }else{
                            t = false;
                          }
                       }
                      if(t == true){
                       if(rt == "m"){
                        Mines[Mines.size()-val] = arg->setReserve(val, Mines, counterusem);
                        counterusem++;
                       }
                       if(rt == "t"){
                         Transport[Transport.size()-val] = arg->setReserve(val, Transport, counteruset);
                         counteruset++;
                       }
                       if(rt == "v"){
                        Vendors[Vendors.size()-val] = arg->setReserve(val, Vendors, counterusev);
                        counterusev++;
                       }
                       arg->setGemCount(5, 1);
                       setgembank(5, -1);
                     }else{
                       wentwong = true;
                      cout<<  " Invalid move (reserve is already full) - enter a valid move: ";
                      player1_turn = !player1_turn;
                     }

                     }else if(move == "b"){
                       string bt;
                       int valb;
                       cin >> bt;
                       cin >> valb;
                       int tempval = arg->getGemCount(5);
                       if(bt == "m" && playervcard(*arg, Mines[Mines.size()-valb], tempval)){
                        // cout << "yup" <<endl;

                        playervcardo(arg, Mines[Mines.size()-valb], tempval);
                        arg->setDiscount(colortonum(Mines[Mines.size()-valb].getGemColor()), 1);
                        arg->setPrestige(Mines[Mines.size()-valb]);
                        Mines[Mines.size()-valb] = Mines[Mines.size()-5-counterusem];
                        counterusem++;
                      }else if(bt == "t" && playervcard(*arg, Transport[Transport.size()-valb], tempval)){
                         // cout << "yup" <<endl;

                         playervcardo(arg, Transport[Transport.size()-valb], tempval);
                         arg->setDiscount(colortonum(Transport[Transport.size()-valb].getGemColor()), 1);
                         arg->setPrestige(Transport[Transport.size()-valb]);
                         Transport[Transport.size()-valb] = Transport[Transport.size()-5-counteruset];
                         counteruset++;
                       }else if(bt == "v" && playervcard(*arg, Vendors[Vendors.size()-valb], tempval)){
                         // cout << "yup" <<endl;

                         playervcardo(arg, Vendors[Vendors.size()-valb], tempval);
                          arg->setDiscount(colortonum(Vendors[Vendors.size()-valb].getGemColor()), 1);
                         arg->setPrestige(Vendors[Vendors.size()-valb]);
                        Vendors[Vendors.size()-valb] = Vendors[Vendors.size()-5-counterusev];
                        counterusev++;
                       }else{
                         wentwong = true;
                        cout<<  " Invalid move (not enough gems) - enter a valid move: ";
                        player1_turn = !player1_turn;
                       }
                     }else if(move == "br"){
                       int valb;
                       cin >> valb;
                       int tempval = arg->getGemCount(5);
                       if(playervcard(*arg, arg->getReserve(-1+valb), tempval)){
                        // cout << "yup" <<endl;
                        playervcardo(arg, arg->getReserve(-1+valb), tempval);
                        arg->setDiscount(colortonum(arg->getReserve(-1+valb).getGemColor()), 1);
                        arg->setPrestige(arg->getReserve(-1+valb));
                        arg->ResetReserve(-1+valb);
                      }else{
                        wentwong = true;
                        cout<<  " Invalid move (not enough gems) - enter a valid move: ";
                        player1_turn = !player1_turn;
                       }
                     }else{
                       wentwong = true;
                       cout<<  " Invalid move - enter a valid move: ";
                       player1_turn = !player1_turn;
                     }

           }
        /*-----------------------------------------------*/
        /*             PLAY A TURN OF THE GAME           */
        /*-----------------------------------------------*/

         
        //change turns
        player1_turn = !player1_turn;
    }
    if(player_1->totalPrestige() == 15){
      clearBoard();
      screen_clear();
      screen_home();
      //draw the board
      
      drawBoard();
      cout << " Congratulations Player 1: YOU WIN!!!!"<< endl;
    }else if(player_2->totalPrestige() == 15){
      clearBoard();
      screen_clear();
      screen_home();
      //draw the board
      
      drawBoard();
      cout << " Congratulations Player 2: YOU WIN!!!!"<< endl;
    }
    vector<Card>().swap(Mines);
    vector<Card>().swap(Transport);
    vector<Card>().swap(Vendors);
    vector<Card>().swap(nobles);
    //so valgrind doesn't get angry >:(
    delete player_1;
    delete player_2;

    screen_bg("white");
    screen_fg("black");
}
int Game::nobleloyalty(Player* arg, vector<Card> n){
  
  int b = 0;
  for(int j = 0; j < 3; j++){
    b = 0;

      for(int i = 0; i < 5; i++){
      int v = stoi(n[j].getPrice(i));
      if(arg->getDiscount(i) >= v){
      b++;
        }
    }
if(b == 5){
  // n[j] = Card();
  return j;
}else if(j == 2){
  return -1;
}
}
return -1;
}
bool Game::playervcard(Player argc, Card type, int tempv){

  for(int i = 0; i < 5; i++){
    // cout << i << endl;
    int l = stoi(type.getPrice(i));
    if(l == 0){
      continue;
    }else if(argc.getGemCount(i)+argc.getDiscount(i) >= l){
      continue;
    }else if(argc.getGemCount(i)+argc.getDiscount(i)+tempv >= l){
      tempv--;
      continue;
    }else{
      // cout << "i value and in false" << endl;
      // cout<< i<< endl;
      return false;
    }
  }
  return true;
}
int Game::playervcardo(Player* argc, Card type, int tempv){

  for(int i = 0; i < 5; i++){
    // cout << i << endl;
    int l = stoi(type.getPrice(i));
    // while(l != 0){
    if(l == 0){
      continue;
    }else if(argc->getDiscount(i) >= l){
      // l -= arg->getDiscount(i);
      continue;
    }else if(argc->getGemCount(i)+argc->getDiscount(i) >= l){
      // cout << "cost of card: ";
      // cout << l << endl;
      // cout <<"at" << i << "discount is: ";
      // cout << argc->getDiscount(i) << endl;

      int p = l - argc->getDiscount(i);
      argc->setGemCount(i, -p);
      setgembank(i, p);
      // l -= argc->getGemCount(i)+argc->getDiscount(i);
      continue;
    }else if(argc->getGemCount(i)+argc->getDiscount(i)+tempv >= l){
      int j = l - (argc->getGemCount(i) + argc->getDiscount(i));
      setgembank(i, argc->getGemCount(i));
      argc->setGemCount(i, -argc->getGemCount(i));
      argc->setGemCount(5, -j);
      setgembank(5, j);
      tempv = tempv - 1;
      continue;
    }else{
      // cout << "i value and in false" << endl;
      // cout<< i<< endl;
    }
  // }
  }
  return tempv;
}

int Game::colortonum(string color){
  if(color == "white"){
     return 0;
  }
  if(color == "red"){
    return 1;
  }
  if(color == "pink"){
     return 2;
  }
  if(color == "blue"){
    return 3;
  }
  if(color == "green"){
   return 4;
  }
  if(color == "yellow"){
    return 5;
  }else{
    return 8;
  }
}
void Game::setgembank(int index, int num){
  gem_bank[index] = gem_bank[index] + num;
}

int Game::getgembank(int index){
  return gem_bank[index];
}
//This is the function that creates the vectors as the file is being
//read in. Passes in two arguments, a physical card, and then the vector.
void Game::addCardm(Card *m, vector<Card> &ctype){
      ctype.push_back(*m);
      // cout << "adding card" << endl;
      // cout << ctype.size() << endl;
      num_cards_m++;
}
//Setupgame allows for the splendor data to be read in.
//utilizes to helper funcitons addCardm and ReadCard to do so.
//only one argument passed through being splendor_data.
bool Game::setupGame(string splendor_data){
    //Read in the splendor file
    //Do this by taking splendor data and turning it into
    // a string stream.
    string line;
    stringstream ss;
    ifstream inFile;
    inFile.open (splendor_data.c_str());
    while(getline(inFile, line)){
      // cout << "strings" << endl;
      ss<< line << "\r\n";
    }
    ss.clear();
    ss.seekg(0, ios::beg);
    //getline because we don't want that useless info in the beg.
    getline(ss, line);
    //Used a similar concept from aliens vs predators to read data
    //in. Read in data according to data file, mines first.
    Card *a = new Card();
    bool success = a->ReadCard(&ss);
    while (success) {
      //add a card given you can read one in.
        addCardm(a, Mines);
        delete a;
        //create a new one.
        a = new Card();
        success = a->ReadCard(&ss);

    }
    //clean up after oneself.
    delete a;

    //Read in the transport
    Card *t = new Card();
    success = t->ReadCard(&ss);
    while (success) {
        addCardm(t, Transport);
        delete t;
        t = new Card();
        success = t->ReadCard(&ss);

    }
    delete t;

    Card *v = new Card();
    success = v->ReadCard(&ss);
    while (success) {
        addCardm(v, Vendors);
          delete v;
        v = new Card();
        success = v->ReadCard(&ss);

    }
    delete v;

    Card *n = new Card();
    success = n->ReadCard(&ss);
    while (success) {
        addCardm(n, nobles);
        delete n;
        n = new Card();
        success = n->ReadCard(&ss);

    }

    delete n;

    return true;
    // ss.close();

}
//Grid setter makes the grid actually point to physical cards. using
//the respective vectors and understanding the grid, grid can be set
//to the correct starting cards.
void Game::gridSetter(){
  //This was my debugging strategy. Kept in because ***
  //data below is useful for part 2                 ***

  // for(int i = 0; i < Vendors.size(); i++){
  //   cout << "vendor data:"<< i << endl;
  //   cout << Vendors.at(i).getPrestiege() << endl;
  //   cout << Vendors.at(i).getType() << endl;
  // }
  // for(int i = 0; i < Vendors.size(); i++){
  //   cout << "Transport data:"<< i << endl;
  //   cout << Transport.at(i).getPrestiege() << endl;
  //       cout << Transport.at(i).getType() << endl;
  // }
  // for(int i = 0; i < Vendors.size(); i++){
  //   cout << "mines data:"<< i << endl;
  //   cout << Mines.at(i).getPrestiege() << endl;
  //       cout << Mines.at(i).getType() << endl;
  // }
  // cout << "in grid setter" << endl;

  for(int i = 0; i < CARD_ROWS; i++){
      for(int j = 0; j < CARD_COLS; j++){
            if(i == 0){
              grid[i][j] = &Vendors.at(Vendors.size()-1-j);
            }
            if(i == 1){
              grid[i][j] = &Transport.at(Transport.size()-1-j);
            }
            if(i == 2){
              grid[i][j] = &Mines.at(Mines.size()-1-j);
            }
      }
  }
}
//indexToColor just goes to a respective index and returns a color.
//Takes one argument being the index.
string Game::indexToColor(int index){
  if(index == 0){
    return "white";
  }
  if(index == 1){
    return "red";
  }
  if(index == 2){
    return "pink";
  }
  if(index == 3){
    return "blue";
  }
  if(index == 4){
    return "green";
  }
  if(index == 5){
    return "yellow";
  }else{
    return "";
  }
}
//some arrays are global variables because they need to
//by accessed by more than one function.


void Game::drawBoard(){
    int vpos = 0;
    int hpos = 1;

    // draw the card decks
    if(!Vendors.empty()){
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if(!Transport.empty()){
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if(!Mines.empty()){
        drawDeck(vpos, hpos, "Mines");
    }
    //before we draw the grid we need to set the grid to
    //some cards.
    gridSetter();
    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for(int i = 0; i < CARD_ROWS; i++){
        for(int j = 0; j < CARD_COLS; j++){
            if(grid[i][j] != nullptr){
                drawCard(vpos, hpos, *grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            int index = (i * 2) + j;

            if(gem_bank[index] > 0){
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }

    //draw players

    drawPlayer(vpos + 1, 1, player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), player_2);


    //draw nobles
    if(play_nobles){
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for(int i = 0; i < NUM_NOBLES; i++){
            if(nobles.size()-7 == NUM_NOBLES){
              if(nobles[i].getGemColor() == "n"){
                drawNoble(vpos, hpos, nobles.at(i));
              }
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            if(board_color[i][j] != "white"){
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
   }
   cout << endl;
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card c){
    string top    = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank  = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < 5; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for(int i = 0; i < GEMS-1; i++){
        int price = stoi(c.getPrice(i));
        if(price > 0){
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p){
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if(hpos < 10){
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    }else{
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for(int i = 0; i < GEMS-1; i++){
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if(bonus >= 10){
            length += 1;
        }
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    for(int i = 0; i < GEMS; i++){
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for(int i = 0; i < 3; i++){
        Card c = p->getReserve(i);
        //c
        if(c.getGemColor() == "null"){
            drawDeck(vpos, hpos, "");
        }else{
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for(int i = 0; i < length; i++){
        board[vpos + (CARD_HEIGHT/2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color){
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for(int i = 0; i < GEMS; i++){
        int length = gem_image[i].length();
        for(int j = 0; j < length; j++){
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card c){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];

        if(i == 8 || i == 9){
            board_color[vpos + 1][hpos + i] = c.getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = stoi(c.getPrestiege()) + 48;
    board_color[vpos + 2][hpos + 8] = c.getGemColor();
    board_color[vpos + 2][hpos + 9] = c.getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c.getGemColor();
    board_color[vpos + 1][hpos + 9] = c.getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for(int i = 0; i < GEMS-1; i++){
        int price = stoi(c.getPrice(i));
        if(price > 0){
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }

}

//clear the board display
void Game::clearBoard(){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }
}
