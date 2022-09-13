<h1 align="center">Jesús Alberto Getial Barragán</h1>

<div align="center">
  Electronic Engineer - FullStack Developer
</div>
<div align="center">
  <strong>Currently Msc System & Computer Engineering Scholarship Student</strong>
</div>
<div align="center">
  <sub>Click to visit my linkedIn profile: 
  <a href="https://www.linkedin.com/in/jesus-barragan-8b868096/">Jesús Barragan</a>  
</div>

## Table of Contents
- [Challenge Definition](#problem-definition)
- [Solution Explanation](#solution-explanation)
-- [Main Functions](#main-functions)
- [How to run](#how-to-run)
- [Results](#results)

## Challenge Definition
The task is to write a function that finds pairs of integers from a list that
sum to a given value. The function will take as input the list of numbers as
well as the target sum.
​
Sample output is shown below.
```
> app 1,9,5,0,20,-4,12,16,7 12
​
+ 12,0
+ 5,7
+ 16,-4
​
```
​
You can assume that all input values are integers. You can assume that there aren't
any repeat values in the list.
​

## Solution Explanation

With the aim to avoid high exponential computational complexity I propose a methodology to group the given array in several groups in order to reduce mandatory comparisons.

Given an array and a target, let's perform:

- First consideration: Classify groups by smaller than target half value and greater than target half value, given that the target can only be reached with the addition of one member of each group since it is not possible to reach the goal by adding members only from the first half or the second.
- Second consideration: Classify a group by greater than the target value, because, those numbers can only be operated with negative values to reach the target in a sum operation.
- Third consideration: Classify the last two groups considering if the target is an even or odd number. So, it's required to compute the following cases for each case: <br> **Even target**: `Even + Even = Even` or `Odd + Odd = Even`; <br>  **Odd target**: `Even + Odd = Odd` or `Odd + Even = Odd`

The following table exposes the grouping. With this grouping I reduce the number of computing operations:

<div align="center">
<table>
  <tr>
    <th>Negatives values</th>
    <th>Smaller target half value</th>
    <th>Greater target half value</th>
    <th>Greater target value</th>
  </tr>
  <tr>
    <td>Even Number</td>
    <td>Even Number</td>
    <td>Even Number</td>
    <td>Even Number</td>
  </tr>
  <tr>
    <td>Odd Number</td>
    <td>Odd Number</td>
    <td>Odd Number</td>
    <td>Odd Number</td>
  </tr>  
</table>
</div>

The proposed algorithm first classify the input array in the correspondent table groups and after that execute the functions CompareArrays and the nested function AddResult to deliver the final result.


### Main Functions

This function takes the values from a given first vector and computes the difference with the given target. The difference is searched in the given second vector, if it is found, AddResult function is executed.
```cpp
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
```
This function check if the found tuple result has already been saved. If not, it stores the new tuple in the final result array.

```cpp
void AddResult(int val1, int val2){
  vector<int> resultArray {val1, val2};  
  for (size_t i = 0; i < result.size(); i++)
  {
    if(result[i][0] == val1 || result[i][0] == val2){
        return;
    }
  }
  
  result.push_back(resultArray);
  cout << "Solution : " << val1 << " , " << val2 << endl;
}
```


## How to run

First, you need to clone the repository in your machine with git previously installed. Type in a console to clone
```
git clone 
```
Next, you need GNU C++ compiler to create an executable file and be able to run the proposed algorithm. I expose how to do it on Linux OS and Windows OS:

### linux system

- Open a console
- Type the following sentence
```
sudo apt install g++​
```
- In the already cloned repository with the file `main.cpp`, open a terminal and type:
```
g++ main.cpp -o app
```
- An executable file called `app` should be created (you can change the name to your liking)
- In the same terminal execute the file. The first argument of the sentence is ***the name of the executable***, which must be preceded by `./`, the second argument is ***the input array*** and the third argument is the ***target*** or desired sum.
```
./app 1,9,5,0,20,-4,12,16,7 12
```

### Windows system

- <a href="https://nuwen.net/mingw.html">Download MinGw</a>
- Complete the installation with all as default. As recommendation install in the following path: 

```
C:\
```
- Let's update the environment path in order to be able to run g++ from the console. Go to the search bar, and type:
```
Edit the system environment variables > Advanced > Environment Variables... > Double click on Path > Click on New > Add C:\MinGw\MinGW\bin > Close all with ok button.
```

- Go to the path where is the already cloned repository with the file `main.cpp`, open a terminal, and type:
```
g++ main.cpp -o app
```
- An executable file called `app` should be created (you can change the name to your liking)
- In the same terminal execute the file. The first argument of the sentence is the name of the executable, which must be preceded by `./`, the second argument is ***the input array*** and the third argument is the ***target*** or desired sum
```
./app 1,9,5,0,20,-4,12,16,7 12
```

## Results
The result of the execution, for the given example in the challenge is shown as follows:
```
Original vector : 1 9 5 0 20 -4 12 16 7
Solution : -4 , 16
Solution : 0 , 12
Solution : 5 , 7
Quantity valid results : 3
```