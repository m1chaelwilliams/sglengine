#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <fstream>

std::string read_file_contents(const char* filename);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(800, 600, "First App", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glm::vec3 vertices[] = {
        glm::vec3{-0.5f, -0.5f, 0.0f},
        glm::vec3{0.0f, 0.5f, 0.0f},
        glm::vec3{0.5f, -0.5f, 0.0f}
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    GLuint shader_program = glCreateProgram();
    
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    

    const char* source_conv = read_file_contents("default.vert").c_str();
    glShaderSource(vert_shader, 1, &source_conv, nullptr);
    glCompileShader(vert_shader);

    const char* frag_conv = read_file_contents("default.frag").c_str();
    glShaderSource(frag_shader, 1, &frag_conv, nullptr);
    glCompileShader(frag_shader);

    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);

    glLinkProgram(shader_program);

    glDetachShader(shader_program, vert_shader);
    glDetachShader(shader_program, frag_shader);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    
    glUseProgram(shader_program);

    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
 
        glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
 
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader_program);
 
    glfwTerminate();
    return 0;
}

std::string read_file_contents(const char* filename) {
    std::ifstream stream(filename);
    std::string source;

    if (stream.is_open()) {
        std::string line;
        while (std::getline(stream, line)) {
            source += line + "\n";
        }
    } else {
        std::cout << "Failed to open file " << filename << std::endl;
    }

    return source;
}

