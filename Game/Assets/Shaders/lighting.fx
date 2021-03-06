
Texture2D scene : register(t0);
Texture2D light : register(t0);

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

SamplerState linearSampler : register(s0);

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.Pos.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.Pos = mul(input.Pos, worldMatrix);
    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    
    return output;
}

float4 PS(PS_INPUT IN) : SV_TARGET
{
    float4 vColor = float4(1, 1, 1, 1);

    vColor = IN.Col * tx.Sample(linearSampler, IN.Tex);
    
    return vColor;
}