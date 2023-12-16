// DS: takes as many variables into consideration as possible to create an approach at the plate

// varibales that can affect the situation, this app always calculates the most efficient way to get a run across no matter the score
// create profile for each hitter can assigns a type after a short quiz

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>
#include <unistd.h>
using namespace std;

// write backend of app in cpp i.e all the logic
// write front end i.e how the information gets formatted into an app
// write data holding servers i.e where all the information gets stored to access later

string username;
string path;

class Situation // DONE
{
public:
     int runs[1];
     int innings;
     string topbot;
     int outs;
     int runners;
     int bases[4] = {0, 0, 0, 0};
     int half;

     void situationInp() // takes in the situation of the game, pitcher may be more cautious and have different mindset in some situations DONE
     {
          int input;
          string names[3] = {"first", "second", "third"};
          string inning[3] = {"1st", "2nd", "3rd"};
          string output = "It is the ";

          cout << "Is it the top or the bottom of the inning (T/B)? ";
          std::cin >> topbot;
          if (topbot == "T")
          {
               half = 0;
               output += "top half";
          }
          else if (topbot == "B")
          {
               half = 1;
               output += "bottom half";
          }

          cout << "What inning is it? ";
          std::cin >> innings;
          if (innings < 4)
          {
               output += " of the " + inning[innings - 1];
          }
          else
          {
               output += " of the " + to_string(innings) + "th";
          }

          cout << "How many outs are there? ";
          std::cin >> outs;
          if (outs > 1)
          {
               output += ", there are " + to_string(outs) + " outs, ";
          }
          else if (outs == 1)
          {
               output += ", there is " + to_string(outs) + " out, ";
          }
          else if (outs == 0)
          {
               output += ", there are no outs, ";
          }

          cout << "How many runners are on base? ";
          std::cin >> runners;
          if (runners == 3)
          {

               output += "the bases are loaded,";
               bases[1] = 1;
               bases[2] = 1;
               bases[3] = 1;
          }
          else if (runners != 0)
          {
               output += "there is a runner on";

               for (int i = 0; i < runners; i++)
               {
                    cout << "What base is the " + names[i] + " runner on? ";
                    std::cin >> input;
                    if (runners == 2)
                    {

                         if (i == 0)
                         {

                              output += " " + names[input - 1] + " and";
                         }
                         else
                         {

                              output += " " + names[input - 1] + ",";
                         }
                    }
                    else
                    {

                         output += " " + names[input - 1] + ",";
                    }

                    bases[input] = 1;
               }
          }

          cout << "How many runs does your team have? ";
          std::cin >> runs[0];

          cout << "How many runs does the other team have? ";
          std::cin >> runs[1];
          output += " the score is " + to_string(runs[0]) + "-" + to_string(runs[1]) + "!";

          cout << "Based off of the information you have given me the situation is the follwing.\n";

          cout << output;
     }
};

void hitterNew() // create account for hitter DONE
{
     ofstream hfile;
     hfile.open("/home/hitters.csv");

     string username, password, a1, a2, a3, a4, a5;
     std::cout << "Welcome to account creation:" << endl;
     std::cout << "Enter your username";
     std::cin >> username;
     std::cout << "Now complete this short 5 question quiz" << endl
               << endl;
     std::cout << "Q1. Are you usually early, late or ontime, 0 being very late, 5 on time, 10 very early: ";
     std::cin >> a1;
     hfile << a1 + ","; // write to hitter file quiz info
     std::cout << "Q2. Enter 1 if you are a righty, Enter 2 if you are a left: ";
     std::cin >> a2;
     hfile << a2 + ","; // write to hitter file quiz info

     hfile.close();
     // output for both contact and power
}

