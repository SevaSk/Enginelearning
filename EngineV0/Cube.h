#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>

class Cube
{
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		constexpr float side = 1.0f / 2.0f;
		std::vector<V> vertices(8);
		vertices[0].pos ={ -side, -side, -side }; // 0
		vertices[1].pos ={ side, -side, -side }; // 1
		vertices[2].pos ={ -side, side, -side }; // 2
		vertices[3].pos ={ side, side, -side }; // 3
		vertices[4].pos ={ -side, -side, side }; // 4
		vertices[5].pos ={ side, -side, side }; // 5
		vertices[6].pos ={ -side, side, side }; // 6
		vertices[7].pos ={side, side, side}; // 7

		return{
			std::move(vertices),{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			}
		};

	}

	template<class V>
	static IndexedTriangleList<V> MakeSkinned()
	{
		constexpr float side = 1.0f / 2.0f;
		std::vector<V> vertices(24);
		
		vertices[0].pos = { -side, -side, -side }; // 0
		vertices[0].tex = { 0.0f,0.0f };
		vertices[1].pos = { side, -side, -side }; // 1
		vertices[1].tex = { 1.0f,0.0f };
		vertices[2].pos = { -side, side, -side }; // 2
		vertices[2].tex = { 0.0f,1.0f };
		vertices[3].pos = { side, side, -side }; // 3
		vertices[3].tex = { 1.0f,1.0f }; 
		
		vertices[4].pos = { -side, -side, -side }; //4,0
		vertices[4].tex = { 0.0f,0.0f };
		vertices[5].pos = { -side, -side, side }; // 5
		vertices[5].tex = { 1.0f,0.0f };
		vertices[6].pos = { side, -side, side }; // 6
		vertices[6].tex = { 1.0f,1.0f };
		vertices[7].pos = { side, -side, -side }; // 7,1
		vertices[7].tex = { 0.0f,1.0f }; 

		vertices[8].pos = { -side, side, -side }; // 8, 2 
		vertices[8].tex = { 0.0f,0.0f };
		vertices[9].pos = { -side, side, side }; // 9
		vertices[9].tex = { 1.0f,0.0f };
		vertices[10].pos = { side, side, side }; // 10
		vertices[10].tex = { 1.0f,1.0f };
		vertices[11].pos = { side, side, -side }; // 11,3
		vertices[11].tex = { 0.0f,1.0f };

		vertices[12].pos = { side, -side, -side }; // 12, 7, 1
		vertices[12].tex = { 0.0f,0.0f };
		vertices[13].pos = { side, -side, side }; // 13, 6
		vertices[13].tex = { 1.0f,0.0f };
		vertices[14].pos = { side, side, -side }; // 14,11,3
		vertices[14].tex = { 0.0f,1.0f };
		vertices[15].pos = { side, side, side }; // 15,10 
		vertices[15].tex = { 1.0f,1.0f };

		vertices[16].pos = { -side, -side, -side }; // 0,4,16
		vertices[16].tex = { 0.0f,0.0f };
		vertices[17].pos = { -side, -side, side }; // 17, 5
		vertices[17].tex = { 1.0f,0.0f };
		vertices[18].pos = { -side, side, -side }; // 18,8,2
		vertices[18].tex = { 0.0f,1.0f };
		vertices[19].pos = { -side, side, side }; // 19, 9
		vertices[19].tex = { 1.0f,1.0f };

		vertices[20].pos = { -side, -side, side }; // 20, 17, 5
		vertices[20].tex = { 0.0f,0.0f };
		vertices[21].pos = { side, -side, side }; // 21,13,6
		vertices[21].tex = { 1.0f,0.0f };
		vertices[22].pos = { -side, side, side }; // 22 ,19, 9
		vertices[22].tex = { 0.0f,1.0f };
		vertices[23].pos = { side, side, side }; // 23,15,10
		vertices[23].tex = { 1.0f,1.0f };

		return{
	std::move(vertices),{
		0,2,1,  1,2,3,
		4,7,5,  5,7,6,
		8,9,11, 9,10,11,
		12,14,13, 13,14,15,
		16,17,18, 17,19,18,
		20,21,22, 21,23,22

	}
		};	
	}

	template<class V>
	static IndexedTriangleList<V> MakeVoxel()
	{
		constexpr float side = 1.0f / 2.0f;
		std::vector<V> vertices(24);

		vertices[0].pos = { -side, -side, -side }; // 0
		vertices[0].n = { 0.0f,0.0f,-1.0f };
		vertices[1].pos = { side, -side, -side }; // 1
		vertices[1].n = { 0.0f,0.0f,-1.0f };
		vertices[2].pos = { -side, side, -side }; // 2
		vertices[2].n = { 0.0f,0.0f,-1.0f };
		vertices[3].pos = { side, side, -side }; // 3
		vertices[3].n = { 0.0f,0.0f,-1.0f };

		vertices[4].pos = { -side, -side, -side }; //4,0
		vertices[4].n = { 0.0f,-1.0f,0.0f };
		vertices[5].pos = { -side, -side, side }; // 5
		vertices[5].n = { 0.0f,-1.0f,0.0f };
		vertices[6].pos = { side, -side, side }; // 6
		vertices[6].n = { 0.0f,-1.0f,0.0f };
		vertices[7].pos = { side, -side, -side }; // 7,1
		vertices[7].n = { 0.0f,-1.0f,0.0f };

		vertices[8].pos = { -side, side, -side }; // 8, 2 
		vertices[8].n = { 0.0f,1.0f,0.0f };
		vertices[9].pos = { -side, side, side }; // 9
		vertices[9].n = { 0.0f,1.0f,0.0f };
		vertices[10].pos = { side, side, side }; // 10
		vertices[10].n = { 0.0f,1.0f,0.0f };
		vertices[11].pos = { side, side, -side }; // 11,3
		vertices[11].n = { 0.0f,1.0f,0.0f };

		vertices[12].pos = { side, -side, -side }; // 12, 7, 1
		vertices[12].n = { 1.0f,0.0f,0.0f };
		vertices[13].pos = { side, -side, side }; // 13, 6
		vertices[13].n = { 1.0f,0.0f,0.0f };
		vertices[14].pos = { side, side, -side }; // 14,11,3
		vertices[14].n = { 1.0f,0.0f,0.0f };
		vertices[15].pos = { side, side, side }; // 15,10 
		vertices[15].n = { 1.0f,0.0f,0.0f };

		vertices[16].pos = { -side, -side, -side }; // 0,4,16
		vertices[16].n = { -1.0f,0.0f,0.0f };
		vertices[17].pos = { -side, -side, side }; // 17, 5
		vertices[17].n = { -1.0f,0.0f,0.0f };
		vertices[18].pos = { -side, side, -side }; // 18,8,2
		vertices[18].n = { -1.0f,0.0f,0.0f };
		vertices[19].pos = { -side, side, side }; // 19, 9
		vertices[19].n = { -1.0f,0.0f,0.0f };

		vertices[20].pos = { -side, -side, side }; // 20, 17, 5
		vertices[20].n = { 0.0f,0.0f,1.0f };
		vertices[21].pos = { side, -side, side }; // 21,13,6
		vertices[21].n = { 0.0f,0.0f,1.0f };
		vertices[22].pos = { -side, side, side }; // 22 ,19, 9
		vertices[22].n = { 0.0f,0.0f,1.0f };
		vertices[23].pos = { side, side, side }; // 23,15,10
		vertices[23].n = { 0.0f,0.0f,1.0f };

		return{
	std::move(vertices),{
		0,2,1,  1,2,3,
		4,7,5,  5,7,6,
		8,9,11, 9,10,11,
		12,14,13, 13,14,15,
		16,17,18, 17,19,18,
		20,21,22, 21,23,22
		}
		};
	}
};

