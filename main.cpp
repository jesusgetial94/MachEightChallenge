#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring> 
#include <string>   

using namespace std;

// Maximum quatity of elements in the input array
#define max 100

// Declare the array of strings
string strings[max];

// The total sum value
int target;

// Input array to be processed
vector<int> originalArray;

//Result array. Each row represents a correct solution. Each row includes 2 values
vector< vector < int > > result;

/// @brief Prints each element from vector of numbers
/// @param a Reference to the vector
/// @param message Message to print
void PrintVector(std::vector <int> const &a, string message) {
   std::cout << message;

   for(int i=0; i < a.size(); i++)
   std::cout << a[i] << ' ';

   std::cout << "" << std::endl;
}

/// @brief Stores a correct solution
/// @param val1 First value that matches the conditions
/// @param val2 Second value that matches the conditions
void AddResult(int val1, int val2){
  vector<int> resultArray {val1, val2};
  // Verify duplicated solutions
  for (size_t i = 0; i < result.size(); i++)
  {
    if(result[i][0] == val1 || result[i][0] == val2){
        return;
    }
  }
  
  result.push_back(resultArray);
  cout << "Solution : " << val1 << " , " << val2 << endl;
}

/// @brief Find 2 values from 2 vectors that matches the conditions
/// @param vec1 vector 1 to be processed
/// @param vec2 vector 2 to be processed
void CompareArrays(std::vector <int> const &vec1, std::vector <int> const &vec2){
  
  // Find the values that matches the conditions
  for (size_t i = 0; i < vec1.size(); i++)
  {
    int currentValue = vec1[i];
    int differenceToTarget = target - currentValue;

    bool existRequiredNumber = std::find(vec2.begin(), vec2.end(), differenceToTarget) != vec2.end();
    if(existRequiredNumber){
      AddResult(currentValue, differenceToTarget);
    }

  }
}

/// @brief Calculates the length of string
/// @param str 
int Len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;          
    }
    return length;     
}

/// @brief Separates an string into pieces based on the separetor symbol
/// @param str String to be splitted
/// @param separetor Symbol that separate the pieces
/// @return The quantity of pieces
int Split (string str, char seperator)  
{  
  int currIndex = 0, i = 0;  
  int startIndex = 0, endIndex = 0;  
  while (i <= Len(str))  
  {  
    if (str[i] == seperator || i == Len(str))  
    {  
        endIndex = i;  
        string subStr = "";  
        subStr.append(str, startIndex, endIndex - startIndex);  
        strings[currIndex] = subStr;  
        currIndex += 1;  
        startIndex = endIndex + 1;  
    }  
    i++;  
  }   
  return currIndex;
} 

/// @brief Convert string to vector int
/// @param str String to be processed
void LoadArray(string str){
  char seperator = ',';
  int arraySize = Split(str, seperator);   
  for (int i = 0; i < arraySize; i++)  
  {
    // Convert string to int
    int num = stoi(strings[i]);
    originalArray.push_back(num);
  } 
}

/// @brief Main function
/// @param argc Quantity of arguments in command line
/// @param argv Array of arguments
int main(int argc, char const *argv[])
{
  // Checks the minimum arguments
  if (argc < 3)
  {
    std::cout << "Not enough arguments!\n";
    return -1;
  }
  
  // Add the array from command line
  LoadArray(argv[1]);   

  // Load the target from command line
  target = stoi(argv[2]); 

  PrintVector(originalArray, "Original vector : ");

  // Size of input array
  size_t originalArrayLength = originalArray.size();
  int targetHalf = target / 2;                                           // Target half
  bool isEvenTarget = !(target % 2);                                     // Is the target an even number ?
  int targetSign = (target >= 0) - (target < 0);                         // Is the target a negative number ?

  
  // Auxiliar arrays. Each array has 2 rows. 
  // The first one stores the odd numbers and second one stores the even numbers
  vector <vector<int>> smallerHalfNumbers {{},{}};    // Numbers smaller than the target half
  vector<vector<int>> greaterHalfNumbers{{},{}};      // Numbers greater than the target half
  vector <vector<int>> negativeNumbers {{},{}};       // Numbers lower than zero
  vector<vector<int>> greaterTargetNumbers{{},{}};    // Numbers greater than the target

  // Elements classification. Clasifies as even or odd numbers and greater or smaller than target half
  for (size_t i = 0; i < originalArrayLength; i++)
  {
    int currentValue = originalArray[i];
    bool isEvenNumber = !(currentValue % 2);

    bool isNegativeNumber = (currentValue * targetSign) < 0;
    if(isNegativeNumber) {
      negativeNumbers[isEvenNumber].push_back(currentValue);
      continue;
    }
    bool isGreaterTarget = (currentValue * targetSign) > (target * targetSign);
    if(isGreaterTarget) {
      greaterTargetNumbers[isEvenNumber].push_back(currentValue);
      continue;
    }
    bool isSmallerHalf = (currentValue * targetSign) < (targetHalf * targetSign);
    if(isSmallerHalf) {
      smallerHalfNumbers[isEvenNumber].push_back(currentValue);
      continue;
    }
    bool isGreaterHalf = (currentValue * targetSign) >= (targetHalf * targetSign);
    if(isGreaterHalf) {
      greaterHalfNumbers[isEvenNumber].push_back(currentValue);
    }
  }

  // Depending on target classification, even number or odd number. It makes differnt comparisons
  if(isEvenTarget){
    // Even target. 

    // EvenNumber + EvenNumber = EvenNumber
    CompareArrays(negativeNumbers[1], greaterTargetNumbers[1]);
    CompareArrays(smallerHalfNumbers[1], greaterHalfNumbers[1]);

    // OddNumber + OddNumber = EvenNumber
    CompareArrays(negativeNumbers[0], greaterTargetNumbers[0]);
    CompareArrays(smallerHalfNumbers[0], greaterHalfNumbers[0]);
  }else{
    // Odd Target

    // EvenNumber + OddNumber = OddTarget
    CompareArrays(negativeNumbers[1], greaterTargetNumbers[0]);
    CompareArrays(smallerHalfNumbers[1], greaterHalfNumbers[0]);

    // OddNumber + EvenNumber = OddTarget
    CompareArrays(negativeNumbers[0], greaterTargetNumbers[1]);
    CompareArrays(smallerHalfNumbers[0], greaterHalfNumbers[1]);
  } 

  //Show found valid results  
  cout << "Quantity valid results : " << result.size() << endl; 

  return 0;
}
