//
//  main.cpp
//  HW2
//
//  Created by Jason Morgan on 10/9/14.
//  Copyright (c) 2014 Jason Morgan. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const static int maxitrs = 2e4;
const static int maxitrsnewton = 1e4;
const static double tolerance = 1e-6;
const static double epsilon = 1e-13;

typedef struct {
	double root;
	bool found;
	int itr = 0;
	string message;
} result;

//metods
result bs(double (*f)(double), double a, double b);
result newton(double (*f)(double), double (*df)(double), double guess);
result bs(double (*f)(double), double a, double b, result &res);
result newton(double (*f)(double), double (*df)(double), double guess, result &res);
result newton(double (*f)(double), double guess, result &res);

//test functions
double fsin(double x);
double dfsin(double x);

double fpolynomial(double x);
double dfpolynomial(double x);

// functions for problem 3
double f3a(double x);
double df3a(double x);

double f3b(double x);
double df3b(double x);

double f3c(double x);
double df3c(double x);

double f3d(double x);
double df3d(double x);


int main(int argc, const char * argv[]) {
	result result;
	
	
	
	
	
	cout << "Problem 1. find roots of function using bisectional method." << endl << endl;
	
	cout << "Using sin(x) as function." << endl;
	
	
	cout << "Range with multiple roots" << endl;
	result = bs(fsin, 2, 13); // multiple roots...
	cout << M_PI << " " << 4 * M_PI << endl;
	cout << "Target Root: " << M_PI << endl;
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	int itr = 1;
	cout << "Range with no roots" << endl;
	result = bs(fsin, 2, 3); // no roots...
	cout << "Target Root: " << NAN << endl;
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	
	cout << "Using 3*x^3 - 5 * x^2 + x -1 as function." << endl;

	itr = 1;
	result = bs(fpolynomial, 1, 7);
	cout << "Target Root: 1.588911" << endl;
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	
	cout << "Problem 2. find roots of function using newtons method." << endl << endl;

	itr = 1;
	cout << "Sin(x) with Guess 3" << endl;
	result = newton(fsin, dfsin, 3); // multiple roots...
	cout << M_PI << " " << 4 * M_PI << endl;
	cout << "Target Root: " << M_PI << endl;
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "Sin(x) with Guess 6" << endl;
	result = newton(fsin, dfsin, 6); // multiple roots...
	cout << M_PI << " " << 4 * M_PI << endl;
	cout << "Target Root: " << 2 * M_PI << endl;
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;

	
	itr = 1;
	cout << "5 * x^2 + x -1 with Guess 1" << endl;
	result = newton(fpolynomial, dfpolynomial, 0); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "5 * x^2 + x -1 with Guess 2" << endl;
	result = newton(fpolynomial, dfpolynomial, 2); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "5 * x^2 + x -1 with Guess .5" << endl;
	result = newton(fpolynomial, dfpolynomial, .5); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	
	cout << "3. Apply the programs developed above to find a single root for:" << endl;
	cout << "	a) e^x ln x - cos(x^2) = 0" << endl;
	
	itr = 1;
	cout << "Using bisection method:" << endl;
	result = bs(f3a, 1, 4); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "using Newtons method:" << endl;
	result = newton(f3a, df3a, 1.5); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;

	cout << "	b) ln(x^2 + 2) cos x + sin x = 0" << endl;

	itr = 1;
	cout << "Using bisection method:" << endl;
	result = bs(f3b, 0, 4); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "using Newtons method:" << endl;
	result = newton(f3b, df3b, 2); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	cout << "	c) e^x - sin(PI * x /3) = 0" << endl;
	
	itr = 1;
	cout << "Using bisection method:" << endl;
	result = bs(f3c, -5, 2); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "using Newtons method:" << endl;
	result = newton(f3c, df3c, -3); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;

	cout << "	d) x^2 - 6x + 9 = 0" << endl;
	
	itr = 1;
	cout << "Using bisection method:" << endl;
	result = bs(f3d, 2, 5); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
	itr = 1;
	cout << "using Newtons method:" << endl;
	result = newton(f3d, df3d, 0); // multiple roots...
	cout << "Result     : " << result.root << endl; // should output ~ PI
	cout << result.itr << endl << endl;
	
}

double fsin(double x){
	//roots n*pi
	return sin(x);
}
double dfsin(double x){
	//roots n*pi
	return cos(x);
}

