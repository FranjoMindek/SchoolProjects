//
// Created by mindek on 16. 05. 2022..
//
#include "Curve.h"
#include <glm/gtx/string_cast.hpp>
#include <bits/stdc++.h>

Curve::Curve(Shader* shader){
    this->shader_ = shader;
    glGenVertexArrays(3, this->VAO_);
    glGenBuffers(3, this->VBO_);
    this->inversion_matrix_4_ = glm::inverse(glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                                            1.0f, 1.0f*19/27, 1.0f*7/27, 1.0f*1/27,
                                                            1.0f, 1.0f*26/27, 1.0f*20/27, 1.0f*8/27,
                                                            1.0f, 1.0f, 1.0f, 1.0f));
//    std::cout << glm::to_string(this->inversion_matrix_4_) << std::endl;
}

int Curve::BinomialCoefficient(const int n, const int k) {
    if (k == 0 or k == n)
        return 1;

    std::vector<int> aSolutions(k);
    aSolutions[0] = n - k + 1;

    for (int i = 1; i < k; ++i) {
        aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
    }

//    for(int i = 0; i<k; i++){
//        std::cout << aSolutions[i] << " ";
//    }
//    std::cout << std::endl;

    return aSolutions[k - 1];
}

Curve::~Curve() {
    for(int i=0; i<3; i++){
        glDeleteVertexArrays(1, &this->VAO_[i]);
        glDeleteBuffers(1, &this->VBO_[i]);
    }
}

void Curve::AddVertex(glm::vec3 vertex) {
    this->vertices_.push_back(vertex);



    int vertices = this->vertices_.size();
    if(vertices > 2){
        int max_vertices = 10*vertices;
        this->approximation_vertices_.clear();
        for(int i=0; i<max_vertices; i++){
            if(i==0){
                this->approximation_vertices_.push_back(this->vertices_[0]);
                continue;
            }else if(i == max_vertices-1){
                this->approximation_vertices_.push_back(this->vertices_[vertices-1]);
                continue;
            }
            float t = 1.0f * i / max_vertices;
            float s = 1-t;
            glm::vec3 temp(0,0,0);
            for(int j=0; j<vertices; j++){
//                std::cout << this->BinomialCoefficient(vertices-1, j) << " ";
                temp = temp + this->vertices_[j] * powf(t, j) * powf(s, vertices-j-1) * (float)this->BinomialCoefficient(vertices-1, j);
            }
    //        std::cout << glm::to_string(temp) << std::endl;
            this->approximation_vertices_.push_back(temp);
        }

        this->interpolation_vertices_vectors_.clear();
        this->interpolation_vertices_.clear();
        if(vertices>3){
            for(int i=0; i<4; i++){
                glm::vec3 temp(0,0,0);
                for (int j=0; j<4; j++){
                    temp = temp + this->inversion_matrix_4_[i][j] * this->vertices_[vertices-4+j];
                }
                this->interpolation_vertices_vectors_.push_back(temp);
            }
            for(int i=0; i<max_vertices; i++){
                if(i==0){
                    this->interpolation_vertices_.push_back(this->vertices_[vertices-4]);
                    continue;
                }else if(i == max_vertices-1){
                    this->interpolation_vertices_.push_back(this->vertices_[vertices-1]);
                    continue;
                }
                float t = 1.0f * i / max_vertices;
                glm::vec3 temp = this->interpolation_vertices_vectors_[0] + (3*t - 3*t*t + t*t*t)*this->interpolation_vertices_vectors_[1]
                                + (3*t*t - 2*t*t*t)*this->interpolation_vertices_vectors_[2] + t*t*t*this->interpolation_vertices_vectors_[3];

                //        std::cout << glm::to_string(temp) << std::endl;
                this->interpolation_vertices_.push_back(temp);
            }
        }
    }
//    auto temp = new std::vector<glm::vec3>(10*vertices_.size());
//    this->approximation_vertices_ = new std::vector<glm::vec3>(10*vertices_.size())

    glBindVertexArray(this->VAO_[0]);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_[0]);

    glBufferData(GL_ARRAY_BUFFER, this->vertices_.size()*sizeof(glm::vec3), &this->vertices_.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindVertexArray(this->VAO_[1]);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_[1]);

    glBufferData(GL_ARRAY_BUFFER, this->approximation_vertices_.size()*sizeof(glm::vec3), &this->approximation_vertices_.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindVertexArray(this->VAO_[2]);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_[2]);

    glBufferData(GL_ARRAY_BUFFER, this->interpolation_vertices_.size() * sizeof(glm::vec3), &this->interpolation_vertices_.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    for(auto& dot : vertices_){
//        std::cout << glm::to_string(dot) << " ";
//    }
//    std::cout << std::endl;
//
//    for(auto& dot : approximation_vertices_){
//        std::cout << glm::to_string(dot) << " ";
//    }
//    std::cout << std::endl;
//
//    for(auto& dot : interpolation_vertices_vectors_){
//        std::cout << glm::to_string(dot) << " ";
//    }
//    std::cout << std::endl;
}

void Curve::Draw() {
    this->shader_->setUnifrom("boja", glm::vec3(0.0f,0.0f,0.0f));
    glBindVertexArray(this->VAO_[0]);
    glDrawArrays(GL_LINE_STRIP, 0, (int) this->vertices_.size());
    this->shader_->setUnifrom("boja", glm::vec3(1.0f,0.0f,0.8f));
    glBindVertexArray(this->VAO_[1]);
    glDrawArrays(GL_LINE_STRIP, 0, (int) this->approximation_vertices_.size());
    this->shader_->setUnifrom("boja", glm::vec3(0.0f,0.7f,0.9f));
    glBindVertexArray(this->VAO_[2]);
    glDrawArrays(GL_LINE_STRIP, 0, (int) this->interpolation_vertices_.size());
    glBindVertexArray(0);

}

