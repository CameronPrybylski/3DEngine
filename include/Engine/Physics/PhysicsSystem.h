#pragma once

//#include <Engine/Scene/GameObject.h>
#include <Engine/Physics/PhysicsBody.h>

class PhysicsSystem {

public:
    PhysicsSystem();
    ~PhysicsSystem();

    void Init(glm::vec3 gravity);
    void SetGravity(glm::vec3 gravity){this->gravity = gravity;}
    std::vector<CollisionEvent> Update(float dt);
    void Integrate(Transform& objectTransform, RigidBodyComponent& objectRigidBody, float dt);
    bool CheckCollision(PhysicsBody& physBod1, PhysicsBody& physBod2);
    std::vector<std::pair<PhysicsBody, PhysicsBody>> BroadPhaseCollision();
    void ResolveCollision(PhysicsBody& physBod1, PhysicsBody& physBod2);
    glm::vec2 GetCollisionNormal(PhysicsBody& physBod1, PhysicsBody& physBod2);//, RigidBodyComponent& object2RigidBody);
    void RegisterBody(Transform& transform, RigidBodyComponent& rigidBody, std::string id);
    void ClearBodies(){physicsBodies.clear();}
    //void SetMinMaxX(float minX, float maxX){this->minX = minX; this->maxX = maxX;}
    glm::vec2 ProjectOBB(const OBB& obb, glm::vec3 axis);

private:
    glm::vec3 gravity;
    std::vector<PhysicsBody> physicsBodies;
    float leftScreenEdge;
    float rightScreenEdge;
    float topScreenEdge;
    float bottomScreenEdge;
    //glm::vec3 drg
    float dt;
};