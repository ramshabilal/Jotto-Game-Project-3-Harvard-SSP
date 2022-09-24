/* Game Project 3
Ramsha Bilal
bilal_week3_gp.cpp
PC
Game: Jotto */


/*Steps:
1. Array of 50 five-letter words
2. randomly choose one out of the 50 - this is answer
3. ask user to guess the word - validate that the guess is 5-lettered
4. save both strings in arrays
5. two loops to compare each character of guess with each char of answer 
6. increment score if common and remove the character from answer when score is 5 
7. loop twice - take input and compare strings (answer and guess)
8. output whether user won or lost
9. display answer in case user lost
*/

#include <string>
#include <iostream>
#include <cstdlib>
#include<ctime>
#include <vector>

using namespace std; 

//function prototypes start here 
string getUserGuess();
bool validateString(string str);
int compareString(string str1, string str2);
void displayScore(int scoreVal, string wordGuess, vector<string>& guess, vector<int>& score);
void getAndDisplayLetters(vector<char>& letterList); 

vector<string> guesses = {}; 
vector<int> scores = {};
vector<char> letters = {};
const int MAX_LETTERS = 5;

// main starts here
int main()
{
	srand(static_cast<unsigned int>(time(0)));

	const int ARRAY_SIZE = 50;
	string vocabulary[ARRAY_SIZE] = { "seven", "world", "about", "again", "heart",
									 "pizza", "water", "happy", "sixty", "board",
									 "month", "angel", "death", "fries", "green",
									 "music", "fifty", "three", "party", "piano",
									 "mouth", "sugar", "woman", "candy", "laugh",
									 "amber", "dream", "apple", "tiger", "faith",
									 "earth", "river", "money", "piece", "forty",
									 "words", "friend", "smile", "house", "alone",
									 "watch", "lemon", "south", "santa", "admin",
									 "women", "blood", "story", "thing", "power" };

	bool valid, stopLoop = false;;
	string userGuess;
	int userScore, noOfGuesses = 0;
	const int MAX_GUESSES = 2, MAX_LETTERS = 5;
	string answer = vocabulary[rand() % 50];

	/*cout << "Answer is: " << answer << endl;     //debug version   */

	cout << "Welcome to Jotto!" << endl;
	do
	{
		do
		{
			userGuess = getUserGuess();
			valid = validateString(userGuess);
		} while (valid == false);

		userScore = compareString(answer, userGuess); 
		displayScore(userScore, userGuess, guesses, scores);  
		if (userScore != 5)
		getAndDisplayLetters(letters);

	} while (userScore != MAX_LETTERS);

	if ((userScore == MAX_LETTERS) && (userGuess==answer)) 
		cout << "Correct. You have won this round of Jotto!" << endl;

	else if (userScore == MAX_LETTERS)
	{
		cout << "You have two guesses." << endl;

		while ((noOfGuesses < MAX_GUESSES) && (stopLoop == false))
		{
			do
			{
				userGuess = getUserGuess();
				valid = validateString(userGuess);
			} while (valid == false);

			noOfGuesses++;
			if (userGuess == answer)
			{
				stopLoop = true;
				cout << "Correct. You have won this round of Jotto!" << endl;
			}
			else
				cout << "Incorrect."; 
		} 
		if (stopLoop == false)
			cout << "You ran out of guesses. The answer was " 
			     << answer << endl;
	}
}


//Functions start here

/*checks that string entered by user is of length 5 (Max Letters) 
  and returns true if valid*/
	bool validateString(string str)
	{
		if (str.length() == MAX_LETTERS)
			return true;
		else
			return false;
	}

/*compares the string entered by user to the answer - it does so by first saving both 
 strings into c-style string arrays and then comparing indexes. It saves an asterisk in answer's array where a letter 
 has been guessed to avoid repition counts how many letters were guessed correctly. These are returned as score. */
int compareString(string str1, string str2)
{
	int score = 0;
	string s1[MAX_LETTERS], s2[MAX_LETTERS];
	for (int i = 0; i < str1.length(); i++)
		s1[i] = str1.substr(i, 1);

	for (int c = 0; c < str2.length(); c++)
		s2[c] = str2.substr(c, 1);

	for (int i = 0; i < MAX_LETTERS; i++)
	{
		for (int j = 0; j < MAX_LETTERS ; j++)
		{
			if (s1[i]==s2[j])
			{
				score++;
				s1[i] = "*";
			}
		}
	}
	/*cout << "string is " << str1 << endl;     // debug version:  */
	return score;
}

/*it prompts the user to guess the answer and takes an input string and returns it. */
string getUserGuess()
{
	string guess;
	cout << "Guess the five-letter word.";
	cin >> guess;

	return guess;
}

/*this function displays the user's score after each turn. 
It also displays the list of scores and guesses after each 
turn. vectors ae passed as arguments by reference to ensure 
the list of scores and guesses is updated after each turn*/
void displayScore(int scoreVal, string wordGuess, vector<string> &guess, vector<int>&score)
{
	cout << "Score on this turn: " << scoreVal << endl << endl;

	guess.push_back(wordGuess);
	score.push_back(scoreVal);  
	cout << "Guesses: " << endl << endl;
		for (string i : guess) 
			cout << i << endl;
		cout << endl;
		cout << "Scores: "<< endl << endl;
		for (int j : score)
			cout << j << endl;
		cout << endl;
}

/*it asks the user if they want to enter letters they think are NOT in the word.
if yes, it lets the user input letters as many times as the user wants. it then displays 
all the letters entered so far with the help of a vector. */
void getAndDisplayLetters(vector<char>& letterList)
{
	int response;
	char letter;
		do
		{
			cout << "Do you want to enter more letters you think are NOT in the word?\n"
				<< "(Choose 1 if yes, choose 0 if no)" << endl;
			cin >> response; 
			if (response == 1)
			{
				cout << "Enter letter: " << endl;
				cin >> letter;
				letterList.push_back(letter);
			}
			else if (response != 0)
				cout << "Invalid response" << endl;
		} while (response != 0);
		 
		cout << "Letters you think are not in the word: \n";
		for (char z : letterList)
			cout << z << "  ";
		cout << endl;
}