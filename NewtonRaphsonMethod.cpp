/*Starting with the name of Almighty Allah, the most merciful, glorious!
This program is written to solve Algebraic and Transcendental
Equations by Bisection Method. This program requires 
C++11 or newer compiler.

Author: Afif Al Mamun, MD Jewel
Date: January 19, 2018.
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <cmath>

using namespace std;

typedef struct Node
{
	char sign;
	string constant;
	string function;
	int exponential;
} node;

vector<node> equationManipulator(string equation)
{
	vector<node> nodes;

	string temp;

	istringstream tream(equation);

	while (tream >> temp)
	{
		char sign = '+';
		string constant = "";
		string function = "";
		int exponential = 1;

		int i = 0;

		if (temp[i] == '-' || temp[i] == '+')
			sign = temp[i++];

		while ((temp[i] >= '0' && temp[i] <= '9') || temp[i] =='.')
			constant += temp[i++];

		if (temp[i] == 'e')
		{
			function += 'e';

			i = temp.length() - 2;
			int p = 0;
			int tempExp = 0;

			while (temp[i] != '^')
			{
				tempExp += (temp[i] - '0') * pow(10, p++);
				--i;
			}
			if (tempExp != 0)
				exponential = tempExp;
		}

		else
		{
			while (temp[i] != '^' && temp[i] != '\0')
				function += temp[i++];

			if (temp[i] != '\0')
				exponential = temp[++i] - '0';
		}
		node newNode;

		newNode.sign = sign;
		newNode.constant = constant;
		newNode.function = function;
		newNode.exponential = exponential;

		nodes.push_back(newNode);
	}

	return nodes;
}

double function(vector<node> eqs, double value)
{
	double res = 0.0;

	for (int i = 0; i < eqs.size(); i++)
	{
		double constant;
		double currentRes = 0;
		int exponent = eqs[i].exponential;

		if (eqs[i].constant != "")
			constant = stod(eqs[i].constant);
		else
			constant = 1;

		if (eqs[i].function != "")
		{
			if (eqs[i].function == "x")
			{
				currentRes = pow(value, exponent);
				currentRes *= constant;
			}
			else if (eqs[i].function == "e")
			{
				currentRes = value;
				currentRes *= exponent;
				currentRes = exp(currentRes);
				currentRes *= constant;
			}
			else if (eqs[i].function == "sinx" || eqs[i].function == "sin(x)")
			{
				currentRes = sin(value);
				currentRes = pow(currentRes, exponent);
				currentRes *= constant;
			}
			else if (eqs[i].function == "cosx" || eqs[i].function == "cos(x)")
			{
				currentRes = cos(value);
				currentRes = pow(currentRes, exponent);
				currentRes *= constant;
			}
			else if (eqs[i].function == "tanx" || eqs[i].function == "tan(x)")
			{
				currentRes = tan(value);
				currentRes = pow(currentRes, exponent);
				currentRes *= constant;
			}
		}
		else
			currentRes = constant;

		if (eqs[i].sign == '+')
			res += currentRes;
		else if (eqs[i].sign == '-')
			res -= currentRes;
	}

	return res;
}

/*Here is the algorithm of N-R method.
This function's parameters are the main function and its derivative as a vector and
the tolerance as well as a chosen value(picked) between the range*/

double NRmethod(vector<node> vc1, vector<node> vc2, double tolerance, double pick)
{
	double range1, range2;

	double value1 = (pick - (function(vc1, pick) / function(vc2, pick)));
	double value2 = (value1 - (function(vc1, value1) / function(vc2, value1)));

	while (true)
	{

		if (fabs(value2 - value1) < tolerance)
			break;

		else
		{
			value1 = value2;
			value2 = (value1 - (function(vc1, value1) / function(vc2, value1)));
		}
	}
	return value2;
}

int main()
{
	string equation;
	string derivative;
	double tol, range1, range2;

	cout << "\t\t\t\t-----#Newton Raphson Method#-----\n";
	cout << "\t\t[Supported Functions: x^n, e^nx, sin(nx), cos(nx), tan(nx)]\n";
	cout << "\t\t*KEEP A SPACE BEFORE EACH OPERATOR*\n";
	cout << "\t\t\n\n\t\t\t**EX: ax^m -nsin(x) +pe^q -c\n";

	cout << "\nInput Equation: ";
	getline(cin, equation);

	cout << "The equation's 1st derivative:  ";
	getline(cin, derivative);

	cout << "Input Tolerance: ";
	cin >> tol;

	cout << "Give two ranges: ";
	cin >> range1 >> range2;

	double pick; // a number in the range

	vector<node> vc1 = equationManipulator(equation);
	vector<node> vc2 = equationManipulator(derivative);

	while (function(vc1, range1) * function(vc1, range2) >= 0)
	{
		cout << "Wrong assumption! Input again: ";
		cin >> range1 >> range2;
	}

	cout << "Pick any number in the range: " << endl;
	cin >> pick;

	double root = NRmethod(vc1, vc2, tol, pick);

	cout << "\nA root between " << range1 << " & " << range2 << " is ";
	cout << setprecision(10) << root << ".\n";
}
