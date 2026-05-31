#include <Engine/Renderer/Shader.h>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw std::runtime_error(std::string("Failed to open file: ") + filename);

}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
    GLint compiled;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        std::cerr << "[Vertex Shader Compile Error]:\n" << infoLog << std::endl;
    }



	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        std::cerr << "[Fragment Shader Compile Error]:\n" << infoLog << std::endl;
    }


	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "[Shader Program Linking Error]:\n" << infoLog << std::endl;
    }

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

// Activates the Shader Program
void Shader::Bind() const
{
	glUseProgram(ID);
    
}

void Shader::Unbind(){
	glUseProgram(0);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

int Shader::getUniformLocation(const char* uniformName){
	if(uniformLocationsCache.find(uniformName) != uniformLocationsCache.end()){
		return uniformLocationsCache[uniformName];
	}
	int location = glGetUniformLocation(ID, uniformName);
	uniformLocationsCache[uniformName] = location;
	return location;
}

void Shader::setUniform1i(const char* uniformName, int value){
	int uniformLoc = getUniformLocation(uniformName);
	glUniform1i(uniformLoc, value);
}

void Shader::setUniform1iv(const char* uniformName, int numOfInd)
{
	int vTex[numOfInd];
	for(int i = 0; i < numOfInd; ++i)
	{
		vTex[i] = i;
	}
	int uniformLoc = getUniformLocation(uniformName);
	glUniform1iv(uniformLoc, numOfInd, vTex);
}

void Shader::setUniform4f(const char* uniformName, float v0, float v1, float v2, float v3){
	int uniformLoc = getUniformLocation(uniformName);
	glUniform4f(uniformLoc, v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const char* uniformName, const glm::mat4& matrix){
	int uniformLoc = getUniformLocation(uniformName);
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &matrix[0][0]);
}