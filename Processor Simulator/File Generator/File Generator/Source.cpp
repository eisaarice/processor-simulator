//Source.cpp

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct job
{
	char jobType; //A B C D
	int processingTime;
	int typeNumber;
	int jobNumber;
	int arrivalTime;
	int waitTime = 0;
};
const int jobSize = sizeof(job); //24

int main()
{
	fstream jobFile("jobs.dat", ios::in | ios::out | ios::trunc | ios::binary);
	if (!jobFile)
	{
		cerr << "jobs.dat could not be opened" << endl;
		return -1;
	}

	fstream orgFile("org.dat", ios::in | ios::out | ios::trunc | ios::binary);
	if (!orgFile)
	{
		cerr << "org.dat could not be opened" << endl;
		return -1;
	}
	
	//5570 total jobs
	job blankFill = { ' ', 0, 0, 0, 0, 0 };

	for (int i = 0; i < 5570; i++) 
	{
		jobFile.write(reinterpret_cast <const char*> (&blankFill), jobSize);
	}
	for (int i = 0; i < 5570; i++) 
	{
		orgFile.write(reinterpret_cast <const char*> (&blankFill), jobSize);
	}

	static int jobNumber = 0;

	static int A = 1;
	//2300 type A jobs
	for (int i = 0; i < 2300; i++)
	{
		static int time = 0;

		blankFill.jobType = 'A';
		blankFill.arrivalTime = (((rand() % 3) + 4)) + (time * 5); //5 +/- 1; 4 5 6
		blankFill.processingTime = rand() % 5 + 1; //3 +/- 2; 1 2 3 4 5
		blankFill.typeNumber = A;
		blankFill.jobNumber = jobNumber;

		jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
		jobFile.write((char*)&blankFill, jobSize);

		time++; A++; jobNumber++;
	}

	static int B = 1;
	//1700 type B jobs
	for (int i = 2300; i < 4000; i++)
	{
		static int time = 0;

		blankFill.jobType = 'B';
		blankFill.arrivalTime = (((rand() % 3) + 6)) + (time * 7); //7 +/- 1; 6 7 8
		blankFill.processingTime = rand() % 9 + 2; //6 +/- 4; 2 3 4 5 6 7 8 9 10
		blankFill.typeNumber = B;
		blankFill.jobNumber = jobNumber;

		jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
		jobFile.write((char*)&blankFill, jobSize);

		time++; B++; jobNumber++;
	}

	static int C = 1;
	//950 type C jobs
	for (int i = 4000; i < 4950; i++)
	{
		static int time = 0;

		blankFill.jobType = 'C';
		blankFill.arrivalTime = ((rand() % 11) + 8) + (time * 13); //13 +/- 5; 8 9 10 11 12 13 14 15 16 17 18
		blankFill.processingTime = rand() % 7 + 6; //9 +/- 3; 6 7 8 9 10 11 12
		blankFill.typeNumber = C;
		blankFill.jobNumber = jobNumber;

		jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
		jobFile.write((char*)&blankFill, jobSize);

		time++; C++; jobNumber++;
	}

	static int D = 1;
	//620 type D jobs
	for (int i = 4950; i < 5570; i++)
	{
		static int time = 0;

		blankFill.jobType = 'D';
		blankFill.arrivalTime = ((rand() % 11) + 14) + (time * 19); //19 +/- 5; 14 15 16 17 18 19 20 21 22 23 24
		blankFill.processingTime = rand() % 9 + 9; //13 +/- 4; 9 10 11 12 13 14 15 16 17
		blankFill.typeNumber = D;
		blankFill.jobNumber = jobNumber;

		jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
		jobFile.write((char*)&blankFill, jobSize);

		time++; D++; jobNumber++;
	}
	
	//write to read
	jobFile.seekg(0, ios::end);

	//order by arrival time (lowest to highest) and if tied by prio (highest to lowest)
	int write = 0;

	//pain.
	for (int i = 1; i < 13000; i++) 
	{
		for (int j = 5569; j > -1; j--) //reverse linear search
		{
			jobFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(j)* jobSize), ios::beg);
			jobFile.read((char*)&blankFill, jobSize);

			if (blankFill.arrivalTime == i)
			{
				orgFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(write)* jobSize), ios::beg);
				orgFile.write((char*)&blankFill, jobSize);

				blankFill = { ' ', 0, 0, 0, 0, 0 }; //reset for next

				write++;
			}
		}
	}

	//write to read
	orgFile.seekg(0, ios::end);

	//display the list
	for (int i = 0; i < 5570; i++)
	{
		orgFile.seekg((static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(i) * jobSize), ios::beg);
		orgFile.read((char*) &blankFill, jobSize);

		cout << left << setw(2) << setfill(' ') << blankFill.jobType << left << setw(20) << setfill(' ') << blankFill.arrivalTime << left << setw(20) << setfill(' ') << blankFill.processingTime << endl;
	}

	//bye bye
	jobFile.close();
	orgFile.close();

	return 0;
}