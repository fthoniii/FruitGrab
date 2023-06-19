// akan menggunakan versi 3.3
#version 330 core

// mendefinisikan 3 variabel input
// datanya di copy dari vbo
// berlaku untuk semua vertex yang ada di GPU, paralel processing
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform int nx = 1;
uniform int ny = 1;
uniform int frameIndex = 0;

// matriks untuk tansformasi model
uniform mat4 model;

// untuk orthographic projection
uniform mat4 projection; 

out vec3 ourColor;
out vec2 TexCoord;

void main() 
{
    
    gl_Position = projection * model * vec4(position, 1.0f);
    ourColor = color;
    int frameX = frameIndex % nx;
    int frameY = frameIndex / nx;
    float x = ((1.0f / nx) * (texCoord.x + frameX));
    float y = ((1.0f / ny) * (texCoord.y + frameY)); 
    // vertex gak bisa memproses warna dan texcoord
    // lempar data TextCoord ke fragment shader, jadi variabel input di fragment
    TexCoord = vec2(x, y);
}



