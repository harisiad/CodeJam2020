/*
############ CodeJam 2020 ############
			  Vestiguim
Problem

Vestigium means "trace" in Latin. In this problem we work with Latin squares and matrix traces.

The trace of a square matrix is the sum of the values on the main diagonal (which runs from the upper left to the lower right).

An N-by-N square matrix is a Latin square if each cell contains one of N different values, and no value is repeated within a row or a column. 
In this problem, we will deal only with "natural Latin squares" in which the N values are the integers between 1 and N.

Given a matrix that contains only integers between 1 and N, we want to compute its trace and check whether it is a natural Latin square. 
To give some additional information, instead of simply telling us whether the matrix is a natural Latin square or not, 
please compute the number of rows and the number of columns that contain repeated values.

Input

The first line of the input gives the number of test cases, T. T test cases follow. 
Each starts with a line containing a single integer N: the size of the matrix to explore. 
Then, N lines follow. The i-th of these lines contains N integers Mi,1, Mi,2 ..., Mi,N. Mi,j is 
the integer in the i-th row and j-th column of the matrix.

Output

For each test case, output one line containing Case #x: k r c, where x is the test case number (starting from 1), k is the trace of the matrix, 
r is the number of rows of the matrix that contain repeated elements, and c is the number of columns of the matrix that contain repeated elements.

Sample

Input			Output

3
4
1 2 3 4			Case #1: 4 0 0
2 1 4 3
3 4 1 2
4 3 2 1
4
2 2 2 2			Case #2: 9 4 4
2 3 2 3
2 2 2 3
2 2 2 2
3
2 1 3			Case #3: 8 0 2
1 3 2
1 2 3
*/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>

bool checkForDuplicates(std::vector<int>& v, int elem)
{
	if (v.empty())
	{
		return false;
	}

	for (auto i : v)
	{
		if (i == elem)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::cout << "Vestigium" << std::endl;
	int noTestCases = 0;
	int aSize = 0;

	std::vector<std::vector<int>> rowList;
	std::vector<std::vector<int>> columnList;
	std::vector<int> traceList;

	std::cout << "Number of test cases: " << std::endl;
	std::cin >> noTestCases;
	for (int tCase = 0; tCase < noTestCases; tCase++)
	{
		std::cout << "Size of array: " << std::endl;
		std::cin >> aSize;

		// User input arrays
		std::vector<std::vector<int>> arr(aSize, std::vector<int>(aSize));
		char input[100];
		int i = 0;

		for (int i = 0; i < aSize; i++)
		{
			int num = 99;
			for (int j = 0; j < aSize; ++j)
			{
				std::cin >> input;
				std::stringstream(input) >> num;

				arr[i][j] = num;
			}
		}

		// Calculate k trace, r number of same elements on row, c number of same elements on column
		int trace = 0;
		std::unordered_map<int, bool> rowValid;
		std::vector<int> rows;
		std::unordered_map<int, bool> colValid;
		std::vector<int> columns;

		for (int i = 0; i < aSize; i++)
		{
			for (int j = 0; j < aSize; j++)
			{
				if (i == j)
				{
					trace += arr[i][j];
				}

				std::unordered_map<int, bool>::iterator r = rowValid.find(arr[i][j]);
				if (r == rowValid.end())
				{
					rowValid.insert(std::pair<int,bool>(arr[i][j], false));
				}
				else
				{
					if (!checkForDuplicates(rows, i) && !rowValid[arr[i][j]])
					{
						rows.push_back(i);
					}
					rowValid[arr[i][j]] = true;
				}

				std::unordered_map<int, bool>::iterator c = colValid.find(arr[j][i]);
				if (c == colValid.end())
				{
					colValid.insert(std::pair<int, bool>(arr[j][i], false));
				}
				else
				{
					if (!checkForDuplicates(columns, i) && !colValid[arr[j][i]])
					{
						columns.push_back(i);
					}
					colValid[arr[j][i]] = true;
				}
				//std::cout << arr[i][j] << " rows: " << rowValid[arr[i][j]];
			}
			std::cout << std::endl;
			rowValid.clear();
			colValid.clear();
		}
		
		rowList.push_back(rows);
		columnList.push_back(columns);
		traceList.push_back(trace);

		rows.clear();
		columns.clear();
		rowValid.clear();
		colValid.clear();
		arr.clear();
	}

	for (int i = 0; i < noTestCases; i++)
	{
		std::cout << "# Case " << i << ":" << traceList[i] << " " << rowList[i].size() << " " << columnList[i].size() << std::endl;
	}

	return 0;
}
