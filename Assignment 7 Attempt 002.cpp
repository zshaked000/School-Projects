// Working Version
#include "Simple_window.h"  // get access to our window library
#include "Graph.h"          // get access to our graphics library facilities
#include "Point.h"
#include "GUI.h"
#include "Window.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include<iostream>


using namespace Graph_lib;
using namespace std;

//------------------------------------------------------------------------------
struct t
{
	string hour;
	string min;
	string sec;
	string AMPM;
	int mi;
	int ho;
	int se;
	t(int h,int m , int s)
	{	mi = m;
		ho = h;
		se = s;
		AMPM = (h > 12) ? " PM" : "AM";
		h = (h > 12) ?  h - 12 : h;

		hour = to_string(h);
		min = (m<10) ? "0" + to_string(m) : to_string(m);
		sec = (s<10) ? "0"+to_string(s) : to_string(s);
	}
	};
struct t Time()
{
	  time_t currentTime;
	  struct tm *localTime;

	  time( &currentTime );                   // Get the current time
	  localTime = localtime( &currentTime );  // Convert the current time to the local time

	  int Hour   = localTime->tm_hour;
	  int Min    = localTime->tm_min;
	  int Sec    = localTime->tm_sec;
	  t current_time(Hour,Min,Sec);
	  return current_time;
}
string outtime()
{	t time = Time();
	string outtime = time.hour + ":" + time.min + ":" + time.sec + time.AMPM;
	return outtime;
}
struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title );

    // Data:
    struct t tim;
    float pi;
    int r1;
    int r2;
    float angleh;
    float anglem;
    float angles;

    Open_polyline lines;
    Rectangle r;
    Text t;
    Circle circle;
    Line hours;
    Line mins;
    Line seconds;
    // Widgets:
private:
    //Button digital;
    Button quit_button;    // end program
    Menu color_menu;
    Button menu_button;

    void show_digital() {

    	circle.set_color(Color::invisible);
    	hours.set_color(Color::invisible);
    	mins.set_color(Color::invisible);
    	seconds.set_color(Color::invisible);

    	r.set_color(Color::red);
    	t.set_label(outtime());
    	t.set_color(Color::black);
    	t.set_font_size(36);

    }
    void show_analog() {
    	r.set_color(Color::invisible);
    	t.set_color(Color::invisible);
    	t.set_label("");
    	circle.set_color(Color::black);
        hours.set_color(Color::black);
        hours.set_style(Line_style(Line_style::solid,2));
        mins.set_color(Color::black);
        mins.set_style(Line_style(Line_style::solid,2));
        seconds.set_color(Color::red);

    }

    void hide_menu() { color_menu.hide(); menu_button.show(); }
  //  void hide_digital() {r.set_color(Color::invisible); t.set_color(Color::invisible);}
    // actions invoked by callbacks:
    void analog_pressed() {show_analog(); hide_menu();}
    void digital_pressed() {show_digital(); hide_menu();}
    void menu_pressed() { menu_button.hide(); color_menu.show(); }
    void next();
    void quit();

    // callback functions:
    static void cb_analog(Address,Address);
    static void cb_digital(Address,Address);
    static void cb_menu(Address, Address);
    static void cb_quit(Address, Address);


};


//------------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
	r(Point(150,100),300,200),
	t(Point(210,200),outtime()),
	circle(Point(w/2,h/2),150),
	tim(Time()),
	pi(M_PI),
	angleh(tim.ho*(pi/6) - (pi/2)),
	r1(75),
	hours(Point(w/2,h/2),Point(w/2 + r1*cos(angleh),h/2 + r1*sin(angleh))),
	anglem(tim.mi*(pi/30) - (pi/2)),
	r2(100),
	mins(Point(w/2,h/2),Point(w/2 + r2*cos(anglem),h/2 + r2*sin(anglem))),
	angles(tim.se*(pi/30) - (pi/2)),
	seconds(Point(w/2,h/2),Point(w/2 + r2*cos(angles),h/2 + r2*sin(angles))),
	color_menu(Point(x_max()-70,30),70,20,Menu::vertical,"color"),
    menu_button(Point(x_max()-80,30), 80, 20, "Clock menu", cb_menu),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit)

{
	attach(r);
	attach(t);
	attach(circle);
	attach(hours);
	attach(mins);
	attach(seconds);
    attach(quit_button);
    color_menu.attach(new Button(Point(0,0),0,0,"digital",cb_digital));
    color_menu.attach(new Button(Point(0,0),0,0,"analog",cb_analog));
    attach(color_menu);
    color_menu.hide();
    attach(menu_button);
    attach(lines);
}


//------------------------------------------------------------------------------

void Lines_window::cb_quit(Address, Address pw)    // "the usual"
{
       reference_to<Lines_window>(pw).quit();
}

//------------------------------------------------------------------------------

void Lines_window::quit()
{
    hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

void Lines_window::cb_digital(Address, Address pw)     // "the usual"
{
    reference_to<Lines_window>(pw).digital_pressed();
}

//------------------------------------------------------------------------------

void Lines_window::cb_analog(Address, Address pw)     // "the usual"
{
    reference_to<Lines_window>(pw).analog_pressed();
}

//------------------------------------------------------------------------------

void Lines_window::cb_menu(Address, Address pw)     // "the usual"
{
    reference_to<Lines_window>(pw).menu_pressed();
}

//------------------------------------------------------------------------------

int main()
try {
    Lines_window win(Point(100,100),600,400,"lines");

    return gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}

//------------------------------------------------------------------------------

