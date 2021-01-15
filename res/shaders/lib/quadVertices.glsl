
/*
 * @private
 */
vec2 quadVertices_uvData[4] = vec2[](
    vec2(0.0, 1.0), // left bottom in vulkan
    vec2(1.0, 1.0),	// right bottom
    vec2(0.0, 0.0),	// left top
	vec2(1.0, 0.0)	// right top
);

/*
 * @private
 */
uint quadVertices_indexData[6] = uint[](
	0, 1, 2, // left bottom
	3, 2, 1  // right top
);

/**
 * @public
 * @param yVertexIndex	should usaly be the build in constant "gl_VertexIndex"
 */
vec2 quadVertices_getUvByTriangleIndex(int yVertexIndex) {
	return quadVertices_uvData[quadVertices_indexData[yVertexIndex]];
}
