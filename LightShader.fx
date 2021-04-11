texture LightTexture;
sampler2D LightMap = sampler_state
{
	Texture = (LightTexture);
};

float Darkness;

float4 ps_main(float2 uv : TEXCOORD) : COLOR0
{
	float4 Light = tex2D(LightMap, uv);
	float4 Dark = float4(0, 0, 0, Darkness);
	
	Dark += Light;
	Dark.a = Darkness -  Light.a;
	
	if (Dark.a <= 0.05)
		Dark.a = 0.05;

	return Dark;
}

technique
{
	pass p0
	{
		AlphaBlendEnable = TRUE;
		DestBlend = INVSRCALPHA;
		SrcBlend = SRCALPHA;
		PixelShader = compile ps_2_0 ps_main();
	}
};