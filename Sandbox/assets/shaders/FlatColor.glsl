#type vertex
#version 330 core
layout (location=0) in vec3 position;

void main()
{
	gl_Position=vec4(position.x, position.y,position.z,1.0);
}

#type fragment
#version 330 core

// Ouput data
layout (location=0) out vec3 color;

void main()
{
	// Output color = red 
	color = vec3(1,0,0);

}