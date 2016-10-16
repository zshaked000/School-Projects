//============================================================================
// Name        : Home.cpp
// Author      : Me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>

#include <vector>

#include <string>

#include <stdlib.h>

using namespace std;


struct card {

    string suit;

    string value;
};

class deck {

private:

vector<card> the_deck ;

public:

    deck() {

        initializeDeck();

    }

    void initializeDeck() {

        the_deck.clear();
        vector<string> numbers;

        for(int i = 2 ; i < 11 ; ++i){
        	string c = to_string(i);
        	numbers.push_back(c);
        }
     numbers.push_back("J"), numbers.push_back("Q"),numbers.push_back("K"),numbers.push_back("A");

   for(int i = 0; i < numbers.size(); ++i)
   {        card card1 = {"Diamonds",numbers[i]},card2 = {"Clubs",numbers[i]},card3 = {"Hearts",numbers[i]}, card4 = {"Spades",numbers[i]} ;
        	the_deck.push_back(card1),the_deck.push_back(card2),the_deck.push_back(card3),the_deck.push_back(card4);
   }
 }
    card getRandomCard() {
        int randIndex = rand() % the_deck.size();
        card temp = the_deck[randIndex]; //Pick random card from deck of cards
        the_deck.erase(the_deck.begin() + randIndex); //remove the card from the deck so it cant be picked again
        return temp; // return the random card to the random hand
    }
    string toString() {
    	string result = "The deck has these cards: \n";
        for(int i = 0; i < the_deck.size() ; ++i){
            result += the_deck[i].suit + the_deck[i].value + "\n";
        }
        return result;
  }

    vector<card> getRandomHand(int size) {
        vector<card> random_hand(size);
        for(int i = 0; i < size ; ++i){
           random_hand[i] = getRandomCard();//create a hand of random cards
        }
        return random_hand;
    }
};

class player{
private:
 vector<card> hand;

public:
    player() {
    }
   void setNewHand(vector<card> newHand) {
        hand = newHand;
    }
    string handToString() {
        string result = "";

        for(int i = 0; i < hand.size() ; ++i)        {
          result += "(" + to_string(i) + ") " +  hand[i].suit + hand[i].value + "\t";
        }
       return result;
   }


// returns a card from the hand
    card pickCard(int index) {
        card temp = hand[index];
       hand.erase(hand.begin() + index);
       return temp;
   }


// not in use
    card pickRandomCard() {
        int randIndex = rand() % hand.size();
       card temp = hand[randIndex];
        hand.erase(hand.begin() + randIndex);
        return temp;
    }


// checks if the cards are all the same
    bool allSameSuit() {
        for(int i = 1; i < hand.size(); ++i)      {
            if(hand[i].suit != hand[i - 1].suit)            {
                return false;
          }
        }
        return true;
    }

    card CompPickCard()
    { 	int index = 0 , Dcards = 0, Hcards = 0, Scards = 0 , Ccards = 0;
    	card temp;
    	vector<int> DcardsIndexes;
    	vector<int> HcardsIndexes;
    	vector<int> ScardsIndexes;
    	vector<int> CcardsIndexes;

    	for(int i = 0; i < hand.size(); ++i)
    	{			if(hand[i].suit == "Diamonds")
    		    	{
    					++Dcards;
    					DcardsIndexes.push_back(i);
    		    	}

    		    	if(hand[i].suit == "Spades")  {
    		    		++Scards;
    		    		ScardsIndexes.push_back(i);
    		    	}

    		    	if(hand[i].suit == "Clubs")	{
    		    		++Ccards;
    		    		CcardsIndexes.push_back(i);
    		    	}
    		    	if(hand[i].suit == "Hearts"){
    		    		++Hcards;
    		    		HcardsIndexes.push_back(i);
    		    	}
    	}
    	int suit = LeastOccuring(DcardsIndexes.size(), ScardsIndexes.size(), CcardsIndexes.size(), HcardsIndexes.size());
    	switch(suit)
    	{
    	//Diamonds
    	case 1:
    		index = DcardsIndexes[0];
    		temp = hand[DcardsIndexes[0]];
    		hand.erase(hand.begin() + index);
    		break;
    	//Spades
    	case 2:
    		index = ScardsIndexes[0];
    		temp = hand[ScardsIndexes[0]];
    		hand.erase(hand.begin() + index);
    	    break;
    	//Clubs
    	case 3:
    		index = CcardsIndexes[0];
    		temp = hand[CcardsIndexes[0]];
    		hand.erase(hand.begin() + index);
    		break;
    	//Hearts
    	case 4:
    		index = HcardsIndexes[0];
    		temp = hand[HcardsIndexes[0]];
    		hand.erase(hand.begin() + index);
    	    		break;
    	}
    	return temp;
    }

