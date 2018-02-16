/*Program to solve Algebraic and Transcendental
Equations by Bisection Method. This program requires 
C++11 or newer compiler.

Author: Afif Al Mamun
Date: January 16, 2018.*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

typedef struct Node
{
	char sign;
	string constant;
	string function;
	int exponential;
} node;

/*This function will manipulate the inputted equation in
several parts and return them as a vector.*/

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

		while (temp[i] >= '0' && temp[i] <= '9')
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

/*This function will calculate the value of the equation in 
double number for a certain value.*/

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

/*This is the method where Bisection is applied. It requires the manipulated
equation as vector, tolerance, two ranges r1, r2 for which function(r1)*function(r2) < 0
and after several steps of calculation it will return the root as a double number.
It can calculate upto 10 decimal degits.*/

double bisectionMethod(vector<node> vc, double tolerance, double r1, double r2)
{
	double range1, range2;

	if(function(vc, r1) < 0.00)
	{
		range1 = r1;
		range2 = r2;
	}
	else
	{
		range1 = r2;
		range2 = r1;
	}

	double rn = (range1 + range2)/2.0000000000;

	while(true)
	{
		if(fabs((range1 - range2)/rn) < tolerance)
			break;

		if(function(vc, rn) < 0.00)
		{
			range1 = rn;
		}
		else
			range2 = rn;
		
		rn = (range1 + range2)/2.00000000000;
		
	}

	return rn;
}

int main()
{
	string equation;
	double tol, range1, range2;
	cout<<"-----Bisection Method-----\n";
	cout<<"[Supported Functions: x^n, e^nx, sin(nx), cos(nx), tan(nx)]\n";
	cout<<"*KEEP A SPACE BEFORE EACH OPERATOR*\n";
	cout<<"*FOR EX: ax^m -nsin(x) +pe^q -c\n";

	cout<<"Input Equation: ";
	getline(cin, equation);

	cout<<"Input Tolerance: ";
	cin>>tol;

	cout<<"Give two ranges: ";
	cin>>range1>>range2;

	
	vector<node> vc = equationManipulator(equation);

	while(function(vc, range1)*function(vc, range2) >= 0)
	{
		cout<<"Wrong assumption! Input again: ";
		cin>>range1>>range2;
	}

	double root = bisectionMethod(vc, tol, range1, range2);

	cout<<"\nA root between "<<range1<<" & "<<range2<<" is ";
	cout<<setprecision(10)<<root<<".\n";

}
