//
//  main.cpp
//  Project 1
//
//  Created by Jason Morgan on 10/27/14.
//  Copyright (c) 2014 Jason Morgan. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

const static double g = 9.82; //m/s
const static double tolerence = 0.05;

struct Condition {
	double x;
	double y;
	string type; //EQ,LTE,GTE,GT,LT
	string name;
	
};



struct Coordinate {
	double t;
	double x;
	double y;
	double vx;
	double vy;
};

bool checkConditions(vector<Condition> conditions, Coordinate& p);
bool checkCondition(Condition& condition, Coordinate& p);
Coordinate getNext(Coordinate& p, double dt);
void euler(Coordinate& initial, Coordinate& final, vector<Condition> conditions, double dt);


int main(int argc, const char * argv[]) {
	
	
	// Projectile Motion Without air resistance
	double minAngle, maxAngle, dTheta, dt, v0, vship;
	
	minAngle = 10;
	maxAngle = 80;
	
	v0 = 200;
	vship = 1.0289; //2 knots
	
	dt = .00009;
	dTheta = .03;
	
	double theta = minAngle;
	
	while (theta <= maxAngle) {
		
		cout << "-------------------------------" << endl;
		cout << "THETA: " << theta << endl;
		Coordinate initial, final;
		
		vector<Condition> conditions;
		
		//Does not hit the wall
		Condition wall;
		wall.x = 1852; // 1 nm
		wall.y = 50 + 60; // 50m above sealevel with 60m wall
		wall.type = "GTE";
		wall.name = "Hit the wall";
		
		//Impacts Armory
		Condition armory;
		armory.x = 1852 + 100 + 4; // distance to wall plus distance to armory plus distance to center of armory
		armory.y = 50 + 3.2; // height above sea level plus height of building
		armory.type = "LTE";
		armory.name = "Missed the Armory";
		
		conditions.push_back(wall);
		conditions.push_back(armory);
		
		initial.t = 0;
		initial.x = 0;
		initial.y = 0;
		initial.vx = v0 * cos(theta * M_PI / 180) + vship;
		initial.vy = v0 * sin(theta * M_PI / 180);
		
		final.t = 0;
		final.x = 1852 + 100 + 4;
		final.y = 0;
		
		euler(initial, final, conditions, dt);
		
		
		
		cout << "-------------------------------" << endl;
		theta += dTheta;
	}
	
    return 0;
}

bool checkConditions(vector<Condition> conditions, Coordinate& p){
	bool result = true;
	for (int i = 0; i< conditions.size(); i++) {
		bool r = checkCondition(conditions[i], p);
		if(!r){
			cout << conditions[i].name << "( X: " << p.x << " Y: " << p.y << ")" << endl;
		}
		result = result & r; // All conditions must pass
	}
	return result;
}

bool checkCondition(Condition& condition, Coordinate& p){
	
	if ( abs(p.x - condition.x) > tolerence) {
		return true;
	}
	
	if (condition.type == "EQ") {
		return p.y >= condition.y - tolerence && p.y <= condition.y + tolerence;
	} else if (condition.type == "LTE"){
		return p.y <= condition.y;
	} else if (condition.type == "GTE"){
		return p.y >= condition.y;
	} else if (condition.type == "GT"){
		return p.y > condition.y;
	} else if (condition.type == "LT"){
		return p.y < condition.y;
	}

	return true;
	
}

Coordinate getNext(Coordinate& p, double dt){
	Coordinate next;
	// Eulers Method
	next.t = p.t + dt;
	next.x = p.x + p.vx * dt;
	next.vx = p.vx;
	next.y = p.y + p.vy * dt;
	next.vy = p.vy - g * dt;
	
	return next;
}


void euler(Coordinate& initial, Coordinate& final, vector<Condition> conditions, double dt){

	Coordinate previous;
	bool check = true;
	
	while (initial.y >= 0) {
		check = checkConditions(conditions, initial);
		if(! check){
			check = false;
			cout << "Conditions Failed" << endl;
			break;
		} //else if(check && abs(initial.x - final.x) < 4){
			// HIT!!
			//break;
		//}
		previous = initial;
		initial = getNext(previous, dt);
	}
	
	if(check && abs(initial.x - final.x) < 4){ //went long and is within 4m of center of armory
		cout << "Impact on armory : " << "( X: " << initial.x << " Y: " << initial.y << ")" << endl;
	} else if (initial.x < final.x - tolerence) {
		cout << "SHORT : " << "( X: " << initial.x << " Y: " << initial.y << ")" << endl;
	} else {
		cout << "LONG : " << "( X: " << initial.x << " Y: " << initial.y << ")" << endl;
	}
	
}

