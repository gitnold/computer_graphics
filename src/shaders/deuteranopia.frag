
#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;
    
    // LMS color space transformation matrix (RGB to LMS)
    mat3 rgb2lms = mat3(
        17.8824, 43.5161, 4.11935,
        3.45565, 27.1554, 3.86714,
        0.0299566, 0.184309, 1.46709
    );
    
    // Convert to LMS
    vec3 lms = rgb2lms * color;
    
    // Deuteranopia simulation - remove M component influence
    // Approximate missing M-cone response from L and S cones
    lms.g = 0.494207 * lms.r + 1.24827 * lms.b;
    
    // LMS back to RGB transformation matrix
    mat3 lms2rgb = mat3(
        0.0809444479, -0.130504409, 0.116721066,
        -0.0102485335, 0.0540193266, -0.113614708,
        -0.000365296938, -0.00412161469, 0.693511405
    );
    
    vec3 deuteranopia = lms2rgb * lms;
    
    FragColor = vec4(clamp(deuteranopia, 0.0, 1.0), 1.0);
}
