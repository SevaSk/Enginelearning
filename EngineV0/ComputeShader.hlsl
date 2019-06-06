cbuffer CBuff : register(b0)
{
    int4 triTable[1024];
};

cbuffer CBuff2 : register(b1)
{
    int4 edgeTable[64];
}


float convfunc(float3 vect)
{
    const float3 c = vect;
    const uint loops = 200;
    [loop]
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
    float3 normal;
    float3 color;
};

static const uint THREAD_GROUP_SIZE_X = 8;
static const uint THREAD_GROUP_SIZE_Y = 8;
static const uint THREAD_GROUP_SIZE_Z = 8;

static const uint GROUPS_Y = 50;
static const uint GROUPS_X = 50;
static const uint GROUPS_Z = 50;



RWStructuredBuffer<BufferStruct> OutBuff : register(u0);

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, THREAD_GROUP_SIZE_Z)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex)
{    
    float3 pos;
    const float scale = 6.0 / (THREAD_GROUP_SIZE_X * GROUPS_X);
    uint cubeIndex = 0;  
    const float3 initvert = float3(110.0, 110.0, 110.0);
    float3 vertlist[12] = { initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert, initvert };

    pos.x = (grpID.x * (THREAD_GROUP_SIZE_X) + grpTID.x) * scale  -3.0;
    pos.y = (grpID.y * (THREAD_GROUP_SIZE_Y) + grpTID.y) * scale  -3.0;
    pos.z = (grpID.z * (THREAD_GROUP_SIZE_Z) + grpTID.z) * scale  -3.0;

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

    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] == 0 || edgeTable[(cubeIndex / 4)][cubeIndex % 4] == 255)
    {
        return;
    }

    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 1)
    {
        vertlist[0] = v0 + float3(scale * 0.5, 0.0, 0.0);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 2)
    {
        vertlist[1] = v2 + float3(0.0, 0.0, scale * 0.5);
    }  
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 4)
    {
        vertlist[2] = v3 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 8)
    {
        vertlist[3] = v3 + float3(0.0, 0.0, scale * 0.5);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 16)
    {
        vertlist[4] = v4 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 32)
    {
        vertlist[5] = v6 + float3(0.0, 0.0, scale * 0.5);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 64)
    {
        vertlist[6] = v7 + float3(scale * 0.5, 0.0, 0.0);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 128)
    {
        vertlist[7] = v7 + float3(0.0, 0.0, scale * 0.5);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 256)
    {
        vertlist[8] = v0 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 512)
    {
        vertlist[9] = v1 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 1024)
    {
        vertlist[10] = v2 + float3(0.0, scale * 0.5, 0.0);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 2048)
    {
        vertlist[11] = v3 + float3(0.0, scale * 0.5, 0.0);
    }


    uint nverts = 0;
    uint idx = OutBuff.IncrementCounter()*15;
    [loop]
    for (uint i = 0; triTable[(cubeIndex * 16 + i) / 4][(cubeIndex * 16 + i) % 4] != -1; i += 3)
    {

        OutBuff[idx + nverts].pos = vertlist[triTable[(cubeIndex * 16 + i) / 4][(cubeIndex * 16 + i) % 4]];
        OutBuff[idx + nverts + 1].pos = vertlist[triTable[(cubeIndex * 16 + i + 1) / 4][(cubeIndex * 16 + i + 1) % 4]];
        OutBuff[idx + nverts + 2].pos = vertlist[triTable[(cubeIndex * 16 + i + 2) / 4][(cubeIndex * 16 + i + 2) % 4]];

        const float3 normal = normalize(cross((OutBuff[idx + nverts + 1].pos - OutBuff[idx + nverts].pos), (OutBuff[idx + nverts + 2].pos - OutBuff[idx + nverts].pos)));
        OutBuff[idx + nverts].normal = normal;
        OutBuff[idx + nverts + 1].normal = normal;
        OutBuff[idx + nverts + 2].normal = normal;\

        OutBuff[idx + nverts].color = float3(0.7,0.9,0.3);
        OutBuff[idx + nverts + 1].color = float3(0.7, 0.9, 0.3);
        OutBuff[idx + nverts + 2].color = float3(0.7, 0.9, 0.3);
        nverts += 3;
    }

 
}