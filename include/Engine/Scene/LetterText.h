#pragma once

#include <Engine/Scene/GameObject.h>
#include <Engine/Renderer/TextTexture.h>


class LetterText : public GameObject 
{
public:
    LetterText(glm::vec4 color, std::string fontPath, std::string text);
    ~LetterText();

    void Render(Renderer& renderer, const Camera& camera) override;
    
    std::string GetText() const 
    {
        return text;
    }

    glm::vec3 GetPosition(){return transform.position;}

    void SetPosition(glm::vec3 position){this->transform.position = position;}
    void SetScale(glm::vec3 scale){this->transform.scale = scale;}

    //void ChangeText(std::string newText);

    std::string GetFontPath(){return fontPath;}

    glm::vec3 GetColor(){return color;}

    std::string GetText(){return text;}

private:
    TextTexture textTexture;
    std::string text;
    std::string fontPath;

};

