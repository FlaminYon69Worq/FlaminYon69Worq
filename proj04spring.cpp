// Author: David Mendoza, UIC, Spring 2021

// Project 04

// Project Due Date: 3/19/2021, 5:00 PM

// Project Overview: DIVVY Bike Data, check stats, durations, starting times, any stations near me
// checks stations with amount of trips found in each station, finds stations with a keyword, and searches for any trips within a timespan

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct BikeData // bike.txt
{
   string  ID;
   int     Capacity;
   double  Lat;
   double  Long;
   string name;
   double NearMeDist;
   int TripsFound = 0;
   int searchFound;
};

struct TripData //trips.txt
{
   string  BikeID;
   string     TripID;
   string StartID;
   string EndID;
   int duration;
   string time;
   int isFound;
  int TripsFound;
  
};

BikeData* inputBike(string filename, int& S) 
{
   //
   // try to open the file, check to make sure successful:
   //
   ifstream infile;

   infile.open(filename);

   if (!infile.good())  // failed to open:
   {
      S = 0;
      return nullptr;
   }

   //
   // file open, input N then input the N 
   //
   infile >> S;  // first line of file is # of bike stations

   BikeData* bike = new BikeData[S];  // dynamically-allocate array of struct

   for (int i = 0; i < S; i++)  // now input the bikeData
   {
      infile >> bike[i].ID;
      infile >> bike[i].Capacity;
      infile >> bike[i].Lat;
      infile >> bike[i].Long;
      getline(infile, bike[i].name);
   }

   infile.close();

   //
   // done, return pointer to array we created:
   //
   return bike;
}

TripData* inputTrips(string filename, int& T)
{
   //
   // try to open the file, check to make sure successful:
   //
   ifstream infile;

   infile.open(filename);

   if (!infile.good())  // failed to open:
   {
      T = 0;
      return nullptr;
   }

   //
   // file open, input N then input the N 
   //
   infile >> T;  // first line of file is # of trips

   TripData* trips = new TripData[T];  // dynamically-allocate array of struct

   for (int i = 0; i < T; i++)  // now input the bikeData
   {
      infile >> trips[i].BikeID;
      infile >> trips[i].TripID;
      infile >> trips[i].StartID;
      infile >> trips[i].EndID;
      infile >> trips[i].duration;
      infile >> trips[i].time;
   }

   infile.close();

   //
   // done, return pointer to array we created:
   //
   return trips;
}

void statsFunction(BikeData bike[], int& T, int&S) { // called in stats
  int count = 0;
  cout << "  stations: " << S << endl; //print out s
  cout << "  trips: " << T << endl; //print out t
  for (int i = 0; i < S; i++) {
    count += bike[i].Capacity; 
  }
  cout << "  total bike capacity: " << count << endl;
}

void TripDuration(TripData trips[], int& T) { //called in durations, lists categories of durations
  int i; //loop 
  
  int catLessEq30 = 0; // categories of times set to 0
  int cat30to60 = 0;
  int cat1to2Hours = 0;
  int cat2to5Hours = 0;
  int cat5HoursPlus = 0;
  
  for (i = 0; i < T; i++) {
    if (trips[i].duration <= 1800) { // 1800 is 30 min
      catLessEq30++; //increment
    }
    else if (trips[i].duration > 1800 && trips[i].duration <= 3600) { //1800 is 30 min or 3600 is an hr
      cat30to60++;
    }
    else if (trips[i].duration > 3600 && trips[i].duration <= 7200) { // 7200 seconds is 2hrs 
      cat1to2Hours++;
    }
    else if (trips[i].duration > 7200 && trips[i].duration <= 18000) { // 18000 seconds is 5hrs
      cat2to5Hours++;
    }
    else if (trips[i].duration > 18000) { //5 hrs or more
      cat5HoursPlus++;
    }
  } //cout the categories
  cout << "  trips <= 30 mins: " << catLessEq30 << endl;
  cout << "  trips 30..60 mins: " << cat30to60 << endl;
  cout << "  trips 1-2 hrs: " << cat1to2Hours << endl;
  cout << "  trips 2-5 hrs: " << cat2to5Hours << endl;
  cout << "  trips > 5 hrs: " << cat5HoursPlus << endl;
}


void makeHistogram (TripData trips[], int& T) { //called in starting
  int* starting = new int[24]; // make new array
  string tempStr;
  std::string::size_type pos;
  for (int i = 0; i < 24; i++) {
    starting[i] = 0; //0, 1, 2, 3, 4 are categories = to 0.
  }
  for(int i = 0; i < T; i++) {             
    pos = trips[i].time.find(":");    
    tempStr = trips[i].time.substr(0, pos); // extract hours from trips[i].time
    if (tempStr == "0") { // if the hour is 0, 1, 2...etc
      starting[0]++; // increment the category
    }
    else if (tempStr == "1") {
      starting[1]++;
    }
    else if (tempStr == "2") {
      starting[2]++;
    }
    else if (tempStr == "3") {
      starting[3]++;
    }
    else if (tempStr == "4") {
      starting[4]++;
    }
    else if (tempStr == "5") {
      starting[5]++;
    }
    else if (tempStr == "6") {
      starting[6]++;
    }
    else if (tempStr == "7") {
      starting[7]++;
    }
    else if (tempStr == "8") {
      starting[8]++;
    }
    else if (tempStr == "9") {
      starting[9]++;
    }
    else if (tempStr == "10") {
      starting[10]++;
    }
    else if (tempStr == "11") {
      starting[11]++;
    }
    else if (tempStr == "12") {
      starting[12]++;
    }
    else if (tempStr == "13") {
      starting[13]++;
    }
    else if (tempStr == "14") {
      starting[14]++;
    }
    else if (tempStr == "15") {
      starting[15]++;
    }
    else if (tempStr == "16") {
      starting[16]++;
    }
    else if (tempStr == "17") {
      starting[17]++;
    }
    else if (tempStr == "18") {
      starting[18]++;
    }
    else if (tempStr == "19") {
      starting[19]++;
    }
    else if (tempStr == "20") {
      starting[20]++;
    }
    else if (tempStr == "21") {
      starting[21]++;
    }
    else if (tempStr == "22") {
      starting[22]++;
    }
    else if (tempStr == "23") {
      starting[23]++;
    }     
  }
  for (int i = 0; i < 24; i++) {
    cout << "  " << i << ": " << starting[i] << endl; // print out index, then the number in each category
  }
  delete[] starting;
}

//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}

void sortByDist(BikeData bike[], int& S) //sort distances
{
    for (int i = 0; i < S-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < S; j++)
      {
         if (bike[j].NearMeDist < bike[minIndex].NearMeDist)
         {
            minIndex = j;
         }
      }
      
      BikeData temp = bike[i];
      bike[i] = bike[minIndex];
      bike[minIndex] = temp;
   }
}

void NearMe(BikeData bike[], int&S, double latitude, double longitude, double inDist) { //called in nearme
  double temp;
  int someFound = 0;
  cout << "The following stations are within " << inDist << " miles of (" << latitude << ", " << longitude << "):" << endl;
  
  for (int i = 0; i < S; i++) {
    bike[i].NearMeDist = 0;
    temp = distBetween2Points(latitude, longitude, bike[i].Lat, bike[i].Long); //temp = the distance
    //cout << temp << endl;
    if (temp <= inDist) { //if distances in trips array are less than or equal to the input distance
      bike[i].NearMeDist = temp; //assign temp to object in struct
      someFound++; //increment counter
    }

  }

  if (someFound == 0) { //not found
      cout << "  none found" << endl;
  }
  else{
    sortByDist(bike, S); //sort distances
    for (int i = 0; i < S; i++) {
      if (bike[i].NearMeDist != 0) { //print stations that are in the range
        cout << "  station " << bike[i].ID << " (" << bike[i].name << "): " << bike[i].NearMeDist << " miles"<< endl;
      }
    }
  }
}


void sortByName(BikeData bike[], int& S) //sort names
{
    for (int i = 0; i < S-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < S; j++)
      {
         if (bike[j].name < bike[minIndex].name)
         {
            minIndex = j;
         }
      }
      
      BikeData temp = bike[i];
      bike[i] = bike[minIndex];
      bike[minIndex] = temp;
   }
}

void sortByNewName(string inStr[], int S)
{ //sort for stationName
    for (int i = 0; i < S-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < S; j++)
      {
         if (inStr[j] < inStr[minIndex])
         {
            minIndex = j;
         }
      }
      
      string temp = inStr[i];
      inStr[i] = inStr[minIndex];
      inStr[minIndex] = temp;
   }
}


