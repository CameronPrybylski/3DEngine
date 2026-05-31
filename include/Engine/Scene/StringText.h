#pragma once

#include <Engine/Scene/LetterText.h>

class StringText : public GameObject 
{
public:
    StringText(std::string letters, glm::vec3 position, glm::vec4 color, std::string fontPath, int fontSize);

    void Render(Renderer& renderer, const Camera& camera) override;
    
    virtual void SetTextSizeAndPos();

    void SetLetterTextSizeAndPos(std::shared_ptr<LetterText> letter);

    virtual void Init();

    virtual void ChangeText(std::string newLetters);

    int GetFontSize(){return fontSize;}

    glm::vec3 GetEndPosition(){return endPosition;}

    std::vector<std::shared_ptr<LetterText>> GetLetters(){return letters;}

    std::string GetFontPath(){return fontPath;}

    std::string GetText(){return this->text;}

protected:
    std::vector<std::shared_ptr<LetterText>> letters;
    int fontSize;
    std::string fontPath;
    static std::string lowerLetters;
    static std::string upperLetters;
    glm::vec3 endPosition;
    std::string text;

};