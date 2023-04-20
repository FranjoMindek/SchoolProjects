//
// Created by mindek on 31. 03. 2022..
//
#define STB_IMAGE_IMPLEMENTATION

#include "Mesh.h"

#include <stb_image.h>

Mesh::Mesh(std::string const& filename) : Mesh(){
    Assimp::Importer importer;
    aiScene const* scene = importer.ReadFile(filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene){
        std::cerr << importer.GetErrorString();
        return;
    }

    if (scene->HasMeshes()){
        aiMesh* mesh = scene->mMeshes[0];
        Vertex vertex{};
        bool firstPass;
        for (unsigned int i = 0; i < mesh->mNumVertices; i++){
            if (mesh->HasTextureCoords(0)){
                vertex.uv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals()){
                vertex.normal   = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }
            if(firstPass){
                firstPass = !firstPass;
                mMinMax.x[0] = vertex.position.x;
                mMinMax.x[1] = vertex.position.x;
                mMinMax.y[0] = vertex.position.y;
                mMinMax.y[1] = vertex.position.y;
                mMinMax.z[0] = vertex.position.z;
                mMinMax.z[1] = vertex.position.z;
            }else{
                if(mMinMax.x[0] > vertex.position.x)
                    mMinMax.x[0] = vertex.position.x;
                if(mMinMax.x[1] < vertex.position.x)
                    mMinMax.x[1] = vertex.position.x;
                if(mMinMax.y[0] > vertex.position.y)
                    mMinMax.y[0] = vertex.position.y;
                if(mMinMax.y[1] < vertex.position.y)
                    mMinMax.y[1] = vertex.position.y;
                if(mMinMax.z[0] > vertex.position.z)
                    mMinMax.z[0] = vertex.position.z;
                if(mMinMax.z[1] < vertex.position.z)
                    mMinMax.z[1] = vertex.position.z;
            }
//            std::cout << vertex.position.x << " ";
            mVertices.push_back(vertex);
        }
//        std::cout << std::endl;
//        std::cout << mMinMax.x[0] << " " << mMinMax.x[1] << std::endl;
        mMinMax.means.x = (mMinMax.x[0] + mMinMax.x[1])/2.0f;
        mMinMax.means.y = (mMinMax.y[0] + mMinMax.y[1])/2.0f;
        mMinMax.means.z = (mMinMax.z[0] + mMinMax.z[1])/2.0f;
        mMinMax.maxMean = std::max(mMinMax.x[1]-mMinMax.x[0], mMinMax.y[1]-mMinMax.y[0]);
        mMinMax.maxMean = std::max(mMinMax.maxMean, mMinMax.z[1]-mMinMax.z[0]);

        for (unsigned int i = 0; i < mesh->mNumFaces; i++){
            for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++){
                mIndices.push_back(mesh->mFaces[i].mIndices[j]);
            }
        }
    }
//    for(auto x : mVertices){
//        std::cout << x.position.x << " " << x.position.y << " " <<x.position.z << " " << std::endl;
//    }
//    for (auto x : mIndices){
//        std::cout << x << std::endl;
//    }

    setupBuffers();
}

void Mesh::setupBuffers(){
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, uv));
    glEnableVertexAttribArray(0); // Vertex Positions
    glEnableVertexAttribArray(1); // Vertex Normals
    glEnableVertexAttribArray(2); // Vertex UVs

    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}
