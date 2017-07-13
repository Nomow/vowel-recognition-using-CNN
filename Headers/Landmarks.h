#include <vector>
class Landmarks
{
public:
	Landmarks();

	std::vector<std::vector<int> > getCoordinates(float arr[], int arrSize);
	 //gets centroid x
	int getCentroidX(std::vector<std::vector<int> > &Coordinates);
	//gets centroid y
	int getCentroidY(std::vector<std::vector<int> > &Coordinates);
	//gets top left x
	int getTopLeftX(int &width, int &centroid);
	//gets top left y
	int getTopLeftY(int &height, int &centroid);

};
