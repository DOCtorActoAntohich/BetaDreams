#version 410 core

in vec4 rgbMultipliers;
in vec2 textureCoordinate;

out vec4 resultingColor;

uniform sampler2D u_texture;



vec4 getTexturePixel() {
	return rgbMultipliers * texture(u_texture, textureCoordinate);
}



void main() {
	resultingColor = getTexturePixel();
}

