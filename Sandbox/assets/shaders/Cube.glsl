#type vertex
#version 460 core

layout ( location = 0 ) in vec3 a_Position;
layout ( location = 1 ) in vec4 a_Color;
layout ( location = 2 ) in vec2 a_TexCoord;
layout ( location = 3 ) in float a_TexIndex;
layout ( location = 4 ) in float a_TilingFactor;
layout ( location = 5 ) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

layout ( location = 0 ) out vec4 v_Color;
layout ( location = 1 ) out vec2 v_TexCoord;
layout ( location = 2 ) out flat float v_TexIndex;
layout ( location = 4 ) out flat float v_TilingFactor;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
};

#type geometry
#version 460 core

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
};

layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 3 ) out;

layout ( location = 0 ) in vec4 v_Color[];
layout ( location = 1 ) in vec2 v_TexCoord[];
layout ( location = 2 ) in flat float v_TexIndex[];
layout ( location = 3 ) in flat float v_TilingFactor[];

layout ( location = 2 ) out flat float g_TexIndex;
layout ( location = 5 ) out VertexOutput Output;
layout ( location = 0 ) out vec3 barycoords;

void main()
{
	g_TexIndex = v_TexIndex[0];
	Output.TilingFactor = 1.0f;

	const vec3 bc[3] = vec3[]
	(
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);

	for ( int i = 0; i < 3; i++ )
	{
		gl_Position = gl_in[i].gl_Position;
		Output.Color = v_Color[i];
		Output.TexCoord = v_TexCoord[i];
		barycoords = bc[i];
		EmitVertex();
	}
	EndPrimitive();
};

#type fragment
#version 460 core

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
};

layout (binding = 0) uniform sampler2D u_Textures[32];

layout ( location = 2 ) in flat float TexIndex;
layout ( location = 5 ) in VertexOutput Input;
layout ( location = 0 ) in vec3 barycoords;
layout ( location = 0 ) out vec4 out_FragColor;

float edgeFactor(float thickness)
{
	vec3 a3 = smoothstep( vec3(0.0), fwidth(barycoords) * thickness, barycoords);
	return min ( min (a3.x, a3.y), a3.z );
}

void main ()
{
	
	vec4 texColor = Input.Color;
	
	switch(int(TexIndex))
	{
		case  0: texColor *= texture(u_Textures[ 0], Input.TexCoord * Input.TilingFactor); break;
		case  1: texColor *= texture(u_Textures[ 1], Input.TexCoord * Input.TilingFactor); break;
		case  2: texColor *= texture(u_Textures[ 2], Input.TexCoord * Input.TilingFactor); break;
		case  3: texColor *= texture(u_Textures[ 3], Input.TexCoord * Input.TilingFactor); break;
		case  4: texColor *= texture(u_Textures[ 4], Input.TexCoord * Input.TilingFactor); break;
		case  5: texColor *= texture(u_Textures[ 5], Input.TexCoord * Input.TilingFactor); break;
		case  6: texColor *= texture(u_Textures[ 6], Input.TexCoord * Input.TilingFactor); break;
		case  7: texColor *= texture(u_Textures[ 7], Input.TexCoord * Input.TilingFactor); break;
		case  8: texColor *= texture(u_Textures[ 8], Input.TexCoord * Input.TilingFactor); break;
		case  9: texColor *= texture(u_Textures[ 9], Input.TexCoord * Input.TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], Input.TexCoord * Input.TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], Input.TexCoord * Input.TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], Input.TexCoord * Input.TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], Input.TexCoord * Input.TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], Input.TexCoord * Input.TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], Input.TexCoord * Input.TilingFactor); break;
		case 16: texColor *= texture(u_Textures[16], Input.TexCoord * Input.TilingFactor); break;
		case 17: texColor *= texture(u_Textures[17], Input.TexCoord * Input.TilingFactor); break;
		case 18: texColor *= texture(u_Textures[18], Input.TexCoord * Input.TilingFactor); break;
		case 19: texColor *= texture(u_Textures[19], Input.TexCoord * Input.TilingFactor); break;
		case 20: texColor *= texture(u_Textures[20], Input.TexCoord * Input.TilingFactor); break;
		case 21: texColor *= texture(u_Textures[21], Input.TexCoord * Input.TilingFactor); break;
		case 22: texColor *= texture(u_Textures[22], Input.TexCoord * Input.TilingFactor); break;
		case 23: texColor *= texture(u_Textures[23], Input.TexCoord * Input.TilingFactor); break;
		case 24: texColor *= texture(u_Textures[24], Input.TexCoord * Input.TilingFactor); break;
		case 25: texColor *= texture(u_Textures[25], Input.TexCoord * Input.TilingFactor); break;
		case 26: texColor *= texture(u_Textures[26], Input.TexCoord * Input.TilingFactor); break;
		case 27: texColor *= texture(u_Textures[27], Input.TexCoord * Input.TilingFactor); break;
		case 28: texColor *= texture(u_Textures[28], Input.TexCoord * Input.TilingFactor); break;
		case 29: texColor *= texture(u_Textures[29], Input.TexCoord * Input.TilingFactor); break;
		case 30: texColor *= texture(u_Textures[30], Input.TexCoord * Input.TilingFactor); break;
		case 31: texColor *= texture(u_Textures[31], Input.TexCoord * Input.TilingFactor); break;
	}

	out_FragColor = mix( texColor * vec4(0.8), texColor, edgeFactor(2.0) );
};
