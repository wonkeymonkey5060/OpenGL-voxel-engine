#include "world.h"

void Block::setVertexArray(std::array<bool, 6> faces){
	vertices.clear();
	vertices.reserve(48*6);

	if (faces[0] == true){ // RIGHT FACE --- VERTICES --- FACE-ID : 0
		vertices.insert(vertices.end(), {
		    // Triangle 1
		     0.5f+position[0],  0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] - pixel,      1.0f, 0.0f, 0.0f,
		     0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  1.0f, 0.0f, 0.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      1.0f, 0.0f, 0.0f,
	
		    // Triangle 2
		     0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  1.0f, 0.0f, 0.0f,
		     0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel, 		uvStart[1] + uvSize[1] / 2 + pixel,  1.0f, 0.0f, 0.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      1.0f, 0.0f, 0.0f
		});
	}
	if (faces[1] == true){ // LEFT FACE --- VERTICES --- FACE-ID : 1
		vertices.insert(vertices.end(), {
		    // Triangle 1
		    -0.5f+position[0],  0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] - pixel,      -1.0f, 0.0f, 0.0f,
		    -0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  -1.0f, 0.0f, 0.0f,
		    -0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      -1.0f, 0.0f, 0.0f,
	
		    // Triangle 2
		    -0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2,   uvStart[1] + uvSize[1] / 2,  -1.0f, 0.0f, 0.0f,
		    -0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0], 		uvStart[1] + uvSize[1] / 2,  -1.0f, 0.0f, 0.0f,
		    -0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0],       uvStart[1] + uvSize[1],      -1.0f, 0.0f, 0.0f
		});
	}

	if (faces[2] == true){ // TOP FACE --- VERTICES --- FACE-ID : 2
		vertices.insert(vertices.end(), {
		    // Triangle 1
		    -0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + pixel,                 uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 1.0f, 0.0f,
		    -0.5f+position[0],  0.5f+position[1], -0.5f+position[2],  uvStart[0] + pixel,                 uvStart[1] + uvSize[1] - pixel,      0.0f, 1.0f, 0.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 - pixel, uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 1.0f, 0.0f,
	
		    // Triangle 2
		    -0.5f+position[0],  0.5f+position[1], -0.5f+position[2],  uvStart[0] + pixel,                 uvStart[1] + uvSize[1] - pixel,      0.0f, 1.0f, 0.0f,
		     0.5f+position[0],  0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 - pixel, uvStart[1] + uvSize[1] - pixel,      0.0f, 1.0f, 0.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 - pixel, uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 1.0f, 0.0f
		});
	}
	if (faces[3] == true){ // BOTTOM FACE --- VERTICES --- FACE-ID : 3
		vertices.insert(vertices.end(), {
		    // Triangle 1
		    -0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,    uvStart[1] + pixel,                   0.0f, -1.0f, 0.0f,
		    -0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,    uvStart[1] + uvSize[1] / 2 - pixel,   0.0f, -1.0f, 0.0f,
		     0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,        uvStart[1] + pixel,                   0.0f, -1.0f, 0.0f,
	
		    // Triangle 2
		    -0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,    uvStart[1] + uvSize[1] / 2 - pixel,   0.0f, -1.0f, 0.0f,
		     0.5f+position[0], -0.5f+position[1], -0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,        uvStart[1] + uvSize[1] / 2 - pixel,   0.0f, -1.0f, 0.0f,
		     0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,        uvStart[1] + pixel,                   0.0f, -1.0f, 0.0f
		});
	}

	if (faces[4] == true){ // FRONT FACE --- VERTICES --- FACE-ID : 4
		vertices.insert(vertices.end(), {
		    // Triangle 1
		    -0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, 1.0f,
		    -0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, 1.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, 1.0f,
	
		    // Triangle 2
		    -0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, 1.0f,
		     0.5f+position[0], -0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel, 		uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, 1.0f,
		     0.5f+position[0],  0.5f+position[1],  0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, 1.0f
		});
	}
	if (faces[5] == true){ // BACK FACE --- VERTICES --- FACE-ID : 4
		vertices.insert(vertices.end(), {
		    // Triangle 1
		    -0.5f+position[0],  0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, -1.0f,
		    -0.5f+position[0], -0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, -1.0f,
		     0.5f+position[0],  0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, -1.0f,
	
		    // Triangle 2
		    -0.5f+position[0], -0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] / 2 + pixel,   uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, -1.0f,
		     0.5f+position[0], -0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] - pixel, 		 uvStart[1] + uvSize[1] / 2 + pixel,  0.0f, 0.0f, -1.0f,
		     0.5f+position[0],  0.5f+position[1],  -0.5f+position[2],  uvStart[0] + uvSize[0] - pixel,       uvStart[1] + uvSize[1] - pixel,      0.0f, 0.0f, -1.0f
		});
	}
}

