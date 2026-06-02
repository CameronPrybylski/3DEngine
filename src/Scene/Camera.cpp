#include <Engine/Scene/Camera.h>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    projMinX = minX;
    projMaxX = maxX;
    projMinY = minY;
    projMaxY = maxY;
    SetPerspectiveProjMat(minX, maxX, minY, maxY, minZ, maxZ);
    SetVP();
}

void Camera::Create(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float distanceFromPlayer, glm::vec3 objPosition)
{
    projMinX = minX;
    projMaxX = maxX;
    projMinY = minY;
    projMaxY = maxY;
    viewPosition = {0.0f, 0.0f, 5.0f};
    viewRotation = {0.0f, 0.0f, 0.0f};
    view = glm::mat4(1.0f);
    this->distanceFromPlayer = distanceFromPlayer;
    angleAroundPlayer = 0.0f;
    SetPerspectiveProjMat(minX, maxX, minY, maxY, minZ, maxZ);
    SetCamera(objPosition);
}

void Camera::SetViewMatrix()
{
    view = glm::mat4(1.0f);
    view = glm::translate(view, viewPosition);
    view = glm::rotate(view, glm::radians(viewRotation.x), glm::vec3(1,0,0));
    view = glm::rotate(view, glm::radians(viewRotation.y), glm::vec3(0,1,0));
    view = glm::rotate(view, glm::radians(viewRotation.z), glm::vec3(0,0,1));
    view = glm::inverse(view);
}

void Camera::OnUpdate(const glm::vec3& positionChange)
{
    viewPosition += positionChange;
    SetViewMatrix();
    SetVP();
}

void Camera::SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    projection = glm::ortho(minX, maxX, minY, maxY,  minZ, maxZ);
}

void Camera::SetPerspectiveProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    float screenWidth = maxX - minX;
    float screenHeight = maxY - minY;
    float aspectRatio = screenWidth / screenHeight;
    projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 3000.0f);
}

void Camera::SetVP()
{
    vp = projection * GetViewMatrix();
}

void Camera::SetCamera(glm::vec3 objPosition)
{
    // Position the camera far away on Z, and centered on the cube's X and Y
    cameraPos   = glm::vec3(objPosition.x, objPosition.y, objPosition.z + distanceFromPlayer); 
    // Look directly at the center of your cube
    cameraTarget = objPosition; 
    //The upwards direction vector of your world, which determines camera roll aka y is up 
    cameraUp     = glm::vec3(0.0f, 1.0f, 0.0f);

    // Overwrite your view matrix with a lookAt matrix
    view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    // Re-calculate your View-Projection matrix combo
    vp = projection * view; 
}

void Camera::Update(glm::vec3 objPosition, float xOffset, float yOffset, float changeInDistance)
{
    //The upwards direction vector of your world, which determines camera roll aka y is up 
    cameraUp     = glm::vec3(0.0f, 1.0f, 0.0f);

    this->distanceFromPlayer += changeInDistance;
    pitch += yOffset;
    angleAroundPlayer += xOffset;
    yaw = 90 - angleAroundPlayer;

    // Constrain pitch to avoid flipping
    if(pitch > 89.0f)  pitch = 89.0f;
    if(pitch < -10.0f) pitch = -10.0f;

    // 4. Calculate the new Front vector
    /*
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraFront = glm::normalize(front);
    */

    float verticalDist   = distanceFromPlayer * sin(glm::radians(pitch));
    float horizontalDist = distanceFromPlayer * cos(glm::radians(pitch));

    float newX = horizontalDist * sin(glm::radians(angleAroundPlayer));
    float newZ = horizontalDist * cos(glm::radians(angleAroundPlayer));
    
    cameraPos = glm::vec3(objPosition.x - newX, objPosition.y + verticalDist, objPosition.z - newZ);

    cameraTarget = objPosition + glm::vec3(0.0f, 100.0f, 0.0f);  //cameraPos + cameraFront;

    // Overwrite your view matrix with a lookAt matrix
    view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    // Re-calculate your View-Projection matrix combo
    vp = projection * view; 
}