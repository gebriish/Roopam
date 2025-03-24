#pragma once

namespace Rpm {

struct Shader {
	unsigned int Id;
};

constexpr Shader INVALID_SHADER = Shader { 0 };

void shaderLoadGlslFromSource(Shader& shader, const char* vertexSource, const char* fragmentSource);
void shaderLoadGlsl(Shader& shader, const char* vertexPath, const char* fragmentPath);

void shaderUseProgram(const Shader& shader);
void shaderDeleteProgram(const Shader& shader);

void shaderUploadInt(const Shader& program, const char* name, int v);
void shaderUploadIntArray(const Shader& program, const char* name, int* v, int size);
void shaderUploadFloat(const Shader& program, const char* name, float v);
void shaderUploadFloat2(const Shader& program, const char* name, float x, float y);
void shaderUploadFloat3(const Shader& program, const char* name, float x, float y, float z);
void shaderUploadFloat4(const Shader& program, const char* name, float x, float y, float z, float w);
void shaderUploadFloatArray(const Shader& program, const char* name, const float* array, int size);
void shaderUploadMat4(const Shader& program, const char* name, const float* mat);

}

