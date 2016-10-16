//version 3 Attempt 013 // somewhat works
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
using namespace std;
using namespace chrono;


vector<int> findTheASCII(int level, string user_input)
		{
	vector<int> ASCII;
	for(int i = 0 ; i < level ; ++i)
	{
		char charlie = user_input[i] ;
		int intie = charlie;
		if(charlie == NULL)
			   	{
		 			intie = 32;
	    		}
		ASCII.push_back(intie);
		cout << i << ") user letter: " << charlie << endl;

	}

	return ASCII;
		}


string random_letter_generator(int level)
{   string random_string;
	for(int k =0; k < level ; k++){
	char charlie;
    int r = rand()%1;
    if(r==0)
	charlie = 'a' + rand() % 26;
    if(r==1)
	charlie = 'A' + rand() % 26;
    random_string.push_back(charlie);
	}

return random_string;
}

int Offset(string random_letters, vector<int> rand_ASCII, vector<int> ASCIIinput){
	int total_offset = 0;

		for(int i = 0; i < random_letters.length(); ++i )
		{
			int offset = 0;
			offset = ASCIIinput[i] - rand_ASCII[i];
			cout << "offset = " << ASCIIinput[i] << " - " << rand_ASCII[i] << " = " << ASCIIinput[i] - rand_ASCII[i] << " = " << offset << endl;
			offset = abs(offset);
			cout << i <<") offset: " << offset << endl;
			total_offset += offset;
			cout << "\t total offset: " << total_offset << endl;
		}
	cout << "\t total offset final: "<< total_offset  << endl;
	return total_offset;
}

int main() {

	//string random_letters = "abcd";

	int level = 5;
	int total_points = 1000;
	int rounds_right = 0;
    int rounds_wrong = 0;
    int seconds_allowed = 5000;

    while(true){

	string random_letters = random_letter_generator(level) ;
	cout<< "Enter random letters " << random_letters << endl;
	auto begin = system_clock::now();
	string user_input;// cin >> user_input;
	getline(cin, user_input);
	auto end = system_clock::now();
    int seconds = duration_cast<milliseconds>(end - begin).count();
    cout << " "<< seconds << " milliseconds, ";
	vector<int> ASCIIinput = findTheASCII(level, user_input);
	vector<int> rand_ASCII = findTheASCII(level, random_letters);
	//vector<int> v = {1,2,3,4,5};
    int offset = Offset(random_letters, rand_ASCII, ASCIIinput);
    if (offset == 0)
    {		rounds_wrong = 0;
            ++rounds_right;

            if(seconds <= seconds_allowed)
            {   cout << "you made it within the interval of " << seconds_allowed << "..." << endl;
                total_points += 100;}
            else if (seconds > seconds_allowed)
            {cout << "you *failed* it within the interval of " << seconds_allowed << "..."<< endl;}
            if(rounds_right == 3)
            {++level;
             seconds_allowed -= 250;
            cout << "\n One more challenge!!!";}
            continue;
    }

    else
    { 	cout << "offset is :" << offset <<endl;
    	total_points -= offset;
        rounds_right = 0;
        ++rounds_wrong;
        if(seconds >= seconds_allowed)
        {   cout<< " you *failed* it within the interval of "<< seconds_allowed << "..." << "rounds wrong [" << rounds_wrong << "]" << endl;
            cout<<  " String offset is " << offset << ", your penalty is " << offset*2 <<"..."<<endl;
            total_points -= offset;}
        	if(rounds_wrong >= 3)
        	{
        		--level;
        		seconds_allowed += 250;
        	}

        	if (total_points <=0) {
        		cout << "You lost..." << endl;
        		break;
        	}

     }
	}

	cout << "Bye.." << endl;
return 0;
}


