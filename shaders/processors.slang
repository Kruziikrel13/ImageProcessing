StructuredBuffer<float4> inputImage;
RWStructuredBuffer<float4> outputImage;

[shader("compute")]
[numthreads(256, 1, 1)]
void blurCompute(uint3 threadId: SV_DispatchThreadID) {
  uint index = threadId.x;
  int a = 1;
  int b = 2;
  int c = a + b;
};
