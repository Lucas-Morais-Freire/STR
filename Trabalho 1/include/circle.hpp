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
    glm::vec2 _center;
    GLfloat _radius;
    glm::vec3 _color;
    GLfloat _vertices[8];
    GLuint _indices[6]; 
    GLuint VAO, VBO, EBO;
public:

    circle(glm::vec2 center = glm::vec2(0, 0), GLfloat radius = 1.f, glm::vec3 color = glm::vec3(0,0,0));
    ~circle();

    void draw(shaderProg& shader);
};

#endif // CIRCLE_HPP