#ifndef CIRCLE_HPP
#define CIRCLE_HPP

// std headers
#include <array>

// 3rd-party headers
#include <glad/glad.h>
#include <glm/glm.hpp>

// my headers
#include <shader.hpp>

class circle {
private:
    GLfloat _center[2];
    GLfloat _radius;
    GLfloat _color[3];
    GLfloat _vertices[8];
    GLuint VAO, VBO, EBO;
    
    const static GLuint _indices[6];
public:

    circle(const GLfloat (&center)[2], GLfloat radius, const GLfloat (&color)[3]);
    ~circle();

    void draw(shaderProg& shader);
};

#endif // CIRCLE_HPP