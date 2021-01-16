#version 450

#define BOARDER_EPSYLON 0.005f

layout (binding = 1) uniform sampler2D samplerColor;

layout (location = 0) in vec2 inUV;

layout (location = 0) out vec4 outFragColor;

void main()
{
	if(    inUV.x < (BOARDER_EPSYLON) || inUV.x > (1.0f - BOARDER_EPSYLON)
		|| inUV.y < (BOARDER_EPSYLON) || inUV.y > (1.0f - BOARDER_EPSYLON)
	) {
		// draw boarder
		outFragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
	} else {
		outFragColor = texture(samplerColor, inUV);
	}
}
