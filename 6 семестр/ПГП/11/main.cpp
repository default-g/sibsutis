#include <iostream>
#include <GLFW/glfw3.h>

void drawSquare()
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glVertex2f(-0.5f, -0.5f);   // Bottom-left corner
    glVertex2f(0.5f, -0.5f);    // Bottom-right corner
    glVertex2f(0.5f, 0.5f);     // Top-right corner
    glVertex2f(-0.5f, 0.5f);    // Top-left corner
    glEnd();
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(300, 200, "My OpenGL Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw the square
        drawSquare();

        // Swap the buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Clean up GLFW
    glfwTerminate();

    return 0;
}