string pitcherNew() // create new pitcher profile DONE FINE TUNE ARCHS
{
     std::cout << "Let's create new Pitcher Profile!" << endl;

     int pitch[8][2][1];

     // create a new text file

     int brek;
     int loop;
     float speed;
     float percent;
     string name;
     string pitchName;
     string handedness;
     string newp;

     ofstream allfile;
     allfile.open("/home/username/pitchers.csv", ios::app);

     std::cout << "Please enter the pitchers name formatted as justinVerlander: ";
     std::cin >> name;
     allfile << name + ",";

     std::cout << "Please enter the pitchers Handedness L/R: ";
     std::cin >> handedness;
     allfile << handedness + ",";

     newp = "cp /home/username/pitchers/pitcherDATA.csv /home/username/pitchers/" + name + "DATA.csv"; // copy template and creating new one per pitcher
     system(newp.c_str());                                                                             // create new txt file to hold new pitchers data

     ofstream pfile;
     pfile.open("/home/username/pitchers/" + name + "DATA.csv", ios::app);

     int pitchesnum;
     std::cout << "How many pitches does the pitcher have? ";
     std::cin >> pitchesnum;

     float pitchValue[pitchesnum];
     int pitcherPoints;
     float maxSpeed;

     std::cout << endl
               << "Now enter all the pitches starting with your fastest!" << endl;

     for (int i = 0; i < pitchesnum; i++) // READ WRITE AND EDIT CSV FILE AND PUT THIS DATA ALONG WITH HITTER SHIT INTO IT
     {

          std::cout << "Pitch " + to_string(i + 1) + " name: ";
          std::cin >> pitchName;
          pfile << pitchName + ","; // writing to csv file

          std::cout << "        break towards hour 4 to hour 8 or 0 for straight: ";
          std::cin >> brek;
          pfile << to_string(brek) + ","; // writing to csv file

          std::cout << "        pitch break on a scale from 0-2: ";
          std::cin >> loop;
          pfile << to_string(loop) + ","; // writing to csv file

          std::cout << "        pitch speed in mph: ";
          std::cin >> speed;
          pitch[brek][loop][0] = speed;
          pfile << to_string(speed) + ","; // writing to csv file
          if (i == 0)
          {
               maxSpeed = speed;
          }

          std::cout << "        pitch usage in %: ";
          std::cin >> percent;
          pitch[brek][loop][1] = percent;
          pfile << to_string(percent) + "\n"; // writing to csv file

          if (speed == maxSpeed)
          {
               pitchValue[i] = percent;
               pitcherPoints += pitchValue[i];
               continue;
          }

          switch (brek)
          {
          case 0:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 1;
               break;
          case 4:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 0.9;
               break;

          case 5:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 0.8;
               break;

          case 6:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 0.7;
               break;

          case 7:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 0.8;
               break;

          case 8:
               pitchValue[i] = percent * (speed / maxSpeed) * (1.0 - loop * 0.1) * 0.9;
               break;
          }

          pitcherPoints += pitchValue[i];
     }

     // each pitch points get added up and then divided by the amount of pitches to assign a pitcher type

     allfile << to_string(pitcherPoints) + "\n";

     std::cout << name + "'s profile has been created. He is a " + handedness + "HP and has " + to_string(pitcherPoints) + " pitcher points!" << endl;
     allfile.close();
     pfile.close();

     return name;

     // create an archtype for a pitcher; hard righty, hard left, crafty righty, crafty lefty, stock righty, stock lefty

     // lefty arch algorithm: hard - stock - crafty

     // right arch algorithm: hard - stock - crafty
}

string pitcherFind(string name) // first step after logging in selecting pitcher DONE
{

     ifstream rfile("/home/username/pitchers.csv", ios::in);
     bool login;
     string line;

     while (rfile.good())
     {
          getline(rfile, line, ',');

          if (line.find(name) != string::npos)
          {
               login = true;
               break;
          }
     }
     if (login == true)
     {
          rfile.close();
          return name;
     }
     else
     {
          rfile.close();
          return "";
     }
}

string genie(string pitcherName, string hitterName) // takes approaches and outcomes creates apporach EMPTY
{
     Situation scope;
     scope.situationInp();
     int pitcherValue;
     int situationPoints;
     string situationOutput;
     string hitterHand;

     // get pitcher points
     ifstream rfile("/home/username/pitchers.csv", ios::in);
     string line;

     while (rfile.good())
     {
          getline(rfile, line, ',');

          if (line.find(pitcherName) != string::npos) // this finds the line that has the right pitchers information
          {
               pitcherValue = stoi(line.substr(pitcherName.length() + 4, 2)); // this finds the pitcherValue within the determined line
               break;
          }
     }
     rfile.close();

     // get hitter handedness
     ifstream rfile("/home/username/hitters.csv", ios::in);
     string line;

     while (rfile.good())
     {
          getline(rfile, line, ',');

          if (line.find(hitterName) != string::npos) // this finds the line that has the right hitters information
          {
               hitterHand = line.substr(line.length() - 4, 1); // this finds the hitter handedness within the determined line
               break;
          }
     }
     rfile.close();

     // data set of words it will use to give an approach taking into account hitter handedness
     if (hitterHand == "R")
     {
          string timing[7] = {"very outinfront", "out infront", "slightly out infront", "on time", "slightly deep", "deep", "very deep"};
          string location[7] = {"left field line", "left field", " left-center gap", "center field", "right center gap", "right field", "right field line"};
          string loft[7] = {"very on top", "on top", "slightly on top", "middle", "slightly under", "under", "very under"};
          string type[4] = {"groundball", "low linedrive", "rising linedrive", "fly ball"};
     }
     else if (hitterHand == "L")
     {
          string timing[7] = {"very outinfront", "out infront", "slightly out infront", "on time", "slightly deep", "deep", "very deep"};
          string location[7] = {"right field line", "right field", " right-center gap", "center field", "left center gap", "left field", "left field line"};
          string loft[7] = {"very on top", "on top", "slightly on top", "middle", "slightly under", "under", "very under"};
          string type[4] = {"groundball", "low linedrive", "rising linedrive", "fly ball"};
     }

#pragma region independent situations

     if (scope.runs[1] - scope.runs[0] > 3)
     {
          situationPoints = 5;
          situationOutput = "this situatuion";
          return situationOutput;
     }
     else
     {
          situationPoints = 0;
     }

     if (scope.innings == 1 || scope.innings == 2 || scope.innings == 3)
     {
          situationPoints = 4;
     }

     else if (scope.innings == 4 || scope.innings == 5 || scope.innings == 6)
     {
          situationPoints = 2;
     }

     else
     {
          situationPoints = 0;
     }

#pragma endregion independent situations

     // below will be the real logic of variable dependent situations

     // variables were playing with
     scope.runs; // only matter if its a close game ie sometimes you will want to get runners on sometimes you want to drive them in if its a tie game
     // runs[0] is YOUR teams runs
     scope.innings;
     scope.topbot;
     scope.outs;
     scope.runners;
     scope.bases;
     scope.half;
     int pitcherValue;

     int timing;   // 0 is very early, 6 is very late
     int location; // 0 is down pull line, 3 is up the middle, 6 is down oppo line
     int loft;     // 0 is very on top, 3 is center cut, 6 is way under
     int type;     // 0 groundball (-25 to -5); 1 low linedrive (-5 to 5); 2 risign line drive (5 to 15); 3 fly ball (15-45)

     // create approach without taking pitcher into account first then add effect pitcher has after!!!

     // takes hitters outcomes and takes into account adjustments they should make

     // harder pitch more on top, softwer pitch more under

     // slower inside

     // faster out in front
}

