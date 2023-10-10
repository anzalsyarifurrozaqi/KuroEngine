#type vertex
#version 460 core

layout(std140, binding = 0) uniform CameraData
{
	mat4 View;
	mat4 Proj;
	vec4 CameraPos;
};

struct Vertex
{
	float Position[3];
	float Normal[3];
	float TexCoords[2];
	float Tangent[3];
	float Bitangent[3];
};

layout(std430, binding = 1) restrict readonly buffer Vertices
{
	Vertex in_Vertices[];
};

layout(std430, binding = 2) restrict readonly buffer Matrices // TODO : perlu create buffer untuk model
{
	mat4 in_ModelMatrices[];
};


layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_EntityID;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) out VertexOutput Output;
layout (location = 1) out flat int v_EntityID;

void main()
{
	Output.Color = vec4(a_Position, 1.0);
	v_EntityID = a_EntityID;

	// mat4 model = in_ModelMatrices[gl_BaseInstance]; TODO : perlu create buffer untuk model;
	mat4 MVP = View;

	gl_Position = MVP * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;
layout (location = 1) in flat int v_EntityID;

void main()
{
	vec4 texColor = Input.Color;

	o_Color = texColor;
	o_EntityID = v_EntityID;
}
