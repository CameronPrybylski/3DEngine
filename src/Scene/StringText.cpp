#include <Engine/Scene/StringText.h>

#include <set>

std::string StringText::lowerLetters = "abcdefghijklmnopqrstuvwxyz";
std::string StringText::upperLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//A=26

StringText::StringText(std::string letters, glm::vec3 position, glm::vec4 color, std::string fontPath, int fontSize)
{
    for(int i = 0; i < letters.length(); i++)
    {
        std::string s;
        s = letters[i];
        this->letters.push_back(std::make_shared<LetterText>(color, fontPath, s));
    }
    this->transform.position = position;
    this->fontSize = fontSize;
    this->fontPath = fontPath;
    this->color = color;
    this->text = letters;
}

void StringText::Init()
{
    SetTextSizeAndPos();
}

void StringText::Render(Renderer &renderer, const Camera &camera)
{
    for(int i = 0; i < letters.size(); i++)
    {
        letters[i]->Render(renderer, camera);
    }
}

void StringText::SetTextSizeAndPos()
{
    glm::vec3 ogPosition = this->transform.position;

    for(int i = 0; i < letters.size(); i++)
    {
        SetLetterTextSizeAndPos(letters[i]);
        this->transform.position.x += letters[i]->transform.scale.x;
    }

    this->endPosition = this->transform.position;
    this->transform.position = ogPosition;
}

void StringText::SetLetterTextSizeAndPos(std::shared_ptr<LetterText> letter)
{
    std::set<std::string> shrinkHalfLetters = {"I", " ", "i", "l", ":", ".", "!"};
    std::set<std::string> shrinkThreeQLetters = {"t", "f"};
    letter->SetPosition(this->transform.position);
    letter->SetScale(glm::vec3(float(fontSize), float(fontSize)*2, 0.0f));
    if(shrinkHalfLetters.find(letter->GetText()) != shrinkHalfLetters.end())
    {
        letter->transform.scale.x /= 2;
        letter->SetPosition(this->transform.position - glm::vec3{letter->transform.scale.x / 2, 0.0f, 0.0f});
    }
    else if(shrinkThreeQLetters.find(letter->GetText()) != shrinkThreeQLetters.end())
    {
        letter->transform.scale.x *= 0.75f;
        letter->SetPosition(this->transform.position - glm::vec3{letter->transform.scale.x / 6, 0.0f, 0.0f});
    }
    else if(letter->GetText() == "m" || letter->GetText() == "M" || letter->GetText() == "w")
    {
        letter->transform.scale.x *= 1.5f;
        letter->SetPosition(this->transform.position + glm::vec3{letter->transform.scale.x * 0.15f, 0.0f, 0.0f});
    }
    else if(letter->GetText() == "G" || letter->GetText() == "N")
    {
        letter->transform.scale.x *= 1.15f;
        letter->SetPosition(this->transform.position + glm::vec3{letter->transform.scale.x * 0.05f, 0.0f, 0.0f});
    }
}

void StringText::ChangeText(std::string newLetters)
{
    letters.clear();
    for(int i = 0; i < newLetters.length(); i++)
    {
        std::string s;
        s = newLetters[i];
        this->letters.push_back(std::make_shared<LetterText>(color, fontPath, s));
    }
    this->text = newLetters;
    SetTextSizeAndPos();
}