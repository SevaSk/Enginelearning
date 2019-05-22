#include "Mandlebulb.h"

using namespace std;
bool Mandlebulb::conv(DirectX::XMFLOAT3 vect)
{
	DirectX::XMFLOAT3 c = vect;
	for (int i = 0; i < 50; i++)
	{
		DirectX::XMFLOAT3 vect2;
		vect2.x = ((3 * pow(vect.z, 2) - pow(vect.x, 2) - pow(vect.y, 2))*vect.x*(pow(vect.x, 2) - 3 * pow(vect.y, 2))) / (pow(vect.x, 2) + pow(vect.y, 2));
		vect2.y = ((3 * pow(vect.z, 2) - pow(vect.x, 2) - pow(vect.y, 2))*vect.y*(3 * pow(vect.x, 2) - pow(vect.y, 2))) / (pow(vect.x, 2) + pow(vect.y, 2));
		vect2.z = vect.z*(pow(vect.z, 2) - 3 * pow(vect.x, 2) - 3 * pow(vect.y, 2));
		vect.x = vect2.x + c.x;
		vect.y = vect2.y + c.y;
		vect.z = vect2.z + c.z;
	}
	return pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2) < 50;
}
