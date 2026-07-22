#include <Engine/Scene/GameObject.h>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
    
}

void GameObject::OnEvent(const Input& input)
{
    
}

void GameObject::Update(float dt)
{
    
}

void GameObject::Update(const Input& input, float dt)
{
    transform.position = hitBox.position;
    oldPos = transform.position;
    transform.position += renderPosOffset;
    oldScale = transform.scale;
    transform.scale /= scaleMulti;
}

void GameObject::Render(Renderer &renderer, const Camera& camera)
{
    transform.position = oldPos;
    transform.scale = oldScale;
}
