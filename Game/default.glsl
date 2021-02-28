#ifdef VERTEX_SHADER

layout (location = 0) in vec4 vertex; 

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
#endif
#ifdef PIXEL_SHADER

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
	color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}
#endif