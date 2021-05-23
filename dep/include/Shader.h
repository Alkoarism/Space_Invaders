#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <string>

class Shader {
public:
	unsigned int ID;

	Shader(const char* shaderPath);

	void use();

	//utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void getInt(const std::string& name, int& value) const;
	void getFloat(const std::string& name, float& value) const;

private:
	void fileRead(const std::string fileName, std::string shaderCode, 
		const std::string start, const std::string end);
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif