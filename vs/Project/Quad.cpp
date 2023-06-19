#include "Quad.h"

using namespace Engine;

Quad::Quad()
{
	Build();
}

Quad::~Quad()
{
}

void Quad::Draw()
{
	// Bind VAO and draw primitive using GL_QUADS
	//mengaktifkan vao
	glBindVertexArray(vao);
	// menggambar data yang di VBO dengan primitif GL_QUADS menggunakan tipe unsigned int
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Quad::Build()
{
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f  // Bottom Left 
		// karena 2 dimensi maka nilai z nya 0
		// koordinat 1,1 akan dipetakan ke koordinat tekstur 1,0 dst
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	//generate vao, vbo, ebo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	//aktifkan vao
	glBindVertexArray(vao);

	//aktifkan vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//copykan data yang udah digenerate ke vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//aktifkan ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//copykan data yang udah digenerate ke ebo
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// atribut akan masuk kedalam VAO
	
	// Position attribute
	// karena posisi data ke-0, maka dia (0, ..), sedangkan (.., 3) menunjukkan jumlah komponen
	// GL_FLOAT itu tipe datanya
	// ukuran stride  8 * sizeof(GLfloat)
	// offside nya di 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
    // karena posisi data ke-1, maka dia (1, ..), sedangkan (.., 3) menunjukkan jumlah komponen
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
    // karena posisi data ke-2, maka dia (02, ..), sedangkan (.., 2) menunjukkan jumlah komponen
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
