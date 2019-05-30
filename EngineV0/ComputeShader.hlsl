struct BufferStruct {
	uint4 color;
};

static const int THREAD_GROUP_SIZE_X = 20;
static const int THREAD_GROUP_SIZE_Y = 20;
static const int THREAD_GROUPS_X = 20;

RWStructuredBuffer<BufferStruct> OutBuff;

[numthreads(THREAD_GROUP_SIZE_X, THREAD_GROUP_SIZE_Y, 1)]
void main(uint3 threadIDInGroup : SV_GroupThreadID, uint3 groupID : SV_GroupID) 
{
	float4 color = float4((float)threadIDInGroup.x / THREAD_GROUP_SIZE_X,
		(float)threadIDInGroup.y / THREAD_GROUP_SIZE_Y, 0, 1
		) * 255;
	int buffIndex = (groupID.y * THREAD_GROUP_SIZE_Y + threadIDInGroup.y)
		* THREAD_GROUPS_X * THREAD_GROUP_SIZE_X
		+ (groupID.x * THREAD_GROUP_SIZE_X + threadIDInGroup.x);
	OutBuff[buffIndex].color = color;
}