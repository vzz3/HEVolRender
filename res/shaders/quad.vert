#version 450

layout (location = 0) out vec2 outUV;

vec2 uvData[4] = vec2[](
    vec2(0.0, 1.0), // left bottom in vulkan
    vec2(1.0, 1.0),	// right bottom
    vec2(0.0, 0.0),	// left top
	vec2(1.0, 0.0)	// right top
);

uint indexData[6] = uint[](
	0, 1, 2, // left bottom
	3, 2, 1  // right top
);

float scale = 0.3f;

void main()
{
	outUV = uvData[indexData[gl_VertexIndex]];
	vec2 screenPos = outUV * 2.0f - 1.0f; // full screen
	screenPos = screenPos * scale - (1.0f - (scale)) + 0.05f;

	gl_Position = vec4(screenPos, 0.0f, 1.0f);
}
