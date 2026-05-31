#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};

    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1,0,0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));
        model = glm::scale(model, scale);
        return model;
    }
    
    bool operator==(const Transform& other) const {
        return this->GetModelMatrix() == other.GetModelMatrix();
    }
};

struct RigidBodyComponent{
    glm::vec3 velocity;
    glm::vec3 previousPosition;
    float mass = 10.0f;
    bool isStatic = true;
};