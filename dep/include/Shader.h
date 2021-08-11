#ifndef SHADER_H
#define SHADER_H

#include "headers.h"

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void Use() const;

	//utility uniform functions
	void SetBool(const std::string&, const bool&) const;
	void SetInt(const std::string&, const int&) const;
	void SetFloat(const std::string&, const float&) const;
	void SetMat4(const std::string&, const glm::mat4&) const;

	void GetInt(const std::string&, int&) const;
	void GetFloat(const std::string&, float&) const;

private:
	void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif