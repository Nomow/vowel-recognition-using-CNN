#include "Landmarks.h"
Landmarks::Landmarks()
{

}

//gets mouth coordinates
std::vector<std::vector<int> > Landmarks::getCoordinates(float arr[], int arrSize){
  std::vector< std::vector<int> > coordinates;
  std::vector<int> row;
  for (int i = 59; i < 76; ++i){
    coordinates.push_back(row);
    coordinates[i-59].push_back(arr[i * 2]);
    coordinates[i-59].push_back(arr[i * 2 + 1]);
  }
  return coordinates;
}


 //gets centroid x
int Landmarks::getCentroidX(std::vector<std::vector<int> > &Coordinates) {
 int sum = 0;
 for (int i = 0; i < Coordinates.size(); i++) {
   sum += Coordinates[i][0];
 }
 return sum / Coordinates.size();
}

//gets centroid y
int Landmarks::getCentroidY(std::vector<std::vector<int> > &Coordinates) {
 int sum = 0;
 for (int i = 0; i < Coordinates.size(); i++) {
   sum += Coordinates[i][1];
 }
 return sum / Coordinates.size();
}

//gets top left x
int Landmarks::getTopLeftX(int &width, int &centroid) {
 return centroid - width / 2;
}

//gets top left y
int Landmarks::getTopLeftY(int &height, int &centroid) {
 return centroid - height / 2;
}
