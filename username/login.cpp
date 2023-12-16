// DS: takes as many variables into consideration as possible to create an approach at the plate

// varibales that can affect the situation, this app always calculates the most efficient way to get a run across no matter the score
// create profile for each hitter can assigns a type after a short quiz

#include <iostream>

using namespace std;

int main() // log in host DONE
{

     string teamname;

     cout << "Welcome to MiOP an app that will provide you with the best approach." << endl
          << endl
          << "Please enter your teamname: ";

     std::cin >> teamname;

     teamname = "ssh " + teamname + "@miop.sytes.net";

     system(teamname.c_str());
}