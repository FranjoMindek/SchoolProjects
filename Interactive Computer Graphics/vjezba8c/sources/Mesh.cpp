//
// Created by mindek on 31. 03. 2022..
//
#define STB_IMAGE_IMPLEMENTATION

#include "Mesh.h"

#include <stb_image.h>
#include <glm/gtx/string_cast.hpp>

Mesh::Mesh(std::string const& dir, std::string const& name) : Mesh(){
    Assimp::Importer importer;
    std::string obj = dir+name+".obj";
    std::string mtl = dir+name+".mtl";
    aiScene const* scene = importer.ReadFile(obj,
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

    if (scene->HasMaterials()) {
        for (int i = 0; i < scene->mNumMaterials; i++) {

            aiString naziv;
            scene->mMaterials[i]->Get(AI_MATKEY_NAME, naziv);
            std::cout <<  "[" << i << "]" << naziv.C_Str() << std::endl;

            aiString texturePosition;

            int width, height, nrChannels;
            unsigned char *data;
            if (AI_SUCCESS == scene->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texturePosition)) {

                std::string tex_path(dir);
                tex_path.append(texturePosition.C_Str());
                data = stbi_load(tex_path.c_str(), &width, &height, &nrChannels, 0);
            }
//            std::cout << *data << std::endl;

//            glm::vec3 ambientColor;
            aiColor3D ambientK, diffuseK, specularK;
            glm::vec3 ambient, diffuse, specular;

            scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, ambientK);
            ambient.r = ambientK.r;
            ambient.g = ambientK.g;
            ambient.b = ambientK.b;

            scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseK);
            diffuse.r = diffuseK.r;
            diffuse.g = diffuseK.g;
            diffuse.b = diffuseK.b;

            scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, specularK);
            specular.r = specularK.r;
            specular.g = specularK.g;
            specular.b = specularK.b;

            this->mMaterial.AddMaterial(naziv.C_Str(), texturePosition.C_Str(), ambient, diffuse, specular);

        }
    }

//    std::cout << glm::to_string(this->mMaterial.GetAmbient()) << " " << glm::to_string(this->mMaterial.GetDiffuse()) << " " << glm::to_string(this->mMaterial.GetSpecular()) << std::endl;

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

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Mesh::GetAmbient() {
    return this->mMaterial.GetAmbient();
}

glm::vec3 Mesh::GetDiffuse() {
    return this->mMaterial.GetDiffuse();
}

glm::vec3 Mesh::GetSpecular() {
    return this->mMaterial.GetSpecular();
}
