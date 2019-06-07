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
    const uint loops = 500;
    [loop]
    for (uint i = 0; i < loops; i++)
    {
        [branch]
        if (length(vect) > 200)
        {
            return 2.0f - (float(i) / (float) loops);
        }

        float3 vect2;
        vect2.x = pow(vect.x, 3) - 3 * vect.x * (pow(vect.y, 2) + pow(vect.z, 2)) + c.x;
        vect2.y = -pow(vect.y, 3) + 3 * vect.y * pow(vect.x, 2) - vect.y * pow(vect.z, 2) + c.y;
        vect2.z = pow(vect.z, 3) - 3 * vect.z * pow(vect.x, 2) + vect.z * pow(vect.y, 2) + c.z;
        vect = vect2;
    }

    return 0.0;
}

float MandelbarSet(float3 vect)
{
    const float3 c = vect;
    const uint loops = 200;
    [loop]
    for (uint j = 0; j < loops; j++)
    {
        [branch]
        if (length(vect) > 200)
        {
            return 2.0f - (float(j) / (float) loops);
        }
        float3 vect2;
        vect2.x = pow(vect.x, 2) - pow(vect.y, 2) - pow(vect.z, 2);
        vect2.y = 2*vect.x*vect.y;
        vect2.z = -2 * vect.x * vect.z;
        vect = vect2 + c;
    }
    return 0.0f;
}



float3 vertexInterp(float isolevel, float3 p1, float3 p2, float valp1, float valp2)
{
float mu;
float3 p;
   [branch]
   if (abs(isolevel-valp1) < 0.00001)
    {
        return (p1);
    }
   [branch]
   if (abs(isolevel-valp2) < 0.00001)
    {
        return (p2);
    }
   [branch]
   if (abs(valp1-valp2) < 0.00001)
    {
        return (p1);
    }



   mu = (isolevel - valp1) / (valp2 - valp1);
   p.x = p1.x + mu * (p2.x - p1.x);
   p.y = p1.y + mu * (p2.y - p1.y);
   p.z = p1.z + mu * (p2.z - p1.z);

   return(p);

}

struct BufferStruct {
	float3 pos;
    float3 normal;
    float3 color;
};

struct Cvert
{
    float3 pos;
    float val;
};



static const uint THREAD_GROUP_SIZE_X = 7;
static const uint THREAD_GROUP_SIZE_Y = 7;
static const uint THREAD_GROUP_SIZE_Z = 7;

static const uint GROUPS_Y = 200;
static const uint GROUPS_X = 200;
static const uint GROUPS_Z = 200;
static const float isolevel = 1.0;