void CheckStation (BikeData bike[], TripData trips[], int& T, int& S) { //prints out all stations and their trips found
  // called in stations
  for (int i = 0; i < S; i++) {
    bike[i].TripsFound = 0;
    for (int j = 0; j < T; j++) { //if the IDs match
      if (trips[j].StartID == bike[i].ID || trips[j].EndID == bike[i].ID) {
        bike[i].TripsFound++; //increment the row on bike; if IDs match, add 1 to this count move on to the next bike ID
      } 
    }
  }
  sortByName(bike, S); //sort the names alphabetically
  for (int i = 0; i < S; i++) { //print the names
    cout << bike[i].name << " (" << bike[i].ID << ") @ (" << bike[i].Lat << ", " << bike[i].Long << "), " <<
      bike[i].Capacity << " capacity, " << bike[i].TripsFound << " trips" << endl;
  }
}



void searchStations(BikeData bike[], TripData trips[], int&T, int&S, string keyword) { //called in find 
  int someFound = 0; //count for if the keyword is found
  std::string::size_type pos;
  for (int i = 0; i < S; i++) { 
    bike[i].TripsFound = 0; //initialize these objects in struct
    bike[i].searchFound = 0;
    pos = bike[i].name.find(keyword); //find keyword  
    if (pos != string::npos) { //if keyword is found      
      bike[i].searchFound++; //updates to 1 or 0, 1 being found, 0 being not found
      someFound++;
    }
    for (int j = 0; j < T; j++) {
      if (trips[j].StartID == bike[i].ID || trips[j].EndID == bike[i].ID ) {
        bike[i].TripsFound++; //same logic as stations, searches tripsfound again
      }    
    }
  }
  if (someFound == 0) { //if all bike[i].searchFound are 0, then nothing was found for that keyword
      cout << "none found" << endl;
  }
  else{
    sortByName(bike, S);
    for (int i = 0; i < S; i++) {
      if (bike[i].searchFound != 0) { // for bike[i].searchFound is 1
        cout << bike[i].name << " (" << bike[i].ID << ") @ (" << bike[i].Lat << ", " << bike[i].Long << "), " <<
        bike[i].Capacity << " capacity, " << bike[i].TripsFound << " trips" << endl;
      }
    }
  }
}


int search(BikeData bike[], int& S, string inName) { //searches for IDs
    int i;   
    for (i = 0; i < S; ++i) {
      if (inName == bike[i].ID) { //if ID matches in bike
        return i;
      }     
    }
    return -1;  // not found
 }

int getTimeVal(string inStr) //gets total min of time
{
    int retInt;
    std::size_t pos;
    pos = inStr.find(':'); //find the colon
    // if the left hand side, right hand side are empty, and there is no colon,
    if (inStr.substr(0, pos) == "" || inStr.substr(pos+1) == "" || pos == string::npos){
        retInt = -1; //no time found
    }
    else {
        retInt = (60 * stoi(inStr.substr(0, pos)) + stoi(inStr.substr(pos+1))); // in minutes
    }
    return retInt;
}

void FindTripsTime(BikeData bike[], TripData trips[], int&T, int&S, string time1, string time2) { //finds trips w/in a timespan
    int startInt, endInt, currentBikeTime; //startInt and EndInt are 1st and 2nd time inputs,
    //converted into total minutes, respectively
    //currentBikeTime is the trips[i].time at the index, converted into minutes
    int count = 0, n = 0; //count for how many stations are found, n is an index
        int seconds = 0; //total seconds for average
  
  int* tripsDuration = new int[T]; //durations for the times found w/in the timespan
  string* stationName = new string[S+1]; //names of stations found w/in a timespan, S+1 to make sure we do not access any element
                                         // out of bounds
  
        startInt = getTimeVal(time1); //convert time1 and time2 into minutes
        endInt = getTimeVal(time2);
  for (n = 0; n < S+1; n++){
         stationName[n] = ""; //initalize as blank string
  }

  for (int i = 0; i < T; i++) {
     tripsDuration[i] = 0;
     currentBikeTime = getTimeVal(trips[i].time); //convert time of the index of loop
     
    if(( currentBikeTime>= startInt &&
         currentBikeTime <= endInt && //falls within a range, which is the first case before the ||
         currentBikeTime >= 0) ||
         (endInt - startInt < 0 && trips[i].duration && //accounts for cases like trips 23:30 0:30, the wrap around case
         (currentBikeTime >= startInt || currentBikeTime <= endInt))){ //multiple conditions
       
       int index = search(bike, S, trips[i].StartID); //searches for ID 
       if (index != -1) { //if found a name
         tripsDuration[i] = trips[i].duration; //set durations and names into the new arrays
         stationName[count++] = bike[index].name;
       }
     }
   }
                     
  if (count == 0) { //none found
   cout << "none found" << endl;
 }
  else { //x amount of trips found
    for (int i = 0; i < T; i++) {
        if(tripsDuration[i] != 0){
         seconds = seconds + tripsDuration[i]; //for all trips durations (in new array) not equal to 0, update total seconds
      }						                           
    } //cout everything
   cout << count << " trips found" << endl;
   cout << "  avg duration: " << (seconds/60)/count << " minutes" << endl;
   cout << "  stations where trip started: ";
  sortByNewName(stationName, count); //sort the new array stationName
  for (int i = 0; i < count; i++){
      int s = i;
      while (stationName[s] == stationName[s+1] && s+1 != count){ //checks for duplicates
        for (int x = s; x < count; x++){
          stationName[x] = stationName[x+1]; //if array index right nwo = array index next
        }
        count--; //for duplicates, shift array left
    }     
  }

    for (int i = 0; i < count; i++){
      cout << stationName[i];
      if (stationName[i+1] != ""){ //comma, same logic as executestmt on project 3
        cout << ", "; //if there are more names found, print comma for more names. else (empty string), stop printing
    }     
  }
  cout << endl;
    
  }
  delete[]stationName; //delete new arrays
  delete[]tripsDuration;
}




