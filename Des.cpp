// Including dependancies
#include <iostream>
#include <string>
using namespace std;
// Array to hold the 16 keys
string initalLength[16];

// declaring the string planeText
string planeText = "1010101111001101111001101010101111001101000100110010010100110110";

// Function to do a circular left shift by 1
string leftshiftonce(string inputkey)
{
	string shifted = "";
	for (int i = 1; i < 28; i++)
	{
		shifted += inputkey[i];
	}
	shifted += inputkey[0];
	return shifted;
}
// Function to do a circular left shift by 2
string leftshiftwice(string inputkey)
{
	string shifted = "";
	string firstShift = leftshiftonce(inputkey);
	string secondShift = leftshiftonce(firstShift);
	return secondShift;
}

// Inital permutation on the given Plane Text preeDefined key
void permuTation()
{
	int initialPermutation[64] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

	string permu = "";
	for (int i = 0; i < 64; i++)
	{
		permu += planeText[initialPermutation[i] - 1];
	}
	cout << "The permuted value for the first time is " << permu << endl;

	// Now divide the Inital permuation into two parts to of 32bit each for the other functions
	string leftPermu = permu.substr(0, 32);
	string rightPermu = permu.substr(32, 32);

	// Now wwe uses a expansion box() to expand the 32 bits into the 48 bits
	//  using a pre defined array of 48 bits
	//  The expansion table For RigtPermutation
	int expansionTable[48] = {
		32, 1, 2, 3, 4, 5, 4, 5,
		6, 7, 8, 9, 8, 9, 10, 11,
		12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21,
		22, 23, 24, 25, 24, 25, 26, 27,
		28, 29, 28, 29, 30, 31, 32, 1};

	string rightExpension = "";
	for (int i = 0; i < 48; i++)
	{
		rightExpension += rightPermu[expansionTable[i] - 1];
	}
	cout << "the right expansion is " << rightExpension << "of 48 bits" << endl;
}

// creating a XOR function for which takes two strings as a input
string XOR(string a, string b)
{
	string result = "";
	int size = b.size();
	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			result += "1";
		}
		else
		{
			result += "0";
		}
	}
	return result;
}
void generatekeys(string key)
{
	// The PC1 table
	int pc1[56] = {
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4};
	// The PC2 table
	int pc2[48] = {
		14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32};
	// 1. Compressing the key using the PC1 table
	string permutedkey = "";
	for (int i = 0; i < 56; i++)
	{
		permutedkey += key[pc1[i] - 1];
	}
	// 2. Dividing the result into two equal halves
	string left = permutedkey.substr(0, 28);
	string right = permutedkey.substr(28, 28);
	// Generating 16 keys
	for (int i = 0; i < 16; i++)
	{
		// 3.1. For rounds 1, 2, 9, 16 the inputkeys
		// are shifted by one.
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			left = leftshiftonce(left);
			right = leftshiftonce(right);
		}
		// 3.2. For other rounds, the inputkeys
		// are shifted by two
		else
		{
			left = leftshiftwice(left);
			right = leftshiftwice(right);
		}
		// 4. The chunks are combined
		string combinedkey = left + right;
		string roundkey = "";
		// 5. Finally, the PC2 table is used to transpose
		// the key bits
		for (int i = 0; i < 48; i++)
		{
			roundkey += combinedkey[pc2[i] - 1];
		}
		initalLength[i] = roundkey;
		cout << "Key " << i + 1 << ": " << initalLength[i] << endl;
	}
}
int main()
{
	string key = "1010101010111011000010010001100000100111001101101100110011011101";

	generatekeys(key);
	permuTation();
}