
Texture2D tx : register(t0);


SamplerState samLinear : register(s0)
{
    Filter = ANISOTROPIC;
    MaxAnisotropy = 4;

    AddressU = WRAP;
    AddressV = WRAP;
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

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    
    output.Pos = input.Pos;
   
    output.Tex = input.Tex;
  
    return output;
}

float4 PS(PS_INPUT IN) : SV_TARGET
{
    float4 vColor;
    
    vColor = tx.Sample(samLinear, IN.Tex);
    
    return vColor;
}