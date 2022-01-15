#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
//declare functions
void fillArray(double multiArray[][3], const int size, std::istream& inStream);
//precondition: size is the size of multiArray; inStream is opened to a stream;
//postcondition: fills multiArray with values from inStream
int determineDeath(double deathChance[][3], int startingAge, int MF, const int size);
//precondition: deathChance is an array filled with the chance of death per age, males in [x][1] and females in [x][2];
//startingAge < size, MF is initialized to 1 for male or 2 for female, size is the size of the array
//postcondition: checks randomly to see what year the user is likely to die.

//main
int main()
{
	using namespace std;
	//seed random
	srand(time(0));
	//initialize variables and stream
	int age, deathYear;
	char sex;
	double deathChance[120][3];
	ifstream inData("LifeDeathProbability.txt");
	//ensure stream is opened and read in data
	if (inData.fail())
		exit(1);
	else
		fillArray(deathChance, 120, inData);
	//greet user and prompt for input
	cout << "Welcome to the Death Calculator! Using reliable data, this program will determine your likely age of death.\n"
		<< "Please enter your sex - M for male, F for female\n";
	cin >> sex;
	cout << "Please enter your age, in years.\n";
	cin >> age;
	//determine user's likely age of death
	if (sex == 'M' || sex == 'm') //if male
		deathYear = determineDeath(deathChance, age, 1, 120);
	else //if female
		deathYear = determineDeath(deathChance, age, 2, 120);
	//output results
	cout << "You will likely die at age " << deathYear << endl
		<< "Hope that's enough time to accomplish your life goals!\n";
	return 0;
}

//define functions
//uses iostream/fstream
void fillArray(double multiArray[][3], const int size, std::istream& inStream)
{
	double next;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inStream >> next;
			multiArray[i][j] = next;
		}
	}
	return;
}
//uses cstdlib
int determineDeath(double deathChance[][3], int startingAge, int MF, const int size)
{
	double kill;
	for (startingAge; startingAge < size; startingAge++)
	{
		kill = (rand() % 1000) / 10000.0;
		if (kill <= (deathChance[startingAge][MF]))
			return startingAge;
	}
	return size;
}