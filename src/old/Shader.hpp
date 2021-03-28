#pragma once

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);

    ~Shader();

    void use() const;

    void setBool(const char* name, bool value) const;

    void setInt(const char* name, bool value) const;

    void setFloat(const char* name, float value) const;

  private:
    unsigned int id;

    static void checkCompileError(unsigned int id);

    static void checkLinkingError(unsigned int id);
};
