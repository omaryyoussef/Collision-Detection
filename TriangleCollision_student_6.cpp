//StudentName: Omar Youssef
//Faculty : Faculty of Medicine
//Discipline : Biomedical Engineering M.Sc.
//Student No. : 3571222



#include <iostream>

#include <string>
#include <fstream>
#include <vector>
#include "VectorStructs.h"
#include <stdlib.h>

using namespace std;




bool lineCrossing3D(Vector3D p1, Vector3D v1, Vector3D p2, Vector3D v2)
{
	// line A = p1 + a1 * v1 ; line B = p2 + a2 * v2;
	// TODO: check if the two line segments A and B cross each other.
	Vector3D v1xv2 = v1.crossproduct(v2);
	Vector3D p1p2 = p2 - p1;
	Vector3D p1p2xv1 = v1.crossproduct(p1p2);
	//    t = (q − p) × s / (r × s)
	double a1 = v1xv2.norm();
	if (a1 > 0 || a1 < 0) {
		a1 = (p1p2.crossproduct(v2).norm()) / (a1);
	}
	//    u = (q − p) × r / (r × s)
	double a2 = v1xv2.norm();
	if (a2 > 0 || a2 < 0) {
		a2 = (p1p2.crossproduct(v1).norm()) / (a2);
	}

	if (v1xv2.norm() == 0 && p1p2xv1.norm() == 0) {
		double t0, t1;
		t0 = (p1p2 * v1) * (1 / (v1 * v1));
		t1 = t0 + (v2 * v1) * (1 / (v1 * v1));
		if ((t0 < 0 && t1 > 0))
			return true;
		else if (t1 < 0 && t0 > 0) // lines are collinear and overlapping
			return true;
		else// lines are collinear and disjoint
			return false;

	}
	else if (v1xv2.norm() != 0) {
		if (a1 > 0 && a1 < 1)
			if (a2 > 0 && a2 < 1)
				return true;
			else return false;
		else
			return false;
	}
	else
		return false;
}


struct Triangle3D
{
	Vector3D a;
	Vector3D b;
	Vector3D c;

	Triangle3D(Vector3D x1, Vector3D x2, Vector3D x3)
	{
		a = x1;
		b = x2;
		c = x3;
	}

	bool pointIsInside(Vector3D p)
	{
		// TODO: Please insert  'Vertex-In-Triangle-Test' algorithm here
		// Vertex-In-Test is the barycentric interpolation
		Vector3D v0 = this->c - this->a;
		Vector3D v1 = this->b - this->a;
		Vector3D v2 = p - this->a;

		// Compute dot products
		double dot00 = v0 * v0;
		double dot01 = v0 * v1;
		double dot02 = v0 * v2;
		double dot11 = v1 * v1;
		double dot12 = v1 * v2;

		// Compute barycentric coordinates
		double Denom = 1 / (dot00 * dot11 - dot01 * dot01);
		double 	u = (dot11 * dot02 - dot01 * dot12) * Denom;
		double v = (dot00 * dot12 - dot01 * dot02) * Denom;

		// Check if point is in triangle
		// this is done only when the weights sum up to '1'
		return (u >= 0) && (v >= 0) && (u + v < 1);
	}

	bool collide2D(Triangle3D t)
	{
		// TODO: Please check for Triangle collisions which are in the same plane here

		if (pointIsInside(t.a) == 1 || pointIsInside(t.b) == 1 || pointIsInside(t.c) == 1)   // First, check if any point is inside the other triangle
			return true;
		else if (lineCrossing3D(t.a, t.b, a, b) == 1)
			return true;
		else if (lineCrossing3D(t.a, t.b, a, c) == 1)
			return true;
		else if (lineCrossing3D(t.a, t.b, b, c) == 1)
			return true;
		else if (lineCrossing3D(t.a, t.c, a, b) == 1)
			return true;
		else if (lineCrossing3D(t.a, t.c, a, c) == 1)
			return true;
		else if (lineCrossing3D(t.a, t.c, b, c) == 1)
			return true;
		else if (lineCrossing3D(t.b, t.c, a, b) == 1)
			return true;
		else if (lineCrossing3D(t.b, t.c, a, c) == 1)
			return true;
		else if (lineCrossing3D(t.b, t.c, b, c) == 1)
			return true;
		else
			return false;

	}


