#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(){}
    Camera(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    
    void Create(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float distanceFromPlayer, glm::vec3 objPosition);
    void SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    void SetPerspectiveProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    void SetVP();

    void SetPosition(const glm::vec3& position){viewPosition = position;}
    const glm::vec3& GetPosition(){return viewPosition;}

    void SetRotation(const glm::vec3& rotation){viewRotation = rotation;}
    const glm::vec3& GetRotation(){return viewRotation;}

    void SetViewMatrix();

    const glm::mat4& GetViewMatrix() const {return view;}
    const glm::mat4& GetViewProjectionMatrix() const {return vp;}

    float GetProjMinX() const {return projMinX;}
    float GetProjMaxX() const {return projMaxX;}
    float GetProjMinY() const {return projMinY;}
    float GetProjMaxY() const {return projMaxY;}

    void OnUpdate(const glm::vec3& positionChange);

    void SetCamera(glm::vec3 objPosition);
    void Update(glm::vec3 objPosition, glm::vec3 objRotation, float xOffset = 0.0f, float yOffset = 0.0f, float changeInDistance = 0.0f);
    void UpdateDistanceFromPlayer(float distance){this->distanceFromPlayer += distance;}

    float GetZAway(){return this->zAway;}
    void SetZAway(float zAway){this->zAway = zAway;}

    float GetAngleAroundPlayer(){return this->angleAroundPlayer;}


    glm::vec3 GetPos(){return this->cameraPos;}

private:
    glm::vec3 viewPosition{0.0f};
    glm::vec3 viewRotation{0.0f};
    glm::mat4 projection;
    glm::mat4 view{1.0f};
    glm::mat4 vp;
    float projMinX;
    float projMaxX;
    float projMinY;
    float projMaxY;

    float zAway;
    float angle = 0.0f;
    float yaw = 90.0f;
    float pitch = 0.0f;

    float distanceFromPlayer;
    float angleAroundPlayer;

    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUp;
};