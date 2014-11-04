//
//  main.cpp
//  eigen-wrapper
//
//  Created by Jason Morgan on 9/20/13.
//  Copyright (c) 2013 Jason Morgan. All rights reserved.
//

#include <iostream>
#include "Eigen/Dense"


using namespace std;
using namespace Eigen;
int main()
{
	
	MatrixXd A(5,5);

	VectorXd b(5);
	A << -2,-3,-4,-1,1,  1,1,3,4,1,  2,3,4,5,1, -4,-3,-2,-1,1, 4,-3,-2,-1,5;
	b << 2, -1, 3, 4, 1;
	
	VectorXd x(5);

	cout << "Solving the system Ax = b for x" << endl;
	cout << "with matrix A:\n" << A << endl;
	cout << "and vector b:\n" << b << endl << endl;
	cout << "gives :" << endl;
	
	ColPivHouseholderQR<MatrixXd> qr;
	qr.compute(A);
	cout << qr.solve(b) << endl;
	
}