#pragma once

#include <DirectXMath.h>

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
		vect2.x = (pow(vect.x,2) - pow(vect.y,2))*(1- pow(vect.z,2)/(pow(vect.x, 2) + pow(vect.y, 2)));
		vect2.y = 2*vect.x*vect.y*(1 - pow(vect.z, 2) / (pow(vect.x, 2) + pow(vect.y, 2)));
		vect2.z = -2*vect.z*pow(pow(vect.x,2)+pow(vect.y,2),1/2);
		vect.x = vect2.x + c.x;
		vect.y = vect2.y + c.y;
		vect.z = vect2.z + c.z;
	}
	return true;
}