#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include <cmath>

#define PI 3.14

using namespace glm;

float duration = 0.02f;
float prev = glfwGetTime();
float time;
float post = 0;
bool clockwise = false;
float jarakBumiX = 30.5;
float jarakBumiY = 0.0;

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
        jarakBumiX--; // lengthen bumi distance
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        jarakBumiX++; // shorten bumi distance
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        jarakBumiX = 30.5; // reset bumi distance
}

void displacement()
{
    time = glfwGetTime();

    if ((time - prev) >= duration)
    {
        if (clockwise == false)
        {
            if (post < 359)
                post++;
            else
                post = 0;
            prev = time;
        }
        else if (clockwise == true)
        {
            if (post > -359)
                post--;
            else
                post = 0;
            prev = time;

        }
    }
}

void lingkaran(float radius, int degree)
{
    glBegin(GL_POLYGON);
    int sudut, i;
    mat4 trans(1.0f);
    for (i = 0; i <= degree; i++)
    {
        float sudut = i * (2 * PI / 360);
        float x = (radius)*cos(sudut);
        float y = (radius)*sin(sudut);
        vec4 point(x, y, 0.0f, 1.0f);
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void segitga(float xstart, float ystart, float alas, float tinggi)
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

void matahari()
{
    glColor3ub(255, 255, 0);
    lingkaran(10.5, 360);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    segitga(0, 11.5, 5, 7);
    glRotatef(30, 0.0f, 0.0f, 1.0f);


    glLoadIdentity();
}

void bumi(float x, float y)
{
    vec4 point(x, y, 0.0f, 1.0f);
    mat4 trans(1.0f);
    trans = rotate(trans, radians(post), vec3(0.0f, 0.0f, 1.0f));
    point = trans * point;
    glTranslatef(point.x, point.y, 0.0f);
    glColor3ub(0, 0, 255);
    lingkaran(5, 360);
}

void bulan()
{
    vec4 point(8.5, 0.0f, 0.0f, 1.0f);
    mat4 trans(1.0f);
    trans = rotate(trans, radians(post * 4), vec3(0.0f, 0.0f, 1.0f));
    point = trans * point;
    glTranslatef(point.x, point.y, 0.0f);
    glColor3ub(100, 100, 100);
    lingkaran(1.5, 360);
}

void display()
{
    displacement();
    matahari();
    bumi(jarakBumiX, jarakBumiY);
    bulan();
}

int main() {
    GLFWwindow* window;
    if (!glfwInit())
        return EXIT_FAILURE;

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
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
