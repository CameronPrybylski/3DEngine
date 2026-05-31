#include <Engine/Scene/LetterText.h>
#include <Engine/Renderer/TextTexture.h>

LetterText::LetterText(glm::vec4 color, std::string fontPath, std::string text)
{
    this->color = color;
    this->name = name;
    this->text = text;
    this->fontPath = fontPath;

    mesh = AssetManager::GetMesh("quadMesh");

    if(fontPath != ""){
        shaderName = "textureShader";
        textTexture.Create(fontPath, text);
        texture = textTexture;
    }else{
        shaderName = "objectShader";
    }
}

LetterText::~LetterText()
{
}

void LetterText::Render(Renderer &renderer, const Camera &camera)
{
    renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader("textureShader"), texture, color);
}