#include <iostream>
#include <format>
#include <random>
#include <map>
#include <sys/time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  

#include <engine.hpp>
#include <shader.hpp>
#include <circle.hpp>

int generate_random_num(int lower, int upper);

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;

void RenderText(shaderProg &s, std::string text, float x, float y, float scale, glm::vec3 color, GLuint VAO, GLuint VBO)
{
    // activate corresponding render state	
    s.use();
    glUniform3f(glGetUniformLocation(s(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int main() {
	engine eng(1280, 720);
	glfwSetWindowPos(eng(),300,100);
	glfwSwapInterval(1);
	std::cout << glGetString(GL_VERSION) << '\n';

	// compilar e linkar shaders
	shaderProg mainShader{
		{"shaders/circle.vert", GL_VERTEX_SHADER},
		{"shaders/circle.frag", GL_FRAGMENT_SHADER}
	};

	// freetype begin
	shaderProg textShader{
		{"shaders/text.vert", GL_VERTEX_SHADER},
		{"shaders/text.frag", GL_FRAGMENT_SHADER}
	};
	textShader.use();

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
		return -1;
	}

	FT_Set_Pixel_Sizes(face, 0, 30);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture, 
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);      
	// freetype end
	

	// definir matriz de projecao
	glm::mat4 projmat = glm::ortho(-640.f, 640.f, -360.f, 360.f, 0.f, 1.0f);
	mainShader.use();
	GLint projmat_loc = glGetUniformLocation(mainShader(), "projmat");
	glUniformMatrix4fv(projmat_loc, 1, GL_FALSE, glm::value_ptr(projmat));	
	textShader.use();
	projmat_loc = glGetUniformLocation(textShader(), "projection");
	glUniformMatrix4fv(projmat_loc, 1, GL_FALSE, glm::value_ptr(projmat));	

	// definir a cor de fundo como cinza
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	// definir as cores possiveis de serem escolhidas
	const GLfloat colors[4][3] = {
		{1.f, 0.f, 0.f}, // vermelho
		{0.f, 1.f, 0.f}, // verde
		{0.f, 0.f, 1.f}, // azul
		{1.f, 1.f, 0.f}, // amarelo
	};

	// inicializar um circulo novo aleatorio	
	GLfloat center[2] = {
		generate_random_num(-640, 640),
		generate_random_num(-360, 360)
	};
	unsigned char color_index = generate_random_num(0, 3);
	circle* circ = new circle(center, 50.f, colors[color_index]);

	// criar um grande circulo como background
	circle background({0.f, 0.f}, 2000.f, {0.f, 0.f, 0.f});

	// definir structs para medir o tempo de reacao
	timeval start, finish;
	bool pressed = false;
	bool hit = false;
	int score = 0;
	float total = 0;
	int presses = 0;
	std::string print1 = "media: 0 ms";
	std::string print2 = "score: 0/0";
	auto render = [&]() {
		if (pressed) {
			gettimeofday(&finish, nullptr);

			center[0] = generate_random_num(-640, 640); center[1] = generate_random_num(-360, 360);
			color_index = generate_random_num(0, 3);
			delete circ;
			circ = new circle(center, 50.f, colors[color_index]);

			score = hit ? score + 1 : score - 1;
			total = total + (finish.tv_sec - start.tv_sec)*1000.f + (finish.tv_usec - start.tv_usec)/1000.f;
			print1 = std::format("media: {:.2f} ms", total/presses);
			print2 = std::format("score: {}/{}", score, presses);

			start.tv_sec = finish.tv_sec;
			start.tv_usec = finish.tv_usec;

			pressed = false;
			hit = false;
		}

		glClear(GL_COLOR_BUFFER_BIT); // limpar a tela
		background.draw(mainShader);  // desenhar o background


		circ->draw(mainShader);
		RenderText(textShader, "amarelo: W", -630.f, -270.f, 1.f, glm::vec3(1.f, 1.f, 0.f), VAO, VBO);
		RenderText(textShader, "vermelho: A", -630.f, -300.f, 1.f, glm::vec3(1.f, 0.f, 0.f), VAO, VBO);
		RenderText(textShader, "verde: S", -630.f, -330.f, 1.f, glm::vec3(0.f, 1.f, 0.f), VAO, VBO);
		RenderText(textShader, "azul: D", -630.f, -360.f, 1.f, glm::vec3(0.f, 0.f, 1.f), VAO, VBO);
		RenderText(textShader, print1, 300, -330, 1.f, glm::vec3(1.f, 1.f, 1.f), VAO, VBO);
		RenderText(textShader, print2, 300, -300, 1.f, glm::vec3(1.f, 1.f, 1.f), VAO, VBO);
	};

	auto keyPress = [&](int key) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			eng.setWindowShouldClose(true);
			break;
		case GLFW_KEY_W:
			pressed = true;
			presses++;	
			if (color_index == 3) hit = true;
			break;
		case GLFW_KEY_A:
			pressed = true;
			presses++;
			if (color_index == 0) hit = true;
			break;
		case GLFW_KEY_S:
			pressed = true;
			presses++;
			if (color_index == 1) hit = true;
			break;
		case GLFW_KEY_D:
			pressed = true;
			presses++;
			if (color_index == 2) hit = true;
		}
	};

	eng.setRenderFunc(render);
	eng.setKeyPressFunc(keyPress);

	gettimeofday(&start, nullptr);
	eng.mainLoop();

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	delete circ;
	return 0;
}

int generate_random_num(int lower, int upper) {
	static std::mt19937 gen(time(nullptr));
	return gen() % (upper - lower + 1) + lower;
}