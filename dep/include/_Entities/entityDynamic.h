#ifndef ENTITYDYNAMIC_H
#define ENTITYDYNAMIC_H

#include "entity.h"

class EntityDynamic : public Entity {
public:
	EntityDynamic() : Entity() { }
	EntityDynamic(glm::vec2 pos, glm::vec2 size,
		glm::vec3 color = glm::vec3(1.0f)) : Entity(pos, size, color) { }
	virtual ~EntityDynamic() = default;

	virtual glm::vec2 Move(float dt, float screen_size) = 0;
private:

};

#endif