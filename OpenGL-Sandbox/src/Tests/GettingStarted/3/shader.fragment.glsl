#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
	vec4 texColor = u_Color;
	switch(int(v_TexIndex))
	{
		 case 0: texColor *= texture(u_Texture0, v_TexCoord); break;
		 case 1: texColor *= texture(u_Texture1, v_TexCoord); break;
	}
	color = texColor; 
}