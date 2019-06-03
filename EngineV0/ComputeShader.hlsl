struct BufferStruct {
	float3 pos;
    float padding;
};

static const int THREAD_GROUP_SIZE_X = 10;
static const int THREAD_GROUP_SIZE_Y = 10;
static const int THREAD_GROUP_SIZE_Z = 10;

static const int GROUPS_Y = 25;
static const int GROUPS_X = 25;
static const int GROUPS_Z = 25;

RWStructuredBuffer<BufferStruct> OutBuff;

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, THREAD_GROUP_SIZE_Z)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex) 
{

    uint idx = (grpID.x + grpID.y * (GROUPS_X) + grpID.z * (GROUPS_X * GROUPS_Y)) * (THREAD_GROUP_SIZE_X * THREAD_GROUP_SIZE_Y * THREAD_GROUP_SIZE_Z) + grpTID.x + grpTID.y * (THREAD_GROUP_SIZE_X) + (THREAD_GROUP_SIZE_X * THREAD_GROUP_SIZE_Y) * grpTID.z;
    float3 pos;
    float scale = 3.0 / (THREAD_GROUP_SIZE_X * GROUPS_X);
    pos.x = (grpID.x * (THREAD_GROUP_SIZE_X) + grpTID.x) * scale;
    pos.y = (grpID.y * (THREAD_GROUP_SIZE_Y) + grpTID.y) * scale;
    pos.z = (grpID.z * (THREAD_GROUP_SIZE_Z) + grpTID.z) * scale;

    OutBuff[idx].pos = pos;

}