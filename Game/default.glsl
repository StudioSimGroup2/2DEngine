#ifdef VERTEX_SHADER

layout (location = 0) in vec4 vertex; 

out vec2 TexCoords;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 World;

void main()
{    
    TexCoords = vertex.zw;
	gl_Position = Model * View * Projection * vec4(vertex.xy, 0.0, 1.0);
}
#endif
#ifdef PIXEL_SHADER

in vec2 TexCoords;
out vec4 color;

uniform sampler2D Image;

void main()
{
	color = texture(Image, TexCoords);
}
#endif