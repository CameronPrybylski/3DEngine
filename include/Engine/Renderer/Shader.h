#pragma once

#include<glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<unordered_map>

std::string get_file_contents(const char* filename);

class Shader
{
private:
	std::unordered_map<const char*, int> uniformLocationsCache;
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(){}
	Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

	// Activates the Shader Program
	void Bind() const;
	// Deactivates the Shader Program
	void Unbind();
	// Deletes the Shader Program
	void Delete();

	int getUniformLocation(const char* uniformName);
	void setUniform4f(const char* uniformName, float v0, float v1, float v2, float v3);
	void setUniform1i(const char* uniformName, int value);
	void setUniform1iv(const char* uniformName, int numOfInd);
	void setUniformMat4f(const char* uniformName, const glm::mat4& matrix);
};