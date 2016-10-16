#include<iostream> //FINAL SHORT VERSION Submitted
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

int role() {return rand()% 6+1;}
//Picks Cho or Han for the Players
string players_ChoHan()
{  int r = rand()%2;
    if (r == 1)
    {return "c";}
    else if(r ==  0)
    {return "h";}
    else return "YOU FAILED";}

//Check if Players 1 and 2 won or lost money, adjust their allowance
int Players(int player_number,string Odd_even, int player_allow, string player_ChoHan, int player_bet)
{
    if(player_allow > 0){
        cout << "Player"<< player_number << " bet $" << player_bet;
        cout << (player_ChoHan == Odd_even ? " -> won... "  : " -> lost... ");
        cout << (player_number == 2 ? "\n" : "") << endl;
        player_allow = (player_ChoHan == Odd_even) ? player_allow += player_bet : player_allow -= player_bet;
        return player_allow;
    }
    if(player_allow <= 0  )// Player 1 or 2 ran out of money
    {  cout << "player" << player_number <<" is broke..."<<endl;
        return 0;}
    return 0;}

int main() {
    srand(time(0));

    int you_allow = 100 , player1_allow = 100 , player2_allow = 100;

    while(true) {

    	int comp = role() + role();// computer throws 2 dice (-> comp) shows to you
        int sum = comp%2; //check if the sum is odd or even, assign officail Cho Han
        string Odd_even = (sum == 0) ? "c" : "h";

        cout << "You have $"<< you_allow << "\n" << "  Player1 has $" << player1_allow << endl
        		<<"  Player2 has $" << player2_allow << "\n" << endl; //balance amount How much money everyone has
        cout << "Enter \"c\" (even) or \"h\" (odd) and an amount you bet: ";//You place bet
        string YouCho_han ; int bet; cin >> YouCho_han >> bet;
        //check for legitimate responses
        if( ( (YouCho_han != "c") && (YouCho_han != "h")) || !cin)
        	{cout << "\n Invalid response, Please try again \n"<< endl;
            cin.clear();
            cin.ignore();
            continue;}
        if(cin.fail() || bet < 0) {
        	cout << "\n invalid response please enter a positive integer value \n"<< endl; continue;}
        if(bet > you_allow){
        	cout << "\n Insufficient Funds \n" << endl;
        	continue;}

  //Players Bet and pick Cho or Han and take Defensive Position Lecture 5 reference same as if else statement (condition) ? "if statement" : "else statement"
        int player1_bet, player2_bet;
        player1_bet = (player1_allow > you_allow) ? rand() % player1_allow + 1 : rand() % (player1_allow/2) + 1;
        player2_bet = (player2_allow > you_allow) ? rand() % player2_allow + 1 : rand() % (player2_allow/2) + 1;
        string player1_chohan = players_ChoHan(), player2_chohan = players_ChoHan(); // Players Pick Cho or Han
  //if you win you guessed right, you get money, Did you win or Lose
        cout << "You bet $" << bet << (YouCho_han == Odd_even? " -> won... " : " -> lost...") << endl;
        you_allow = (YouCho_han == Odd_even)?you_allow += bet : you_allow+-bet;
   //Did you lose, you ran out of money, terminate game
            if( you_allow <=0)
            {cout << "You are broke... " ; break;}
   //Players 1 and 2 win or lose
            player1_allow = Players(1,Odd_even, player1_allow, player1_chohan, player1_bet);
            player2_allow = Players(2,Odd_even, player2_allow,player2_chohan, player2_bet);
   // Did you Win?, Terminate Game
            if (player1_allow && player2_allow <=0){
        cout << "  You Won you beat both Player 1 and Player 2 " << endl;break; }
   }
    cout << "\n Bye..." << endl;
    return 0;
}