int main()
{ 
    // intro
    cout << "** Divvy Bike Data Analysis **" << endl; 

    string filename;
    cout << "Please enter name of stations file> " << endl;
    cin >> filename;
    BikeData* bike = nullptr;
    int          S = 0; 
    bike = inputBike(filename, S);
  for (int i = 0; i < S; i++) {
    bike[i].name.erase(0, bike[i].name.find_first_not_of(" "));
  }
    
   if (S <= 0) //S is number of bike stations
   {
     cout << "**Error: unable to open input file '" << filename << "'" << endl;
     return 0;
   }
     
    cout << "Please enter name of bike trips file> " << endl; //trips.txt
    cin >> filename;
    TripData* trips = nullptr;
    int          T = 0;  
    trips = inputTrips(filename, T);
     
   if (T <= 0) //T is number of trips
   {
     cout << "**Error: unable to open input file '" << filename << "'" << endl;
     return 0;
   }
     
     // declare command as a string
     string command = " ";
     cout << "Enter command (# to stop)>   ";
// "stats - Outputs the total # of stations, the total # of trips, and the total capacity across all the stations." 
// "durations - Analyzes the bike trips, and then categorizes the trips into 1 of 5 categories based on the duration." 
// "starting - Analyzes the bike trips, and then categorizes the trips into 1 of 24 categories based on the starting hour." 
// "nearme - Finds all stations near a given position, expressed as latitude (Y coordinate) and longitude (X coordinate)." 
// "stations - Lists all stations in alphabetical order by name. For each station, the output includes the name, station ID, 
//        "position (latitude, longitude), capacity, and the total # of bike trips where this station was the starting station 
//        "or the ending station." 
// "find (station) - Performs a case-sensitive search of the stations whose name includes the word input by the user"   
// "trips, timespan - Searches the bike trips for all trips with a start time that falls within the given timespan." 
     cin >> command;
     
     //while loop of commands
     while (command != "#") {   
       if (command == "stats") { //for each command, a function is called
           statsFunction(bike, T, S); //call stats
         }
          
       else if (command == "durations") { 
           TripDuration(trips, T); //call durations function
         }
              
       else if (command == "starting") { 
         makeHistogram (trips, T); //call starting function
       }
       
       else if (command == "nearme") { 
         double latitude, longitude, dist;
         cin >> latitude >> longitude >> dist; //input latitude, longitude, and the distance from coordinates
         NearMe(bike, S, latitude, longitude, dist); //call nearme
       }
       
       else if (command == "stations") { 
         CheckStation(bike, trips, T, S); //call stations function       
       }
       
        else if (command == "find") { 
          string word;
          cin >> word; //input keyword
         searchStations(bike, trips, T, S, word); //call find function
       }
       
        else if (command == "trips") {
          string timeBegin1, timeBegin2;
          cin >> timeBegin1 >> timeBegin2; //input range of times
         FindTripsTime(bike, trips, T, S, timeBegin1, timeBegin2); //call trips function       
       }
       
       else { //invalid command
         cout << "** Invalid command, try again..." << endl;
       }
       
     cout << "Enter command (# to stop)>   ";
     cin >> command;
     }

  //done
     cout << "** Done **" << endl;
  
  //delete the arrays
     delete[]bike;
     delete[]trips;
  
     return 0;
}    
