#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D _texture;
uniform vec4 headColor;

//lighting
uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse);

	FragColor = vec4(texture(_texture, TexCoord).xyz * headColor.xyz * result, 1.0);
}