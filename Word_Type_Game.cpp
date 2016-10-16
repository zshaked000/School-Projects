//version 3 Attempt 013 // somewhat works version 2 // Zachary Shaked
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
using namespace std;
using namespace chrono;


vector<int> findTheASCII(int level, string user_input) // changes string into ASCII code
	{
	vector<int> ASCII;
	for(int i = 0 ; i < level ; ++i)
	{
		char charlie = user_input[i] ;
		int intie = charlie;
		if(charlie == NULL){intie = 32;}
		ASCII.push_back(intie);
	}
	return ASCII;
		}

string random_letter_generator(int level) // creates random string for user to input
{   string random_string;
	for(int k =0; k < level ; k++){
	char charlie;
    int r = rand()%2;
    if(r==0)
	charlie = 'a' + rand() % 26;
    if(r==1)
	charlie = 'A' + rand() % 26;
    random_string.push_back(charlie);
	}

return random_string;
}
//Find the Offset between the user input and the rand letters
int Offset(string random_letters, vector<int> rand_ASCII, vector<int> ASCIIinput){
	int total_offset = 0;

		for(int i = 0; i < random_letters.length(); ++i )
		{   int offset = 0;
			offset = ASCIIinput[i] - rand_ASCII[i];
			offset = abs(offset);
			total_offset += offset;
		}
	return total_offset;
}

int main() {
	int level = 5, total_points = 1000, rounds_right = 0, rounds_wrong = 0, seconds_allowed = 5000;

	while(true){
	string random_letters = random_letter_generator(level) ; // changed
	cout << "Your current points " << total_points << ", just type [" << level << "] ->" << random_letters << ": ";
	auto begin = system_clock::now(); // time how long it takes user to enter input
	string user_input;
	getline(cin, user_input);
	auto end = system_clock::now();
    int seconds = duration_cast<milliseconds>(end - begin).count();
    cout << seconds << " milliseconds, ";
	vector<int> ASCIIinput = findTheASCII(level, user_input);
	vector<int> rand_ASCII = findTheASCII(level, random_letters );//changed
    int offset = Offset( random_letters , rand_ASCII, ASCIIinput);
    if (offset == 0) // if user enters the word correctly
    {		rounds_wrong = 0;++rounds_right; // keeps track of how many consecutive times the user is correct or incorrect

            if(seconds <= seconds_allowed)
            {   cout << "you made it within the interval of " << seconds_allowed << "..." << endl;
                total_points += 100;} // if user is correct and within the alloted time interval, their total points go up
            else if (seconds > seconds_allowed)
            {cout << "you *failed* it within the interval of " << seconds_allowed << "..."<< endl;}
            if(rounds_right == 3)  {
            	cout << "One more for next challenge!!!"<< endl;
            	++level; // if user is correct 3 consecutive times, goes up a level, time allowed decreases
            	seconds_allowed -= 250; }
            cout << endl;
            continue;
    }
// if user enters words incorrectly
    if(offset != 0) {
    	total_points -= offset; // adjusts points according to offset
        rounds_right = 0; // sets consecutive rounds right to 0
        ++rounds_wrong; //keeps track of rounds wrong

        if(seconds >= seconds_allowed) // user goes into over time
        {   cout<< " you *failed* it within the interval of "<< seconds_allowed << "..." << endl;
            cout<<  "String offset is " << offset << ", your penalty is " << offset*2 <<"..."<<endl;
            total_points -= offset; // if the user is wrong and goes over time, dedcuts the offset from the total points a second time
        }
        else
            {cout<<  "String offset is " << offset << ", your penalty is " << offset <<"..."<<endl;}
        if(rounds_wrong == 2 && level > 5) cout << "Make next round for not going back!!!" << endl;
        if(rounds_wrong >= 3){
        		--level;
        		if(level < 5){level = 5;} //user can't go below level 5
        		seconds_allowed += 250;}
        	cout << endl;
        	//if the user ran out of points they lose, end of game
        	if (total_points <=0) {
        		cout << "You lost..." << endl;
        		break;
        	}

    }
}
	cout << "Bye.." << endl;
return 0;
}
