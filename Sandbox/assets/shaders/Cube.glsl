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

layout ( location = 5 ) out VertexOutput Output;
layout ( location = 0 ) out vec3 barycoords;

void main()
{
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
	texColor *= texture(u_Textures[ 0], Input.TexCoord * 1.0);
	out_FragColor = mix( texColor * vec4(0.8), texColor, edgeFactor(2.0) );
};
