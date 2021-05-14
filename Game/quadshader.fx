
Texture2D tx : register(t0);

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
    bool flipX;
    bool flipY; // Todo checking padding
};

cbuffer ColourBuffer
{
    float r;
    float g;
    float b;
    float a;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Col : COLOUR;
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
    
    if (!flipX)
    {
        output.Tex.x = input.Tex.x;
    }
    else
    {
        output.Tex.x = -input.Tex.x;
    }
    
    if (!flipY)
    {
        output.Tex.y = input.Tex.y;
    }
    else
    {
        output.Tex.y = -input.Tex.y;
    }
	
    output.Col = float4(r, g, b, a);
    
    return output;
}

float4 PS(PS_INPUT IN) : SV_TARGET
{
    float4 vColor = float4(1, 1, 1, 1);

    vColor = IN.Col * tx.Sample(linearSampler, IN.Tex);
    
    return vColor;
}