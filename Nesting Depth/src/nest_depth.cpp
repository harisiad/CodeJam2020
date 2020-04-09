/*
############ CodeJam 2020 ############
			Nesting Depth
Problem

tl;dr: Given a string of digits S, insert a minimum number of opening and closing parentheses into it such that the resulting string is balanced 
and each digit d is inside exactly d pairs of matching parentheses.

Let the nesting of two parentheses within a string be the substring that occurs strictly between them. 
An opening parenthesis and a closing parenthesis that is further to its right are said to match if their nesting is empty, 
or if every parenthesis in their nesting matches with another parenthesis in their nesting.
The nesting depth of a position p is the number of pairs of matching parentheses m such that p is included in the nesting of m.

For example, in the following strings, all digits match their nesting depth: 0((2)1), (((3))1(2)), ((((4)))), ((2))((2))(1). 
The first three strings have minimum length among those that have the same digits in the same order, 
but the last one does not since ((22)1) also has the digits 221 and is shorter.

Given a string of digits S, find another string S', comprised of parentheses and digits, such that:

	all parentheses in S' match some other parenthesis,
	removing any and all parentheses from S' results in S,
	each digit in S' is equal to its nesting depth, and
	S' is of minimum length.

Input

The first line of the input gives the number of test cases, T. T lines follow. Each line represents a test case and contains only the string S.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the string S' defined above.

Input		Output
4
0000		Case #1: 0000
101			Case #2: (1)0(1)
111000		Case #3: (111)000
1			Case #4: (1)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define pline() std::cout << std::endl

int openParenthesis(int count, std::string& str, int pos)
{
	std::string startToPar = str.substr(0, pos);
	std::string openParToEnd = (pos == 0) ? str.substr(0, str.size()) : str.substr(pos, str.size() - 1);

	for (int i = 0; i < count; ++i)
	{
		openParToEnd = '(' + openParToEnd;
	}

	if (pos == 0)
	{
		str = openParToEnd;
		return pos + count;
	}
	else
	{
		str = startToPar + openParToEnd;
		return str.find(openParToEnd);
	}
}

int closeParenthesis(int count, std::string& str, int pos, int finalCloseFlag)
{
	std::string startToClosePar = (finalCloseFlag) ? str.substr(0, (size_t) pos + 1) : str.substr(0, pos);
	std::string closeParToEnd = (pos == 0) ? str.substr(0, 1) : str.substr(pos, str.size() - 1);

	for (int i = 0; i < count; ++i)
	{
		startToClosePar += ')';
	}

	if (finalCloseFlag)
	{
		str = startToClosePar;
		return pos + count;
	}
	else
	{
		str = startToClosePar + closeParToEnd;
		return str.find(closeParToEnd);
	}
}

int main()
{
	std::cout << "Nesting Depth" << std::endl;
	
	int noTestCases = 0;
	std::vector<std::string> results;
	std::cout << "Number Test Cases: ";
	std::cin >> noTestCases;
	bool b_openParenthesis = false;

	for (int tCase = 0; tCase < noTestCases; ++tCase)
	{
		std::string input;
		std::cin >> input;
		int lastPos = 0, currDepth = 0;

		for (int c = 0; c < input.size(); ++c)
		{
			std::stringstream ss_curr;
			std::stringstream ss_prev;

			int i_curr = 0, i_prev = 0;

			ss_curr << input[c];
			ss_curr >> i_curr;
			if (c != 0)
			{
				ss_prev << input[(size_t) c - 1];
				ss_prev >> i_prev;
			}

			if (i_curr - i_prev < 0)
			{
				c = closeParenthesis(i_prev - i_curr, input, c, false);
				currDepth -= i_prev - i_curr;
				if (currDepth < 0) currDepth = 0;
			}
			else if (i_curr - i_prev > 0)
			{
				if (currDepth - i_curr < 0)
				{
					c = openParenthesis(i_curr - currDepth, input, c);
					currDepth = i_curr;
				}
			}

			if (c == input.size() - 1 &&
				currDepth != 0)
			{
				c = closeParenthesis(currDepth, input, c, true);
			}
		}

		results.push_back(input);
	}

	for (int tCase = 0; tCase < noTestCases; ++tCase)
	{
		std::cout << "# Case " << tCase << ": " << results[tCase];
		pline();
	}

}