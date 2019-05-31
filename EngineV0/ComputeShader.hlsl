struct BufferStruct {
	float3 pos;
};

static const int THREAD_GROUP_SIZE_X = 20;
static const int THREAD_GROUP_SIZE_Y = 20;
static const int THREAD_GROUP_SIZE_Z = 1;

static const int GROUPS_Y = 20;
static const int GROUPS_X = 20;
static const int GROUPS_Z = 1;

RWStructuredBuffer<BufferStruct> OutBuff;

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, 1)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex) 
{
    int idx = id.x + (id.y * THREAD_GROUP_SIZE_X * GROUPS_X) + (id.z * THREAD_GROUP_SIZE_X * GROUPS_Y * THREAD_GROUP_SIZE_Y * GROUPS_Z);
    float3 pos = (id + grpTID + (grpID * float3(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, THREAD_GROUP_SIZE_Z)));
    OutBuff[idx].pos = pos;

}