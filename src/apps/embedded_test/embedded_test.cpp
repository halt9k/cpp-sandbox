#include <sstream>

#include "hr_extended.h"
#include "sandbox_adapter.h"

#include <cstdio>
#include <iostream>
#include <string>


float lagrange4(float x,
				float x0, float y0,
				float x1, float y1,
				float x2, float y2,
				float x3, float y3)
	{
	float l0 = (x - x1) * (x - x2) * (x - x3) /
		((x0 - x1) * (x0 - x2) * (x0 - x3));

	float l1 = (x - x0) * (x - x2) * (x - x3) /
		((x1 - x0) * (x1 - x2) * (x1 - x3));

	float l2 = (x - x0) * (x - x1) * (x - x3) /
		((x2 - x0) * (x2 - x1) * (x2 - x3));

	float l3 = (x - x0) * (x - x1) * (x - x2) /
		((x3 - x0) * (x3 - x1) * (x3 - x2));

	return y0 * l0 + y1 * l1 + y2 * l2 + y3 * l3;
	}

void embedded_test()
	{
	for (float i = 0.1; i < 300; i += 10)
		{
		float y = lagrange4(
			i,
			0, 0,
			25, 120,
			68, 185,
			100, 245);

		cout << "x:  " << i << " y:   " << y << endl;
		}
	}


int main()
	{
	embedded_test();
	return 0;
	}