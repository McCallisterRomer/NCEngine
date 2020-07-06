cbuffer CBuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VSOut
{
    float3 posFromCam : Position;
    float3 normal : Normal;
    float4 pos : SV_Position;
    float2 tex : TexCoord;
};

VSOut main(float3 pos : Position, float3 n : normal, float2 tex : TexCoord)
{
    VSOut vso;
    vso.posFromCam = (float3)mul(float4(pos, 1.0f), modelView);  //transformation on homogeneous coords
    vso.normal = mul(n, (float3x3)modelView);                //apply rotation to normals, but not translation
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);  //
    vso.tex = tex;
    return vso;
}