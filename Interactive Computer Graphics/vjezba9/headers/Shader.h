#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

#include <fstream>
#include <sstream>

class Shader
{
private:
	void checkCompilerErrors(unsigned int shader, std::string type);

public:

	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath="-1");

	~Shader();

	void use();
	void setUniform(const std::string &name, bool value)const;
	void setUniform(const std::string &name, int value)const;
	void setUniform(const std::string &name, float value)const;
    void setUnifrom(const std::string &name, const glm::vec2 &value) const;
    void setUnifrom(const std::string &name, const glm::vec3 &value) const;
    void setUnifrom(const std::string &name, const glm::vec4 &value) const;
    void setUnifrom(const std::string &name, const glm::mat2 &value) const;
    void setUnifrom(const std::string &name, const glm::mat3 &value) const;
    void setUnifrom(const std::string &name, const glm::mat4 &value) const;

};

