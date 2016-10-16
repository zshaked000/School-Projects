//ATTEMPT #16 FINAL VERSION DO NOT TOUCH Submitted
//============================================================================
// Name        : HomeWork1Attempt005.cpp
// Author      : Me
// Version     : Robot Players
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//Players 1 and 2 are Robots
#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>

using namespace std;

int role() {return rand()% 6+1;}
//Picks Cho or Han for the Players
string players_ChoHan()
{   int r = rand()%2;
    if (r == 1)
    {return "c";}
    else if(r ==  0)
    {return "h";}
return "0";
}

int main() {
    srand(time(0));

    int you_allow = 100 , player1_allow = 100 , player2_allow = 100;

    while(true) {
        // computer throws 2 dice (-> comp) shows to you
        int comp = role() + role();
       //check if the sum is odd or even
        int sum = comp%2;
        string Odd_even = (sum == 0) ? "c" : "h";
        //balance amount How much money everyone has
        cout << "You have $" << you_allow << endl;
        cout << "  Player1 has $" << player1_allow << endl;
        cout << "  Player2 has $" << player2_allow << "\n" << endl;
        //You place bet
        cout << "  Enter \"c\" (even) or \"h\" (odd) and an amount you bet: ";
        string YouCho_han = "x";int bet;cin >> YouCho_han >> bet;

        //check for legitimate responses
        if(( (YouCho_han != "c") && (YouCho_han != "h")) || !cin)
        {
        	cin.clear();
        	cin.ignore();
            cout << "Invalid response, Please try again"<< endl;
             continue;
        }
        if(cin.fail()|| bet < 0)
        {
        	cin.clear();
        	cout << "invalid response please enter a positive integer value "<< endl;
        	continue;
         }
          if(bet > you_allow)
          {
        	  cout << "Insufficient Funds" << endl;
        	  continue;
          }

        //Players Bet and pick Cho or Han
        int player1_bet, player2_bet;
        // Defensive Position Lecture 5 reference same as if else statement (condition) ? "if statement" : "else statement"
        player1_bet = (player1_allow > you_allow) ? rand() % player1_allow + 1 : rand() % (player1_allow/2) + 1;
        player2_bet = (player2_allow > you_allow) ? rand() % player2_allow + 1 : rand() % (player2_allow/2) + 1;
        // Players Pick Cho or Han
        string player1_chohan = players_ChoHan(), player2_chohan = players_ChoHan();
        //if you win you guessed right, you get money, Did you win or Lose
        if(YouCho_han == Odd_even)
        {
            cout<< "  You bet $" << bet <<" -> won... " << endl;
            you_allow += bet;
        }
        else if  (YouCho_han != Odd_even)
        {
            cout << "  You bet $" << bet << " -> lost " << endl;
            you_allow -= bet;
          //you ran out of money
            if( you_allow <=0)
            {
                cout << "  You are broke... " ;
                break;
            }
        }
        //Player1 win or lose
        if(player1_allow > 0)
        {
            cout << "  Player1 bet $" << player1_bet;
            cout << (player1_chohan == Odd_even ? " -> won... "  : " -> lost... ") << endl;
            player1_allow = (player1_chohan == Odd_even) ? player1_allow += player1_bet : player1_allow -= player1_bet;
        }
        // Player 1 ran out of money
        if(player1_allow <= 0  )
        	cout << "player1 is broke..."<<endl;

        //Player 2 Win or Lose
        if(player2_allow > 0)
        {
            cout << "  Player2 bet $" << player2_bet;
            if (player2_chohan == Odd_even)
            {
                cout<<" -> won... \n"<<endl;
                if(player2_allow <= 0)
                {
                    cout << "  Player2 is broke...\n"<<endl;
                    continue;
                }
                player2_allow += player2_bet;
            }
            else  if (player2_chohan != Odd_even)
            {
                if(player2_allow <= 0)
                    cout << "  Player2 is broke... \n"<<endl;
                cout<<" -> lost... \n"<<endl;
                player2_allow -= player2_bet;
            }
        }
        if (player1_allow && player2_allow <=0)
        {
            cout << "  You Won you beat both Player 1 and Player 2 " << endl;
            break;
        }
}
    cout << "\n  Bye..." << endl;
    return 0;
}
