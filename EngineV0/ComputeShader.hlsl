static const uint edgeTable[256] =
{
    0x0, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
0x190, 0x99, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
0x230, 0x339, 0x33, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
0x3a0, 0x2a9, 0x1a3, 0xaa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
0x460, 0x569, 0x663, 0x76a, 0x66, 0x16f, 0x265, 0x36c,
0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff, 0x3f5, 0x2fc,
0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55, 0x15c,
0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
0xcc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
0x15c, 0x55, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
0x2fc, 0x3f5, 0xff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
0x36c, 0x265, 0x16f, 0x66, 0x76a, 0x663, 0x569, 0x460,
0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa, 0x1a3, 0x2a9, 0x3a0,
0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33, 0x339, 0x230,
0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99, 0x190,
0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0
};

cbuffer CBuff
{
    int triTable[256][16];
};


float convfunc(float3 vect)
{
    float3 c = vect;
    uint loops = 200;
    for (uint i = 0; i < loops; i++)
    {
        if (pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2) > 500)
        {
            return 2.0f - (1.0f / (float) loops);
        }

        float3 vect2;
        vect2.x = pow(vect.x, 3) - 3 * vect.x * (pow(vect.y, 2) + pow(vect.z, 2)) + c.x;
        vect2.y = -pow(vect.y, 3) + 3 * vect.y * pow(vect.x, 2) - vect.y * pow(vect.z, 2) + c.y;
        vect2.z = pow(vect.z, 3) - 3 * vect.z * pow(vect.x, 2) + vect.z * pow(vect.y, 2) + c.z;
        vect = vect2;
    }

    return 0.0f;
}


struct BufferStruct {
	float3 pos;
    float padding;
};

static const int THREAD_GROUP_SIZE_X = 8;
static const int THREAD_GROUP_SIZE_Y = 8;
static const int THREAD_GROUP_SIZE_Z = 8;

static const int GROUPS_Y = 9;
static const int GROUPS_X = 9;
static const int GROUPS_Z = 9;



RWStructuredBuffer<BufferStruct> OutBuff;

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, THREAD_GROUP_SIZE_Z)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex)
{
    
    float3 pos;
    float scale = 3.0 / (THREAD_GROUP_SIZE_X * GROUPS_X);
    uint cubeIndex = 0;  
    float3 initvert = float3(110.0, 110.0, 110.0);
    float3 vertlist[12] = { initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert };

    pos.x = (grpID.x * (THREAD_GROUP_SIZE_X) + grpTID.x) * scale;
    pos.y = (grpID.y * (THREAD_GROUP_SIZE_Y) + grpTID.y) * scale;
    pos.z = (grpID.z * (THREAD_GROUP_SIZE_Z) + grpTID.z) * scale;

    float3 v0 = pos + float3(0.0, 0.0, scale);

    [branch] if (convfunc(v0) < 1.0)
    {
        cubeIndex |= 1;
    }
    float3 v1 = pos + float3(scale, 0.0, scale);
    [branch] if (convfunc(v1) < 1.0)
    {
        cubeIndex |= 2;
    }
    float3 v2 = pos + float3(scale, 0.0, 0.0);
    [branch] if (convfunc(v2) < 1.0)
    {
        cubeIndex |= 4;
    }
    float3 v3 = pos;
   [branch] if (convfunc(v3) < 1.0)
    {
        cubeIndex |= 8;
    }
    float3 v4 = pos + float3(0.0, scale, scale);
   [branch] if (convfunc(v4) < 1.0)
    {
        cubeIndex |= 16;
    }
    float3 v5 = pos + float3(scale, scale, scale);
    [branch] if (convfunc(v5) < 1.0)
    {
        cubeIndex |= 32;
    }
    float3 v6 = pos + float3(scale, scale, 0.0);
   [branch] if (convfunc(v6) < 1.0)
    {
        cubeIndex |= 64;
    }
    float3 v7 = pos + float3(0.0, scale, 0.0);
    [branch] if (convfunc(v7) < 1.0)
    {
        cubeIndex |= 128;
    }

   [branch] if (edgeTable[cubeIndex] == 0 || 255)
    {
        return;
    }

    [branch] if (edgeTable[cubeIndex] & 1)
    {
        vertlist[0] = v0 + float3(scale * 0.5, 0.0, 0.0);
    }
    [branch] if (edgeTable[cubeIndex] & 2)
    {
        vertlist[1] = v2 + float3(0.0, 0.0, scale * 0.5);
    }  
   [branch] if (edgeTable[cubeIndex] & 4)
    {
        vertlist[2] = v3 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch] if (edgeTable[cubeIndex] & 8)
    {
        vertlist[3] = v3 + float3(0.0, 0.0, scale * 0.5);
    }
   [branch] if (edgeTable[cubeIndex] & 16)
    {
        vertlist[4] = v4 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch] if (edgeTable[cubeIndex] & 32)
    {
        vertlist[5] = v6 + float3(0.0, 0.0, scale * 0.5);
    }
    [branch] if (edgeTable[cubeIndex] & 64)
    {
        vertlist[6] = v7 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch] if (edgeTable[cubeIndex] & 128)
    {
        vertlist[7] = v7 + float3(0.0, 0.0, scale * 0.5);
    }
    [branch] if (edgeTable[cubeIndex] & 256)
    {
        vertlist[8] = v0 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch] if (edgeTable[cubeIndex] & 512)
    {
        vertlist[9] = v1 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch] if (edgeTable[cubeIndex] & 1024)
    {
        vertlist[10] = v2 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch] if (edgeTable[cubeIndex] & 2048)
    {
        vertlist[11] = v3 + float3(0.0, scale * 0.5, 0.0);
    }

    uint nverts = 0;
    uint idx = ((grpID.x + grpID.y * (GROUPS_X) + grpID.z * (GROUPS_X * GROUPS_Y)) * (THREAD_GROUP_SIZE_X * THREAD_GROUP_SIZE_Y * THREAD_GROUP_SIZE_Z) + grpTID.x + grpTID.y * (THREAD_GROUP_SIZE_X) + (THREAD_GROUP_SIZE_X * THREAD_GROUP_SIZE_Y) * grpTID.z) * 16;

    [unroll(16)] for (uint i = 0; triTable[cubeIndex][i] != -1; i += 3)
    {
        OutBuff[idx + nverts].pos = vertlist[triTable[cubeIndex - 1][i]];
        OutBuff[idx + nverts + 1].pos = vertlist[triTable[cubeIndex - 1][i + 1]];
        OutBuff[idx + nverts + 2].pos = vertlist[triTable[cubeIndex - 1][i + 2]];
        nverts += 3;
    }


}