	bool collide(Triangle3D t)
	{
		//TODO: Please check for 3D-3D triangle collisions here.
		//
		// Implement the cases: - same triangle planes
		//                      - parallel triangle planes
		//                      - intersecting triangle planes
		enum collisionCase { same, parallel, intersecting, noCollision };
		collisionCase CC = noCollision;

		Vector3D v1;
		Vector3D v2;
		Vector3D normalizedv1;
		Vector3D normalizedv2;
		Vector3D triangleNormal1;

		double d1 = 0;
		v1 = this->b - this->a;
		v2 = this->c - this->a;
		triangleNormal1 = v1.crossproduct(v2);  // N1
		d1 = -1 * (triangleNormal1 * this->a);

		Vector3D v1_T;
		Vector3D v2_T;
		Vector3D normalizedv1_T;
		Vector3D normalizedv2_T;
		Vector3D triangleNormal2;

		double d2 = 0;

		v1_T = t.b - t.a;
		v2_T = t.c - t.a;
		triangleNormal2 = v1_T.crossproduct(v2_T); // N2
		d2 = -1 * (triangleNormal2 * t.a);

		// test all vertices againsts triangle planes
		// COllisionCase for d_v2i = N1*v2i + d1; e.g. triangle t againts plane of triangle this->
		double signt1 = 0;
		double signt2 = 0;
		double signt3 = 0;
		double signt = 0;
		signt1 = triangleNormal1 * t.a + d1;
		signt2 = triangleNormal1 * t.b + d1;
		signt3 = triangleNormal1 * t.c + d1;
		signt = signt1 * signt2 * signt3;
		// COllisionCase for d_v1i = N2*v1i + d2;
		double signT1 = 0;
		double signT2 = 0;
		double signT3 = 0;
		double signT = 0;
		signT1 = triangleNormal2 * this->a + d2;
		signT2 = triangleNormal2 * this->b + d2;
		signT3 = triangleNormal2 * this->c + d2;
		signT = signT1 * signT2 * signT3;

		if (signt1 != 0 && signt2 != 0 && signt3 != 0)  // check if signs are not equal to zero
		{
			if (signt1 < 0 && signt2 < 0 && signt3 < 0) // check if signs have same sign eg + or -
			{
				CC = parallel;
			}
			else if (signt1 > 0 && signt2 > 0 && signt3 > 0) // check if signs have same sign eg + or -
			{
				CC = parallel;
			}
		}
		else if (signt1 == 0 && signt2 == 0 && signt3 == 0) // check if signs are equal to zero
		{
			if (signT1 == 0 && signT2 == 0 && signT3 == 0)
			{
				CC = same;
			}
		}

		if (signt1 < 0 && signt2 > 0)//  this here means that neither all signs are equal nor are they zero, thus intersection happend at a line
		{
			if (signt1 * signt1 == signT1 * signT1)
				CC = intersecting;
		}
		else if (signt1 < 0 && signt3 > 0)//  this here means that neither all signs are equal nor are they zero, thus intersection happend at a line
		{
			if (signt1 * signt1 == signT3 * signT3)
				CC = intersecting;
		}
		else if (signt3 < 0 && signt2 > 0)//  this here means that neither all signs are equal nor are they zero, thus intersection happend at a line
		{
			if (signt3 * signt3 == signT2 * signT2)
				CC = intersecting;
		}

		switch (CC)
		{
		case same:
			return this->collide2D(t);
			break;
		case parallel:
			return false;
			break;
		case intersecting:
			return this->collide2D(t);
			break;
		case noCollision:
			std::cout << "error calculating triangle normals" << endl;
			return false;
			break;
		}
	}
};

int main(int argc, char* argv[])
{
	{
		Vector3D a(1, 1, 1);
		Vector3D b(1, 1, 4);
		Vector3D c(1, 2, 2);
		Triangle3D t(a, b, c);

		Vector3D A(1, 1, 1);
		Vector3D B(1, 1, 5);
		Vector3D C(1, 2, 3);
		Triangle3D T(A, B, C);
		std::cout << "3D-test 1:\n";
		std::cout << t.collide(T) << "\n"; // triangles on same plane and have a common vertex
	}

	{
		Vector3D a(1, 1, 1);
		Vector3D b(1, 1, 4);
		Vector3D c(1, 2, 2);
		Triangle3D t(a, b, c);

		Vector3D A(2, 1, 1);
		Vector3D B(2, 1, 4);
		Vector3D C(2, 2, 2);
		Triangle3D T(A, B, C);
		std::cout << "3D-test 1b:\n";
		std::cout << t.collide(T) << "\n"; // parallel
	}

	{
		Vector3D a(1, 1, 1);
		Vector3D b(1, 1, 5);
		Vector3D c(1, 3, 4);
		Triangle3D t(a, b, c);

		Vector3D A(0, 2, 1);
		Vector3D B(0, 2, 5);
		Vector3D C(2, 2, 4);
		Triangle3D T(A, B, C);
		std::cout << "3D-test 2:\n";
		std::cout << t.collide(T) << "\n"; // 90 degree planes and intersecting at a line segment
	}
	{
		Vector3D a(1, 1, 1);
		Vector3D b(1, 1, 5);
		Vector3D c(1, 3, 4);
		Triangle3D t(a, b, c);

		Vector3D A(0, 2, 6);
		Vector3D B(0, 2, 8);
		Vector3D C(2, 2, 7);
		Triangle3D T(A, B, C);
		std::cout << "3D-test 3:\n";
		std::cout << t.collide(T) << "\n";// 90 degree planes yet NOT intersecting at any point or line
	}
	return 0;
}
