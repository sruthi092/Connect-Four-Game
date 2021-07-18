#include<iostream>
#include "PROJECT2_A05024226_GAME.h"
#include<chrono>
using namespace std;
using namespace std::chrono;

int main()
{
	int choice;
	Connect4Game connectfour;
	connectfour.setBoard();
	cout<< "Choose your option\n1. Max (Running MinMax A-B with EV#1) verses Min (Running Alpha- Beta Search with EV #1)\n2. Max (Running MinMax A-B with EV#2) verses Min (Running Alpha- Beta Search with EV #2)\n3. Max (Running MinMax A-B with EV#3) verses Min (Running Alpha- Beta Search with EV #3)\n4. Max (Running MinMax A-B with EV#1) verses Min (Running MinMax A-B with EV #2)\n5. Max (Running MinMax A-B with EV#1) verses Min (Running MinMax A-B with EV #3)\n6. Max (Running MinMax A-B with EV#2) verses Min (Running MinMax A-B with EV #3)\n7. Max (Running Alpha- Beta Search with EV#1) verses Min (Running Alpha- Beta Search with EV #2)\n8. Max (Running Alpha- Beta Search with EV#1) verses Min (Running Alpha- Beta Search with EV #3)\n9. Max (Running Alpha- Beta Search with EV#2) verses Min (Running Alpha- Beta Search with EV #3)\n\nInput your choice::" <<endl;
	cin>> choice;
	auto start = high_resolution_clock::now();
	connectfour.playGame(choice);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout<< "\nTime taken to play:: "<< duration.count() << " milli seconds" << endl;
	return 0;
}