    int MostOccuring(int num1, int num2, int num3, int num4)
    {
    	if(num1 >= num2 && num1 >= num3 && num1 >= num4)
    	{//return "Diamonds";
    		return 1;}
    	if(num2 >= num1 && num2 >= num3 && num2 >= num4)
    	{//return "Spades";
    		return 2;}
    	if(num3 >= num2 && num3 >= num1 && num3 >= num4)
    	{	//return "Clubs";
    		return 3;}
    	if(num4 >= num2 && num4 >= num3 && num4 >= num1)
    	{	//return "Hearts";
    		return 4;}

    	else
    	{
    		cout << "MostOccuring function failed "<< endl;
    		abort();
    		//return "Failed";
    		return 0;}
    }

    int LeastOccuring(int num1, int num2, int num3, int num4)
    {	if(num1 == 0) num1 = 100;
    	if(num2 == 0) num2 = 100;
    	if(num3 == 0) num3 = 100;
    	if(num4 == 0) num4 = 100;
    	if( num1 <= num2 && num1 <= num3 && num1 <= num4)
    	{//return "Diamonds";
    		return 1;}
    	if( num2 <= num1 && num2 <= num3 && num2 <= num4)
    	{//return "Spades";
    		return 2;}
    	if( num3 <= num2 && num3 <= num1 && num3 <= num4)
    	{	//return "Clubs";
    		return 3;}
    	if( num4 <= num2 && num4 <= num3 && num4 <= num1)
    	{	//return "Hearts";
    		return 4;}

    	else
    	{
    		cout << "MostOccuring function failed "<< endl;
    		abort();
    		//return "Failed";
    		return 0;}
    }
    void AddCard(card temp)
       {
       	hand.push_back(temp);
       }


};

int main() {
	srand(time(0));
    deck mydeck;
    int choice;
   //initialize the players
    player me, comp1 , comp2 , comp3 , comp4;
    me.setNewHand(mydeck.getRandomHand(7)),comp1.setNewHand(mydeck.getRandomHand(7)), comp2.setNewHand(mydeck.getRandomHand(7)), comp3.setNewHand(mydeck.getRandomHand(7)), comp4.setNewHand(mydeck.getRandomHand(7));
//do the game loop
    while(true){
        cout << me.handToString() << endl;
        cout << "Choose a card to pass: " << endl;
        char response;        cin >> response;
        if(response == '?')
        {	cout << "player1 hand  -> "  << comp1.handToString() << "\n"<< "player2 hand  -> "  << comp2.handToString() << "\n";
        	cout << "player3 hand  -> "  << comp3.handToString() << "\n" << "player4 hand  -> "  << comp4.handToString() << "\n";
        }
        choice = response - '0';

        if (choice >= 0 && choice < 7) {
            card temp_me = me.pickCard(choice), temp_comp1 = comp1.CompPickCard() , temp_comp2 = comp2.CompPickCard(), temp_comp3 = comp3.CompPickCard(), temp_comp4 = comp4.CompPickCard();

            me.AddCard(temp_comp1);
            cout << "comp1 passed card " << temp_comp1.suit << temp_comp1.value << " to me!" << endl;

            if (me.allSameSuit()) {
                cout << "You won!" << endl;
               break;
            }

            comp1.AddCard(temp_me);
            if (comp1.allSameSuit())  {
            	cout << "Comp won " << endl;

                break;

                return 0;

            }

            comp2.AddCard(temp_comp3);
            if (comp2.allSameSuit())  {

                cout << "You lost..." << endl;
                break;
                return 0;
            }
            comp3.AddCard(temp_comp4);
             if (comp3.allSameSuit())  {
                       cout << "You lost..." << endl;
                       break;
                   }
             comp4.AddCard(temp_comp2);
                          if (comp2.allSameSuit())  {
                        	  cout << "You lost..." << endl;
                        	  break;
                        	  return 0;
                          }
}
        else {
   cout << "Invalid card selection!" << endl;
  continue;
 }
}
    cout << "Bye..." << endl;
    return 0;
}