void home(string TEAM) // home function once you are logged in you come here DONE BUT CHANGE MENU TO MAKE MORE USER FRIENYL DO NOT REPRINT WELCOME MESSAGE AND NO NOT MAKE RESIGN IN
{
     string pinput;
     string findpitcher;
     string newpitcher;
     string pitcherName;
     std::cout << "Welcome to your home page. You are now logged in as: " + username + " with the team: " + TEAM << endl;

     std::cout << endl
               << "Which pitcher will you be facing today, please format his name as justinVerlander: ";
     std::cin >> pinput;
     findpitcher = pitcherFind(pinput);

     if (findpitcher == pinput)
     {
          std::cout << "Pitcher Profile found! " << endl;
          pitcherName = pinput;
          std::cout << endl
                    << "Please enter the game situation." << endl;
          std::cout << genie(pitcherName, username);
     }
     else
     {
          std::cout << endl
                    << "Would you like to create a new pitcher? Y/N: ";
          std::cin >> newpitcher;
          if (newpitcher == "Y")
          {
               pitcherName = pitcherNew();
               std::cout << genie(pitcherName, username);
          }
     }
}

int main() // log in host DONE
{
     //   useradd -s /bin/rbash -d /home/restricted_folder username
     string teamname = ""; // create team name variable
     char line[256];       // create char

     FILE *fp = popen("pwd", "r");           // open a file
     while (fgets(line, 256, fp) != nullptr) // get each cahracter of the path which includes the team name
     {
          teamname += line; // add each char value retreived
     }
     pclose(fp);

     teamname.erase(0, 6); // erase the /home/ from the name to only get the team name

     //  root@server-approach:/home# sudo usermod -s /bin/rbash stevens edit the properties
     //  root@server-approach:/home# sudo mkdir -p /home/stevens/restricted //create directory
     //  root@server-approach:/home# sudo usermod -d /home/stevens/restricted stevens //set home directory to that directory

     // scp genie.cpp root@miop.sytes.net:/home/username TO COPY THIS CODE TO LINUX SERVER
     // g++ logic.cpp -o logic THIS IS TO EXCEUTE CPP FILE
     //./ to run

     while (true)
     {
          string password;

          cout << "Welcome to MiOP an app that will provide you with the best approach." << endl
               << endl
               << "If you have a profile please sign in if not press 1 to create your account." << endl
               << "Sign in:" << endl
               << "Username: ";

          std::cin >> username;

          if (username != "1")
          {
               ifstream rfile("/home/username/hitters.csv", ios::in);
               bool login;
               string line;

               while (rfile.good())
               {
                    getline(rfile, line, ',');

                    if (line.find(username) != string::npos)
                    {
                         login = true;
                         break;
                    }
               }
               rfile.close();
               if (login == true)
               {
                    cout << "Log in Successful!" << endl;
                    home(teamname);
               }
               else
               {
                    cout << "Account not found." << endl;
               }
          }

          else
          {
               hitterNew();
          }
     }
}