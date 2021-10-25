cbuffer constantBuffer
{
	float4 face_colours[6];
};

float4 main(uint triangle_id : SV_PrimitiveID) : SV_TARGET
{
	return face_colours[triangle_id/2];
}