RWStructuredBuffer<BufferStruct> OutBuff : register(u0);

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, THREAD_GROUP_SIZE_Z)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex)
{   

    float3 pos;
    const float scale = 6.0 / (THREAD_GROUP_SIZE_X * GROUPS_X);
    uint cubeIndex = 0;  
    const float3 initvert = float3(0.0, 0.0, 0.0);
    Cvert vertlist[12];

    pos.x = (grpID.x * (THREAD_GROUP_SIZE_X) + grpTID.x) * scale  -3.0;
    pos.y = (grpID.y * (THREAD_GROUP_SIZE_Y) + grpTID.y) * scale  -3.0;
    pos.z = (grpID.z * (THREAD_GROUP_SIZE_Z) + grpTID.z) * scale  -3.0;

    Cvert v0;
    v0.pos = pos + float3(0.0, 0.0, scale);
    v0.val = MandelbarSet(v0.pos);
    [branch] 
    if (v0.val < isolevel)
    {
        cubeIndex |= 1;
    }
    Cvert v1;
    v1.pos = pos + float3(scale, 0.0, scale);
    v1.val = MandelbarSet(v1.pos);
    [branch]
    if (v1.val < isolevel)
    {
        cubeIndex |= 2;
    }
    Cvert v2;
    v2.pos = pos + float3(scale, 0.0, 0.0);
    v2.val = MandelbarSet(v2.pos);
    [branch]
    if (v2.val < isolevel)
    {
        cubeIndex |= 4;
    }
    Cvert v3;
    v3.pos = pos;
    v3.val = MandelbarSet(v3.pos);
   [branch]
    if (v3.val < isolevel)
    {
        cubeIndex |= 8;
    }
    Cvert v4;
    v4.pos = pos + float3(0.0, scale, scale);
    v4.val = MandelbarSet(v4.pos);
   [branch]
    if (v4.val < isolevel)
    {
        cubeIndex |= 16;
    }
    Cvert v5;
    v5.pos = pos + float3(scale, scale, scale);
    v5.val = MandelbarSet(v5.pos);
    [branch]
    if (v5.val < isolevel)
    {
        cubeIndex |= 32;
    }
    Cvert v6;
    v6.pos = pos + float3(scale, scale, 0.0);
    v6.val = MandelbarSet(v6.pos);
   [branch]
    if (v6.val < isolevel)
    {
        cubeIndex |= 64;
    }
    Cvert v7;
    v7.pos = pos + float3(0.0, scale, 0.0);
    v7.val = MandelbarSet(v7.pos);
    [branch]
    if (v7.val < isolevel)
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
        vertlist[0].pos = vertexInterp(isolevel, v0.pos, v1.pos, v0.val, v1.val);
        vertlist[0].val =   2.0 -  (v0.val + v1.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 2)
    {
        vertlist[1].pos = vertexInterp(isolevel, v1.pos, v2.pos, v1.val, v2.val);
        vertlist[1].val = 2.0 - (v1.val + v2.val);
    }  
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 4)
    {
        vertlist[2].pos = vertexInterp(isolevel, v2.pos, v3.pos, v2.val, v3.val);
        vertlist[2].val = 2.0 - (v2.val + v3.val);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 8)
    {
        vertlist[3].pos = vertexInterp(isolevel, v3.pos, v0.pos, v3.val, v0.val);
        vertlist[3].val = 2.0 - (v3.val + v0.val);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 16)
    {
        vertlist[4].pos = vertexInterp(isolevel, v4.pos, v5.pos, v4.val, v5.val);
        vertlist[4].val = 2.0 - (v4.val + v5.val);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 32)
    {
        vertlist[5].pos = vertexInterp(isolevel, v5.pos, v6.pos, v5.val, v6.val);
        vertlist[5].val = 2.0 - (v5.val + v6.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 64)
    {
        vertlist[6].pos = vertexInterp(isolevel, v6.pos, v7.pos, v6.val, v7.val);
        vertlist[6].val = 2.0 - (v6.val + v7.val);
    }
   [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 128)
    {
        vertlist[7].pos = vertexInterp(isolevel, v7.pos, v4.pos, v7.val, v4.val);
        vertlist[7].val = 2.0 - (v7.val + v4.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 256)
    {
        vertlist[8].pos = vertexInterp(isolevel, v0.pos, v4.pos, v0.val, v4.val);
        vertlist[8].val = 2.0 - (v0.val + v4.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 512)
    {
        vertlist[9].pos = vertexInterp(isolevel, v1.pos, v5.pos, v1.val, v5.val);
        vertlist[9].val = 2.0 - (v1.val + v5.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 1024)
    {
        vertlist[10].pos = vertexInterp(isolevel, v2.pos, v6.pos, v2.val, v6.val);
        vertlist[10].val = 2.0 - (v2.val + v6.val);
    }
    [branch]
    if (edgeTable[(cubeIndex / 4)][cubeIndex % 4] & 2048)
    {
        vertlist[11].pos = vertexInterp(isolevel, v3.pos, v7.pos, v3.val, v7.val);
        vertlist[0].val = 2.0 - (v0.val + v1.val);
    }


    uint nverts = 0;
    const uint idx = OutBuff.IncrementCounter()*15;
    [loop]
    for (uint i = 0; triTable[(cubeIndex * 16 + i) / 4][(cubeIndex * 16 + i) % 4] != -1; i += 3)
    {

        Cvert p1 = vertlist[triTable[(cubeIndex * 16 + i) / 4][(cubeIndex * 16 + i) % 4]];
        Cvert p2 = vertlist[triTable[(cubeIndex * 16 + i + 2) / 4][(cubeIndex * 16 + i + 2) % 4]];
        Cvert p3 = vertlist[triTable[(cubeIndex * 16 + i + 1) / 4][(cubeIndex * 16 + i + 1) % 4]];
 
        OutBuff[idx + nverts].pos = p1.pos;
        OutBuff[idx + nverts + 1].pos = p2.pos;
        OutBuff[idx + nverts + 2].pos = p3.pos;

        const float3 normal = normalize(cross(p2.pos - p1.pos, p3.pos - p1.pos));
        OutBuff[idx + nverts].normal = normal;
        OutBuff[idx + nverts + 1].normal = normal;
        OutBuff[idx + nverts + 2].normal = normal;

        OutBuff[idx + nverts].color = float3(p1.pos.x+1.5, p1.pos.y+1.5, p1.pos.z+1.5);
        OutBuff[idx + nverts + 1].color = float3(p2.pos.x+1.5, p2.pos.y+1.5, p2.pos.z+1.5);
        OutBuff[idx + nverts + 2].color = float3(p3.pos.x+1.5, p3.pos.y+1.5, p3.pos.z+1.5);
        nverts += 3;
    }
}