double fpolynomial(double x){
	return 3 * pow(x,3) - 5 * pow(x, 2) + x - 1;
}
double dfpolynomial(double x){
	return 2 * pow(x,2) - 10 * x + 1;
}

double f3a(double x){
	return pow(M_E, x) * log(x) - cos(pow(x, 2));
}
double df3a(double x){
	return (pow(M_E, x) * ( 1 + x * log( x ) ) ) / x + 2 * x * sin(pow(x,2));
}

double f3b(double x){
	return log(pow(x,2) + 2) * cos(x) + sin(x);
}
double df3b(double x){
	return cos(x)+( 2 * x * cos(x) )/(2+pow(x,2))-log(2+pow(x,2)) * sin(x);
}

double f3c(double x){
	return pow(M_E,x) - sin(M_PI * x / 3);
}
double df3c(double x){
	return pow(M_E, x)- M_PI * cos(M_PI * x / 3) / 3;
}

double f3d(double x){
	return pow(x, 2) - 6 * x + 9;
}
double df3d(double x){
	return 2 * x - 6;
}
/*
	Bi-Sectional root finding method
 */
result bs(double (*f)(double), double a, double b){
	result res;
	return bs(f, a, b, res);
}

result bs(double (*f)(double), double a, double b, result &res){
	res.itr++;
	if (res.itr > maxitrs ){
		res.found = false;
		res.message = "MAX ITERATIONS REACHED";
		res.root = NAN;
		return res;
	}
	
	double mid = a + (b - a) / 2;
	double fa = f(a);
	double fb = f(b);
	double fmid = f(mid);
	
	if (fa == 0) {
		res.root = a;
		res.found = true;
		return res;
	}
	
	if (fb == 0) {
		res.root = b;
		res.found = true;
		return res;
	}
	
	if (fmid == 0) {
		res.root = mid;
		res.found = true;
		return res;
	}
	
	
	if(fa * fmid < 0){ // there is a cross over
		if ((mid - a)/2 <= tolerance){
			res.root = a + (mid - a) / 2;
			res.found = true;
			return res;
		
		}
		return bs(f, a, mid, res);
	}
	if(fb * fmid < 0){ // there is a cross over
		if ((b - mid)/2 <= tolerance){
			res.root = mid + (b - mid) / 2;
			res.found = true;
			return res;
		}
		return bs(f, mid, b, res);
	}
	
	/*
	 If both are positive or negative thenthere are 2n roots between them n=0,1,2,3,...
	 */
	
	bs(f, a, mid, res);
	
	if (res.found){
		return res;
	}
	
	bs(f, mid, b, res);
	
	return res;
}

result newton(double (*f)(double), double (*df)(double), double guess){
	result res;
	return newton(f, guess, res);
}

result newton(double (*f)(double), double (*df)(double), double guess, result &res){
	res.itr++;
	if(res.itr >= maxitrsnewton){
		//cout << "MAX ITTERATIONS" << endl;
		res.found = false;
		res.message = "MAX ITTERATIONS REACHED";
		res.root = NAN;
		return res;
	}
	
	double fguess = f(guess);
	double dfguess = df(guess);
	
	if (abs(dfguess) < epsilon) {
		//cout << "DENOMINATOR TOO SMALL" << endl;
		res.found = false;
		res.message = "DENOMINATOR TOO SMALL";
		res.root = NAN;
		return res;
	}
	
	double better = guess - fguess / dfguess;
	
	if(abs(better - guess)/abs(better) < tolerance){
		res.found = true;
		res.root = better;
		return res;
	}
	
	return newton(f, df, better, res);
}


result newton(double (*f)(double), double guess, result &res){
	res.itr++;
	double h = 1e-4;
	if(res.itr >= maxitrsnewton){
		//cout << "MAX ITTERATIONS" << endl;
		res.found = false;
		res.message = "MAX ITTERATIONS REACHED";
		res.root = NAN;
		return res;
	}
	
	double fguess = f(guess);
	double dfguess = (f(guess + h) - f(guess)) / h;
	
	if (abs(dfguess) < epsilon) {
		//cout << "DENOMINATOR TOO SMALL" << endl;
		res.found = false;
		res.message = "DENOMINATOR TOO SMALL";
		res.root = NAN;
		return res;
	}
	
	double better = guess - fguess / dfguess;
	
	if(abs(better - guess)/abs(better) < tolerance){
		res.found = true;
		res.root = better;
		return res;
	}
	
	return newton(f, better, res);
}

