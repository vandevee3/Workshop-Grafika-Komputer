#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include <cmath>
using namespace glm;

float duration = 0.02f;
float prev_time = glfwGetTime();
float time;
float dt;
float pos = 0;
float newAngle = 0;
bool clockwise = false;
float earth_distancex = 34.5;
float earth_distancey = 0.0;

void setup_viewport(GLFWwindow* window)
{
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-60, 60, -60, 60, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE); // close program on ESC key
    else if (key == GLFW_KEY_UP&& action == GLFW_PRESS)
        clockwise = false; // rotate counter clock wise
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        clockwise = true; // rotate clock wise
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        earth_distancex--; // lengthen earth distance
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        earth_distancex++; // shorten earth distance
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        earth_distancex = 30.5; // reset earth distance
}

void changePos()
{
    time = glfwGetTime();

    if ((time - prev_time) >= duration)
    {
        if (clockwise == false)
        {
            if (pos < 359)
                pos++;
            else
                pos = 0;
            prev_time = time;
        }
        else if (clockwise == true)
        {
            if (pos > -359)
                pos--;
            else
                pos = 0;
            prev_time = time;

        }
    }
}

void circle(float radius, int degree)
{
    glBegin(GL_POLYGON);
    int sudut, i;
    mat4 trans(1.0f);
    for (i = 0; i <= degree; i++)
    {
        float sudut = i * (2 * M_PI / 360);
        float x = (radius)*cos(sudut);
        float y = (radius)*sin(sudut);
        vec4 point(x, y, 0.0f, 1.0f);
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void triangle(float xstart, float ystart, float alas, float tinggi)
{
    glBegin(GL_TRIANGLES);

    vec4 a((-0.5 * alas) + xstart, 0.0f + ystart, 0.0f, 1.0f);
    vec4 b((0.5 * alas) + xstart, 0.0f + ystart, 0.0f, 1.0f);
    vec4 c(0 + xstart, tinggi + ystart, 0.0f, 1.0f);

    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);

    glEnd();
}

void sun()
{
    glColor3ub(255, 255, 0);
    circle(10.5, 360);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);
    triangle(0, 11.5, 5, 7);
    glRotatef(36, 0.0f, 0.0f, 1.0f);

    glLoadIdentity();
}

void earth(float x, float y)
{
    vec4 point(x, y, 0.0f, 1.0f);
    mat4 trans(1.0f);
    trans = rotate(trans, radians(pos), vec3(0.0f, 0.0f, 1.0f));
    point = trans * point;
    glTranslatef(point.x, point.y, 0.0f);
    glColor3ub(0, 0, 255);
    circle(5, 360);
}

void moon()
{
    vec4 point(8.5, 0.0f, 0.0f, 1.0f);
    mat4 trans(1.0f);
    trans = rotate(trans, radians(pos * 2), vec3(0.0f, 0.0f, 1.0f));
    point = trans * point;
    glTranslatef(point.x, point.y, 0.0f);
    glColor3ub(100, 100, 100);
    circle(1.5, 360);
}

void display(int count)
{
    changePos();
    sun();
    earth(earth_distancex, earth_distancey);
    moon();
}

int main() {
    GLFWwindow* window;
    if (!glfwInit())
        return EXIT_FAILURE;

    // Membuat window
    window = glfwCreateWindow(640, 480, "Matahari, bumi, dan bulan", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    //Enable Antialiasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    while (!glfwWindowShouldClose(window))
    {
        setup_viewport(window);
        display(12);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