void Block::addToChunkMesh(std::vector<float>* chunk_vertices){
	verticesIndex = chunk_vertices->size();
    chunk_vertices->insert(chunk_vertices->end(), vertices.begin(), vertices.end());
}

void Block::removeFromChunkMesh(std::vector<float>* chunk_vertices){
	chunk_vertices->erase(vertices.begin() + verticesIndex, vertices.begin() + verticesIndex+288);
}

Chunk::Chunk(int x, int z) {
	position[0] = x;
	position[1] = z;
    blocks.reserve(256*16*16);
	vertices.reserve(391*48*6); // estimated size: blocks × 6 verts × 8 floats
  	unorderedBlocks.max_load_factor(0.5f);
    unorderedBlocks.reserve(65536);
    double time = glfwGetTime();
    for (int i = -7; i <= 8; i++) {
	    for (int j = -7; j <= 8; j++) {
	    	for (int k = -255; k < 0; k++) {
		    	addBlock({i, k, j});
		    }
		}
	}
	cout << "block adding took " << (glfwGetTime()-time)*1000 << "ms" << endl;
    time = glfwGetTime();
    for (Block& block : blocks){
			block.setVertexArray(

				{
				(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
			 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
			 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
			 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
			 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
			 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
			 }

			 );
			block.addToChunkMesh(&vertices);
    	
    }
    cout << "block mesh adding took " << (glfwGetTime()-time)*1000 << "ms" << endl;

    initMesh();
    setMeshVertices();
    std::cout << "num_vertices = " << num_vertices << std::endl;

    model = glm::translate(glm::mat4(1.0f), glm::vec3(position[0], 0.0f, position[1]));
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    modelLoc = glGetUniformLocation(currentProgram, "model");
}

void Chunk::draw(){
	
	
	

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	if (!vao || num_vertices == 0) return;
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glBindVertexArray(0);
}

void Chunk::removeBlock(array<int, 3> pos){
	int i = 0;
	int index;
	
	for (Block& block : blocks){
		if (block.position == pos){
			index = i;

		}
		else {

			if (block.position == std::array<int, 3>{pos[0]-1, pos[1], pos[2]} ){
				
				block.setVertexArray(

					{
					(true),
				 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
				 	}
			 );
			block.addToChunkMesh(&vertices);
			}

			if (block.position == std::array<int, 3>{pos[0]+1, pos[1], pos[2]} ){
				block.setVertexArray(

					{
					(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
				 	(true), 
				 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
				 	}
			 );
			block.addToChunkMesh(&vertices);
			}

			if (block.position == std::array<int, 3>{pos[0], pos[1]-1, pos[2]} ){
				block.setVertexArray(

					{
					(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
				 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
				 	(true), 
				 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
				 	}
			 );
			block.addToChunkMesh(&vertices);
			}

			if (block.position == std::array<int, 3>{pos[0], pos[1]+1, pos[2]} ){
				block.setVertexArray(

					{
					(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
				 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
				 	(true), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
				 	}
			 );
			block.addToChunkMesh(&vertices);
			}

			if (block.position == std::array<int, 3>{pos[0], pos[1], pos[2]-1} ){
				block.setVertexArray(

					{
					(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
				 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
				 	(true), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]-1}))
				 	}
			 );
			block.addToChunkMesh(&vertices);
			}

			if (block.position == std::array<int, 3>{pos[0], pos[1], pos[2]+1} ){
				block.setVertexArray(

					{
					(!isBlockAt({block.position[0]+1, block.position[1], block.position[2]})),
				 	(!isBlockAt({block.position[0]-1, block.position[1], block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]+1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1]-1, block.position[2]})), 
				 	(!isBlockAt({block.position[0], block.position[1], block.position[2]+1})), 
				 	(true)
				 	}
			 );
			block.addToChunkMesh(&vertices);

			}


		}
		i += 1;
	}
	blocks.erase(blocks.begin() + index);
	unorderedBlocks.erase(pos);
	unorderedWorldBlocks.erase({pos[0]+position[0], pos[1], pos[2]+position[1]});
	
	vertices.erase(vertices.begin() + i*36, vertices.begin() + 35);
	
	/*vertices.clear();
	for (Block& block : blocks){
			block.addToChunkMesh(&vertices);
	}
	initMesh();*/
}


void Chunk::initMesh(){

    num_vertices = vertices.size() / 8;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //    – 3 floats, offset 0, stride = 8 * sizeof(float)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Chunk::setMeshVertices(){
	num_vertices = vertices.size() / 8;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}


