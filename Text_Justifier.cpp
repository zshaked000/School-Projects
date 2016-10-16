//============================================================================
// Name        : Home.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

 //Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string insert_space(int new_space_index,string line)
{
//string line = "hello";
string new_line;
//line.insert(3 , " ");
//cout << line << endl;
new_line = line;
for(int i = new_space_index; i < line.length(); ++i)
{
    new_line[i] = line[i - 1]  ;
}
new_line = new_line + line[line.length() - 1];
new_line[new_space_index] = ' ';
return new_line;
}

string justify_greater_than(int width, string line)
{	vector<int> space_index;
	//cout << "Im in justified greater than " << endl;
while(line.length() != width){
space_index.clear();
for(int i = line.length(); i >= 0; --i) //iterate through the line backwards
{   if(line[i] == ' ' && line[i+1] == ' ') space_index.push_back(i + 1);
else if( line[i] == ' ') space_index.push_back(i);
}

for(int i = 0; i < space_index.size() ; ++i)
{	if(line.length() == width ) break;

	line = insert_space(space_index[i] + 1, line);
}
}
return line;
}



vector<string> justify_less_than(int width, string line)
{
	vector<int> space_indexes;
		vector<int> new_line_indexes;
		new_line_indexes.push_back(0);
		string partial_line ="";
		vector<string> new_lines;
		for(int i = 0; i < line.length(); ++i)
			{   //cout << line[i] << endl;
				if(line[i]  == ' ')
				{
					space_indexes.push_back(i);
				//	cout << "The space indexes are -> " << i << endl;
				}
			}
		int sum = 0;
	//	for(int k = 0; k space_indexes.size)
		int r = 0;
		for(int i = 0; i < space_indexes.size(); ++i)
		{
			sum += space_indexes[i] - r;
			//cout << " sum = sum + space_index - previous space index -> " << sum << endl;
			if(sum > width)
			{
				//new_line_indexes.push_back(space_indexes[i]);
				new_line_indexes.push_back(space_indexes[i-1]);
				// r = space_indexes[i];
				r = space_indexes[i-1];
				//cout << "new line index contains --> " << space_indexes[i] << endl;
				sum = 0;
			}
		}
		new_line_indexes.push_back(line.length());

		for(int i = 0; i < new_line_indexes.size() - 1;++i)
		{	partial_line = "";
			for(int j = new_line_indexes[i] ; j < new_line_indexes[i+1]; ++j )
			{
				partial_line = partial_line + line[j];
			}
			//cout << "these are the partial lines -> " << partial_line << "	these are the partial line sizes -> " << partial_line.length() << endl;
			new_lines.push_back(partial_line);
		}
/*
		for(int i = 0; i < new_lines.size() ; ++i)
		{
			cout << setw(10) << "new_lines vector contains: ->	" << new_lines[i] << endl;
		}
*/
		string l;
		vector<string> justified_new_lines;
		for(int i = 0; i < new_lines.size() ; ++i)
				{
					//new_lines[i] = justify_greater_than(width,new_lines[i]);
					justified_new_lines.push_back( justify_greater_than(width,new_lines[i]));
				}

//return new_lines;
		/*
		for(int i = 0 ; i < justified_new_lines.size() ; ++i)
		{
			cout << justified_new_lines[i] << endl;
		}
		*/
		return justified_new_lines;
}

int Justify(int width, string line, vector<string>list_of_lines, vector<string> new_lines)
		{

    for(int i = 0; i < list_of_lines.size(); ++i)
    {
    	line = list_of_lines[i];

	if(width >= line.length() )
	{
	line = justify_greater_than(width,  line);
	cout << line << endl;
	//continue;
	}

	if(width < line.length() )
	{
		new_lines = justify_less_than(width,line);
		for(int i  = 0; i < new_lines.size() ; ++ i)
			{
				//cout <<"new Lines -> " << new_lines[i] << endl;
				cout  << new_lines[i] << endl;
			}
		//continue;
	}
	}
    cout << "Enter a width " << endl;
return width;
		}



int main() {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	//string line = "Hello my name is Bob"; // length of the line is 20
	string line = "Hi im the coolest guy";
	//cout << line << endl;
	vector<string> new_lines;
	int width = 20;
    cout << "Enter lines " << endl;
    vector<string> list_of_lines;
	while(line != ""){
    getline(cin,line);
    //line = "I am the most coolest coder there ever was to be ever cause Im cool Im the best coder to ever code because I code coding";
    	//	cout << "line length " << line.length() << endl;
    list_of_lines.push_back(line);
    if(line == ""){ break;}
	}
	while(true){
cout << "Enter a Width " << endl;
cin >> width;
Justify( width, line, list_of_lines, new_lines);
	}




	//cout << line << endl;
	//cout << "line length: " << line.length() << endl;
	return 0;
}
