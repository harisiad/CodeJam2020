/* CodeJam2020.cpp : Defines the entry point for the application.

############ CodeJam 2020 ############
		Vestiguim Excercise
*/


#include "CodeJam2020.h"

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
