#include "ConvergenceFuncs.h"

bool convn3(DirectX::XMFLOAT3 vect)
{
	DirectX::XMFLOAT3 c = vect;
	for (int i = 0; i < 50; i++)
	{
		if (pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2) > 50)
		{
			return false;
		}
		DirectX::XMFLOAT3 vect2;
		vect2.x = ((3 * pow(vect.z, 2) - pow(vect.x, 2) - pow(vect.y, 2))*vect.x*(pow(vect.x, 2) - 3 * pow(vect.y, 2))) / (pow(vect.x, 2) + pow(vect.y, 2));
		vect2.y = ((3 * pow(vect.z, 2) - pow(vect.x, 2) - pow(vect.y, 2))*vect.y*(3 * pow(vect.x, 2) - pow(vect.y, 2))) / (pow(vect.x, 2) + pow(vect.y, 2));
		vect2.z = vect.z*(pow(vect.z, 2) - 3 * pow(vect.x, 2) - 3 * pow(vect.y, 2));
		vect.x = vect2.x + c.x;
		vect.y = vect2.y + c.y;
		vect.z = vect2.z + c.z;
	}
	return true;
}

bool convn2(DirectX::XMFLOAT3 vect)
{
	DirectX::XMFLOAT3 c = vect;
	for (int i = 0; i < 50; i++)
	{
		if (pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2) > 50)
		{
			return false;
		}

		DirectX::XMFLOAT3 vect2;
		vect2.x = (pow(vect.x, 2) - pow(vect.y, 2))*(1 - pow(vect.z, 2) / (pow(vect.x, 2) + pow(vect.y, 2)));
		vect2.y = 2 * vect.x*vect.y*(1 - pow(vect.z, 2) / (pow(vect.x, 2) + pow(vect.y, 2)));
		vect2.z = -2 * vect.z*pow(pow(vect.x, 2) + pow(vect.y, 2), 1.0f / 2.0f);
		vect.x = vect2.x + c.x;
		vect.y = vect2.y + c.y;
		vect.z = vect2.z + c.z;
	}
	return true;
}

float convn4(float x, float y, float z)
{
	DirectX::XMFLOAT3 vect;
	vect.x = x;
	vect.y = y;
	vect.z = z;
	DirectX::XMFLOAT3 c = vect;
	int loops = 200;
	for (int i = 0; i < loops; i++)
	{
		if (pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2) > 500)
		{
			return 2.0f - (1.0f / (float)loops);
		}

		DirectX::XMFLOAT3 vect2;
		vect2.x = pow(vect.x, 3) - 3 * vect.x*(pow(vect.y, 2) + pow(vect.z, 2)) + c.x;
		vect2.y = -pow(vect.y, 3) + 3 * vect.y*pow(vect.x, 2) - vect.y*pow(vect.z, 2) + c.y;
		vect2.z = pow(vect.z, 3) - 3 * vect.z*pow(vect.x, 2) + vect.z*pow(vect.y, 2) + c.z;
		vect = vect2;
	}

	return 0.0f;
}