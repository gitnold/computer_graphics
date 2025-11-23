#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform int colorblindMode;

void main()
{
    vec3 texColor = texture(tex0, texCoord).rgb;
    
    if (colorblindMode == 0) {
        // Normal vision
        FragColor = vec4(texColor, 1.0);
        return;
    }
    
    vec3 result;
    
    if (colorblindMode == 1) {
        // Protanopia (red-blind)
        result.r = 0.56667 * texColor.r + 0.43333 * texColor.g;
        result.g = 0.55833 * texColor.r + 0.44167 * texColor.g;
        result.b = 0.24167 * texColor.g + 0.75833 * texColor.b;
    } 
    else if (colorblindMode == 2) {
        // Deuteranopia (green-blind)
        result.r = 0.625 * texColor.r + 0.375 * texColor.g;
        result.g = 0.7 * texColor.r + 0.3 * texColor.g;
        result.b = 0.3 * texColor.g + 0.7 * texColor.b;
    } 
    else if (colorblindMode == 3) {
        // Tritanopia (blue-blind)
        result.r = 0.95 * texColor.r + 0.05 * texColor.g;
        result.g = 0.43333 * texColor.g + 0.56667 * texColor.b;
        result.b = 0.475 * texColor.g + 0.525 * texColor.b;
    }
    else {
        result = texColor;
    }
    
    FragColor = vec4(result, 1.0);
}
