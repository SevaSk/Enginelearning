struct BufferStruct {
	float3 pos;
};

static const int THREAD_GROUP_SIZE_X = 21;
static const int THREAD_GROUP_SIZE_Y = 21;
static const int THREAD_GROUP_SIZE_Z = 1;

static const int GROUPS_Y = 21;
static const int GROUPS_X = 21;
static const int GROUPS_Z = 1;

RWStructuredBuffer<BufferStruct> OutBuff;

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, 1)]
void main(uint3 grpID : SV_GroupID, uint3 id : SV_DispatchThreadId, uint3 grpTID : SV_GroupThreadId, uint grpIdx : SV_GroupIndex) 
{

    OutBuff[OutBuff.IncrementCounter()].pos = grpTID;


}