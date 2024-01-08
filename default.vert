//#version 330 core

//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 vertexColors;

//out vec3 FragPos;  
//out vec3 Normal;   

//uniform mat4 camMatrix;
//uniform mat4 model;

//void main()
//{
//   FragPos = vec3(model * vec4(aPos, 1.0));
//   Normal = mat3(transpose(inverse(model))) * vertexColors; 
//   gl_Position = camMatrix * vec4(aPos, 1.0);
//}

//#version 330 core

//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 vertexColors;

//out vec3 v_vertexColors;

//uniform vec3 sphereColor;
//uniform vec3 lightColor;
//uniform vec3 lightPosition;
//uniform mat4 camMatrix;

//void main()
//{
//   v_vertexColors = vertexColors;
//   gl_Position = camMatrix * vec4(aPos, 1.0);
//}

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColors;

out vec3 v_vertexColors;
out vec3 v_tableColor;

uniform vec3 sphereColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform mat4 camMatrix;

void main()
{
   v_vertexColors = vertexColors;

   vec3 lightDirection = normalize(lightPosition - aPos);

   vec3 normal = normalize(aPos);

   float diff = max(0.0, dot(normal, lightDirection));

   vec3 ambientColor = 0.10 * sphereColor; 
   vec3 diffuseColor = diff * lightColor * sphereColor; 
   vec3 finalColor = ambientColor + diffuseColor;

   v_vertexColors = finalColor;
   v_tableColor = vec3(0.4, 0.2, 0.0);

   gl_Position = camMatrix * vec4(aPos, 1.0);
}
