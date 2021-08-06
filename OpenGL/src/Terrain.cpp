#include "Terrain.h"

int indices[zSize * xSize];
glm::vec3 vector[zSize * xSize];

void Terrain::terrainInitialization()
{
	for (int i = 0,z = 0; z <= zSize; z++) 
		for (int x = 0; x <= xSize; x++)
		{
			vector[i] = glm::vec3(x, 0, z);
			i++;
		}
	for (int j = 0, i = 0; i < xSize * zSize-5 ; i += 6, j++)
	{

		if (i % (xSize*6) == 0 && j!=0)
			j++;
		indices[i] = j;
		indices[i + 1] = xSize + j + 1;
		indices[i + 2] = j + 1;

		indices[i + 3] = xSize + j + 1;
		indices[i + 4] = j + 1;
		indices[i + 5] = j + 2 +xSize;
	}

	glGenBuffers(1, &TerrainVAO);
	glBindVertexArray(TerrainVAO);

	glGenBuffers(1, &TerrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, TerrainVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vector), vector, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(TerrainVAO);

}
void Terrain::terrainDraw()
{
	glBindVertexArray(TerrainVAO);
	glDrawElements(GL_TRIANGLES, xSize * zSize, GL_UNSIGNED_INT, 0);
}