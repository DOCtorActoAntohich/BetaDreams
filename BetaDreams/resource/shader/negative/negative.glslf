#version 410 core

in vec4 rgbMultipliers;
in vec2 textureCoordinate;

out vec4 resultingColor;

uniform sampler2D u_texture;



vec4 getTexturePixel() {
	return rgbMultipliers * texture(u_texture, textureCoordinate);
}



vec4 invert(vec4 color, bool keepAlpha = true) {
    vec4 newColor = vec4(1, 1, 1, 1) - color;
	if (keepAlpha) {
	    newColor.w = color.w;
	}
	return newColor;
}



void main() {
	vec4 resultColor = getTexturePixel();
	resultingColor = invert(resultColor);
}
