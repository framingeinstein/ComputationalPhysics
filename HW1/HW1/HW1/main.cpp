//
//  main.cpp
//  HW1
//  Integrate function using, trapazoidal, 1/3 simpson and 4-point Gausian methods
//  Created by Jason Morgan on 9/3/14.
//  Copyright (c) 2014 Jason Morgan. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdlib>

const static double TOLLERANCE = 0.000001;

double integrand1(double x);
double dintegrand1(double x);
double integrand2(double t);

int trapazodialIterations(double error);
int trapazodialIterations(double a, double b, double error, double (*df)(double));
int simpsonsIterations(double error);

double trapazoid(double a, double b, double (*f)(double), int n);
double simpson(double a, double b, double (*f)(double), int n);


using namespace std;


int main(int argc, const char * argv[])
{

	double (*f)(double) = integrand1;
	double (*df)(double) = dintegrand1;
	
	
	// trapazoidal rule for intrgral 1
	int n = trapazodialIterations(TOLLERANCE) * 100;
	double b = 35000 * M_PI;
	cout << "trapazoidal rule for intrgral 1 n=" << n <<endl;
	cout << trapazodialIterations(TOLLERANCE) << endl;
	cout << trapazodialIterations(0, b, TOLLERANCE, df) << endl;
	cout << "target: 1.570796" << endl;
	cout << trapazoid(0, b, f, n) << endl << endl;
	
	// simpsons rule for intrgral 1
	n = simpsonsIterations(TOLLERANCE) * 10000;
	cout << "simpsons rule for intrgral 1 n=" << n << endl;
	cout << "target: 1.570796" << endl;
	cout << simpson(0, b, f, n) << endl << endl;

	
	f = integrand2;
	b = 70;
	// trapazoidal rule for intrgral 2
	n = trapazodialIterations(TOLLERANCE) * 40;
	cout << "trapazoidal rule for intrgral 2 n=" << n << endl;
	cout << "target: 0.403653" << endl;
	cout << trapazoid(0, b, f, n) << endl << endl;
	
	// simpsons rule for intrgral 2
	n = simpsonsIterations(TOLLERANCE) * 40;
	cout << "simpsons rule for intrgral 2 n=" << n << endl;
	cout << "target: 0.403653" << endl;
	cout << simpson(0, b, f, n) << endl << endl;
	
	return 0;
}


double integrand1(double x){
	if(x == 0){
		return 1;
	}
	return sin(x) / x;
}
double dintegrand1(double x){
	if(x == 0){
		return 0;
	}
	return (x * cos(x) - sin(x))/pow(x,2);
}


double integrand2(double t){
	return (t / (t + 1)) * exp(-1 * t);
}


double trapazoid(double a, double b, double (*f)(double), int n){
	double h = (b - a) / ( n - 1) ;
	
	double s =(f(a) + f(b)) ; // evaluation of the end points

	for(int i = 2; i < n; i++){
		s += 2 * f(a + (i-1)*h) ; // evaluation of the interior points
	}
	s *= h / 2 ;
	return s ;
}

double simpson(double a, double b, double (*f)(double), int n){
	double h = (b - a) / (n) ;
	
	double s = (f(a) + f(b));
	
	for(int i = 1; i <= (n - 1) ; i+=2){
		s += 4*f(a+i*h) ;
	}
	
	
	for(int i = 2; i <= (n - 2) ; i+=2){
		s += 2*f(a+i*h) ;
	}
	s *= h / 3 ;
	return s ;
}

int trapazodialIterations(double error){
	
	int n = (int)ceil(1/sqrt(error));
	if(n % 2 != 0) {
		return n + 1; // must be even
	}
	return n;
}

int trapazodialIterations(double a, double b, double error, double (*df)(double)){
	
	double dn = sqrt(((b - a) / (12 * error)) * (df(b) - df(a)));
	
	int n = (int)ceil(dn);
	if(n % 2 != 0) {
		return n + 1; // must be even
	}
	return n;
}

int simpsonsIterations(double error){
	int n = (int)ceil(1/sqrt(sqrt(error)));
	if(n % 2 == 0) {
		return n + 1; // must be odd
	}
	return n;
}
