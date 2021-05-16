#ifdef VERTEX_SHADER

layout (location = 0) in vec4 vertex; 

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform bool flipX;
uniform bool flipY;

void main()
{    
	if (!flipX)
	{
		TexCoords.x = vertex.z;
	}
	else
	{
		TexCoords.x = -vertex.z;
	}

	if (!flipY)
	{
		TexCoords.y = vertex.w;
	}
	else
	{
		TexCoords.y = -vertex.w;
	}
	
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
#endif
#ifdef PIXEL_SHADER

in vec2 TexCoords;
out vec4 ps;

uniform sampler2D Image;
uniform vec4 Colour;

void main()
{
	ps = Colour * texture(Image, TexCoords);
	//
}
#endif