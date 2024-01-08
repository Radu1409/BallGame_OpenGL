//#version 330 core

//in vec3 FragPos;
//in vec3 Normal;

//out vec4 color;

//uniform vec3 sphereColor;
//uniform vec3 lightColor;
//uniform vec3 lightPosition;

//void main()
//{
//    vec3 ambient = 0.1 * lightColor;  

//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPosition - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;  

//    vec3 result = (ambient + diffuse) * sphereColor;
//    color = vec4(result, 1.0f);
//}

#version 330 core

in vec3 v_vertexColors;
in vec3 v_tableColor;

out vec4 color;

uniform vec3 sphereColor;

uniform vec3 lightColor;

uniform vec3 lightPosition;

void main()
{
    vec3 sphereLighting = lightColor * sphereColor;
    vec3 tableLighting = lightColor * v_tableColor;

    color = vec4(v_vertexColors, 1.0f);
};



