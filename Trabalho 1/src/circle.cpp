#include <circle.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLuint circle::_indices[6] = {
    0, 1, 3, 1, 2, 3
};

circle::circle(GLfloat center[2], GLfloat radius, const GLfloat (&color)[3]) :
    _radius(radius),
    _vertices {
        center[0] - radius, center[1] - radius,
        center[0] + radius, center[1] - radius,
        center[0] + radius, center[1] + radius,
        center[0] - radius, center[1] + radius,
    } {
    _center[0] = center[0];
    _center[1] = center[1];
    _color[0] = color[0]; _color[1] = color[1]; _color[2] = color[2];
    
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // select this VAO
    glBindVertexArray(VAO);

    // select this vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // send vertices to GPu
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);  

    // select this EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // send indices to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
}

circle::~circle()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void circle::draw(shaderProg& shader)
{
    shader.use();
    glUniform2fv(glGetUniformLocation(shader(), "center"), 1, _center);
    glUniform1f(glGetUniformLocation(shader(), "radius"), _radius);
    glUniform3fv(glGetUniformLocation(shader(), "fColor"), 1, _color);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}