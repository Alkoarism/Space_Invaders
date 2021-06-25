#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include <utility>

class VAO {
public:
	//Other constructors as normal

	//Free up the object
	~VAO() { Release(); }

	//Delete the copy constructor/assignment
	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;

	VAO(VAO&& other) :obj_(other.obj_) {
		other.obj_ = 0; //Use "null" VAO for the old object
	}
	VAO& operator=(VAO&& other) {
		//ALWAYS check for self-assignment
		if (this != &other) {
			Release();
			//obj_ is now 0
			std::swap(obj_, other.obj_);
		}
	}

private:
	GLuint obj_ = 0; //Cannot leave this uninitialized

	void Release() {
		glDeleteVertexArrays(1, &obj_);
		obj_ = 0;
	}
};

#endif