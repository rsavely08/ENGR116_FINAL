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
string teamname = "";

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

          std::cout << "Is it the top or the bottom of the inning (T/B)? ";
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

          std::cout << "What inning is it? ";
          std::cin >> innings;
          if (innings < 4)
          {
               output += " of the " + inning[innings - 1];
          }
          else
          {
               output += " of the " + to_string(innings) + "th";
          }

          std::cout << "How many outs are there? ";
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

          std::cout << "How many runners are on base? ";
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
                    std::cout << "What base is the " + names[i] + " runner on? ";
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

          std::cout << "How many runs does your team have? ";
          std::cin >> runs[0];

          std::cout << "How many runs does the other team have? ";
          std::cin >> runs[1];
          output += " the score is " + to_string(runs[0]) + "-" + to_string(runs[1]) + "!";

          // std::cout << "Based off of the information you have given me the situation is the follwing.\n";

          // std::cout << output;
     }
};

Situation scope;

void hitterNew() // create account for hitter DONE
{
     ofstream hfile;
     hfile.open("/home/username/hitters.csv", ios::app);

     string username, password, a1, a2, a3, a4, a5;
     std::cout << "Welcome to account creation:" << endl;
     std::cout << "Enter your username: ";
     std::cin >> username;
     hfile << username + ",";
     std::cout << "Now complete this short 5 question quiz" << endl
               << endl;
     std::cout << "Q1. Enter R if you are a righty, Enter L if you are a left: ";
     std::cin >> a1;
     hfile << a1 + ","; // write to hitter file quiz info
     std::cout << "Q2. Are you usually early, late or ontime, 0 being very late, 5 on time, 10 very early: ";
     std::cin >> a2;
     hfile << a2 + "\n"; // write to hitter file quiz info

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

int outMult(int outs)
{

     switch (outs)
     {
     case 0:
          return 4;
     case 1:
          return 8;
     case 2:
          return -4;
     }

     return 1;
}

void genie(string pitcherName, string hitterName) // takes approaches and outcomes creates apporach EMPTY
{
     scope.situationInp();
     int pitcherValue;
     int situationPoints;
     string situationOutput;
     string hitterHand;

     // get pitcher points
     ifstream pfile("/home/username/pitchers.csv", ios::in);
     string pline;

     while (pfile.good())
     {
          getline(pfile, pline, ',');

          if (pline.find(pitcherName) != string::npos) // this finds the line that has the right pitchers information
          {
               pitcherValue = stoi(pline); // this finds the pitcherValue within the determined line
               break;
          }
     }
     pfile.close();

     // get hitter handedness
     ifstream hfile("/home/username/hitters.csv", ios::in);
     string hline;

     while (hfile.good())
     {
          getline(hfile, hline, '\n');

          if (hline.find(hitterName) != string::npos) // this finds the line that has the right hitters information
          {
               hitterHand = hline.substr(hline.length() - 3, 1); // this finds the hitter handedness within the determined line
               break;
          }
     }
     hfile.close();

     string timing[8] = {"very outinfront", "out infront", "slightly out infront", "on time", "slightly deep", "deep", "very deep"};
     string location[8] = {"the left field line", "left field", " the left-center gap", "center field", "the right-center gap", "right field", "the right field line"};
     string loft[8] = {"very on top", "on top", "slightly on top", "middle", "slightly under", "under", "very under"};
     string type[5] = {"groundball", "low linedrive", "rising linedrive", "fly ball"};
     // data set of words it will use to give an approach taking into account hitter handedness
     if (hitterHand == "L")
     {
          timing[0] = "very deep";
          timing[1] = "deep";
          timing[2] = "slightly deep";
          timing[3] = "on time";
          timing[4] = "slightly out infront";
          timing[5] = "out infront";
          timing[6] = "very out infront";
     }

     // variables were playing with
     scope.runs; // only matter if its a close game ie sometimes you will want to get runners on sometimes you want to drive them in if its a tie game
     // runs[0] is YOUR teams runs
     scope.innings; // only effect would be to gear more towards getting runners on base the earler in the game it is and to focus more on scoring the later it is
     scope.outs;    // USED
     scope.runners; // USED
     scope.bases;   // USED

     // pitcher variables i.e what you want to think about taking in the pitcher and the situation
     int time;    // 0 is very early, 100 is very late
     int loftCal; // 0 is very on top, 50 is center cut, 100 is way under

     // situation variables i.e the outcome you want
     int locationCal = 50; // 0 is down pull line, 50 is up the middle, 100 is down oppo line
     int typeCal = 50;     // 0 groundball (25 to 45); 1 low linedrive (45 - 55); 2 risign line drive (55 to 65); 3 fly ball (65 - 100)

     // location and type are both situatin dependent
     // timing and loft is pitcher dependent

#pragma region independent situations

     bool ifind = false;
     // ADD CODE FOR NO BODY ON BASE
     if (scope.bases[3] == 1 && scope.outs < 2)
     {
          locationCal = 50;
          typeCal = 75;
          situationOutput = "this situatuion";
          ifind = true;
     }

     /*
     if (scope.innings == 1 || scope.innings == 2 || scope.innings == 3)
     {
          situationPoints = 4;
          return situationOutput;
     }

     else if (scope.innings == 4 || scope.innings == 5 || scope.innings == 6)
     {
          situationPoints = 2;
          return situationOutput;
     }
     */

     // ADD NO OUTS NO ONE ON
     // ADD RUNNER ON THIRD SITUATIONS

#pragma endregion independent situations

     // below will be the real logic of variable dependent situations

     // create approach without taking pitcher into account first then add effect pitcher has after!!!

#pragma region situation dependent

     if (scope.runners != 0) // RUNNER EFFECT CODE and OUTS EFFECT, makes sure there is a runner on base first
     {
          for (int i = 0; i < scope.runners; i++) // effect each runner has
          {
               if (scope.bases[2] == 1) // logic for runner on second
               {
                    locationCal += 20;
                    typeCal = 45; // need to get something on the ground over rides due to being more important

                    scope.bases[2] = 0; // so that it doestnt read all three runners being atthe same base
               }
               else if (scope.bases[3] == 1) // logic for runner on third
               {
                    locationCal = 0; // override must get runner in, think up the middle so your misses still play;
                    typeCal = 45;    // need to get something on the ground over rides due to being more important

                    scope.bases[3] = 0; // so that it doestnt read all three runners being atthe same base
               }
               else if (scope.bases[1] == 1) // logic for runner on first
               {
                    locationCal += 0;
                    typeCal += 7; // it is at the end to mold approach around it, accomplish two things at once

                    scope.bases[1] = 0; // so that it doestnt read all three runners being atthe same base
               }
          }

          typeCal += outMult(scope.outs);
     }

     if (abs(scope.runs[0] - scope.runs[1]) < 6 - scope.innings * 0.333 && abs(scope.runs[0] - scope.runs[1]) <= scope.runners + 1) // RUNS EFFECT CODE, float vs. int error
     {                                                                                                                              // THIS IS RUN SCORING MODE
          // if the run difference is too significant the code will switch to a mode of trying to get runners on
          // if the run difference is small and conquerable it will stay in lets get every runner in mode
          // the logic in the if statement is saying: if run diff in 1st inning is 5 efficient more but if the run diff in the 8th is 5 try to get runners on

          // LETS SCORE
          locationCal += 10;
          typeCal += 10;
     }
     else // code for when the run difference is too big to over come with just trying to score runners, must get runners on base
     {
          // LETS GET ON BASE
          locationCal -= 10;
          typeCal -= 10;
     }

#pragma endregion situation dependent

     // ADD SECTION THAT PITCHER HAS AN EFFECT

#pragma region pitcher dependent

     time = locationCal;
     loftCal = typeCal;

     time -= pitcherValue / 10;
     // be ealrier with pitcher ISOLATE TIMING BASED OFF OF PITCH SPEED NOT PITCHER POINTS
     // be early with a faster pitcher so think about pulling

     loftCal -= pitcherValue / 10;
     // be more on top the higher the pitcher points
     // think more low linedrive/groundball for faster higher point pitcher

#pragma endregion pitcher dependent

     // STRING DETERMINATION BELOW

     int stringDet;

     stringDet = time / 14.3;                                                                                                 // dvson into int so if 14.3 fits into timing 4 times the number is between 57.2 and 71.5
     situationOutput += "\nThe ideal outcome is to hit a " + type[typeCal / 25] + " to " + location[locationCal / 14] + "! "; // this number then assigns it a string based off of its intensity

     situationOutput += "\nThe mindset to accomplish this is to think about getting the ball " + timing[time / 14] + " and " + loft[loftCal / 14] + "!\n";

     // add a section that selects the strings
     // takes hitters outcomes and takes into account adjustments they should make
     // harder pitch more on top, softwer pitch more under
     // slower inside
     // faster out in front
     cout << situationOutput;
}

void home(string TEAM) // home function once you are logged in you come here DONE BUT CHANGE MENU TO MAKE MORE USER FRIENYL DO NOT REPRINT WELCOME MESSAGE AND NO NOT MAKE RESIGN IN
{
     string pinput;
     string findpitcher;
     string newpitcher;
     string pitcherName;
     std::cout << "Welcome to your home page. You are now logged in as: " + username + " with the team: " + TEAM << endl;

     while (true)
     {

          std::cout << endl
                    << endl
                    << "Which pitcher will you be facing today, please format his name as justinVerlander: ";
          std::cin >> pinput;
          findpitcher = pitcherFind(pinput);

          if (findpitcher == pinput)
          {
               std::cout << "Pitcher Profile found! " << endl;
               pitcherName = pinput;
               std::cout << endl
                         << "Please enter the game situation." << endl;
               genie(pitcherName, username);
          }
          else
          {
               std::cout << endl
                         << "Would you like to create a new pitcher? Y/N: ";
               std::cin >> newpitcher;
               if (newpitcher == "Y")
               {
                    pitcherName = pitcherNew();
                    genie(pitcherName, username);
               }
          }
          cout << endl
               << endl;
     }
}

int main() // log in host DONE
{
     //   useradd -s /bin/rbash -d /home/restricted_folder username; // create team name variable
     char line[256]; // create char

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