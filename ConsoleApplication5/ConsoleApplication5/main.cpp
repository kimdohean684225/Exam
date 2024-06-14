#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float BACKGROUND_COLOR_R = 0.0f;
const float BACKGROUND_COLOR_G = 30.0f / 255.0f;
const float BACKGROUND_COLOR_B = 100.0f / 255.0f;

const float PLAYER_SIZE = 50.0f; // 플레이어 사각형 한 변의 길이 (단위: cm)
const float PLAYER_BORDER_THICKNESS = 3.0f; // 플레이어 사각형 테두리 두께 (단위: cm)
const float PLAYER_COLOR_R = 255.0f / 255.0f; // 플레이어 색상 (빨강)
const float PLAYER_COLOR_G = 0.0f / 255.0f;
const float PLAYER_COLOR_B = 0.0f / 255.0f;

const float GROUND_Y = 100.0f; // 지면의 높이 (단위: cm)
const float GROUND_COLOR_R = 255.0f / 255.0f; // 지면 색상 (황색)
const float GROUND_COLOR_G = 200.0f / 255.0f;
const float GROUND_COLOR_B = 15.0f / 255.0f;

const float OBSTACLE_WIDTH = 50.0f; // 장애물 너비 (단위: cm)
const float OBSTACLE_COLOR_R = 0.0f / 255.0f; // 장애물 색상 (녹색)
const float OBSTACLE_COLOR_G = 255.0f / 255.0f;
const float OBSTACLE_COLOR_B = 0.0f / 255.0f;

struct Player {
    float posX;
    float posY;

    Player(float x, float y)
        : posX(x), posY(y) {}
};

struct Obstacle {
    float posX;
    float posY;
    float height;

    Obstacle(float x, float y, float h)
        : posX(x), posY(y), height(h) {}
};

Player player(100.0f, GROUND_Y + PLAYER_SIZE); // 플레이어 초기 위치 설정
Obstacle obstacles[] = {
    Obstacle(200.0f, GROUND_Y, 100.0f), // 낮은 장애물
    Obstacle(400.0f, GROUND_Y, 300.0f)  // 높은 장애물
};

GLFWwindow* window; // GLFW 윈도우 객체 선언

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int Initialize()
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // OpenGL 컨텍스트 버전 설정 (OpenGL 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // 추가적인 옵션 설정 (Core Profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

void DrawPlayer()
{
    glColor3f(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B); // 플레이어 색상 설정
    glLineWidth(PLAYER_BORDER_THICKNESS);

    glBegin(GL_LINE_LOOP);
    glVertex2f(player.posX, player.posY);
    glVertex2f(player.posX + PLAYER_SIZE, player.posY);
    glVertex2f(player.posX + PLAYER_SIZE, player.posY + PLAYER_SIZE);
    glVertex2f(player.posX, player.posY + PLAYER_SIZE);
    glEnd();
}

void DrawGround()
{
    glColor3f(GROUND_COLOR_R, GROUND_COLOR_G, GROUND_COLOR_B); // 지면 색상 설정

    glBegin(GL_QUADS);
    glVertex2f(0.0f, GROUND_Y);
    glVertex2f(WINDOW_WIDTH, GROUND_Y);
    glVertex2f(WINDOW_WIDTH, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
}

void DrawObstacles()
{
    glColor3f(OBSTACLE_COLOR_R, OBSTACLE_COLOR_G, OBSTACLE_COLOR_B); // 장애물 색상 설정

    for (const auto& obstacle : obstacles) {
        glBegin(GL_QUADS);
        glVertex2f(obstacle.posX, obstacle.posY);
        glVertex2f(obstacle.posX + OBSTACLE_WIDTH, obstacle.posY);
        glVertex2f(obstacle.posX + OBSTACLE_WIDTH, obstacle.posY + obstacle.height);
        glVertex2f(obstacle.posX, obstacle.posY + obstacle.height);
        glEnd();
    }
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawGround();
    DrawObstacles();
    DrawPlayer();

    glfwSwapBuffers(window);
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 초기화 및 창 생성
    if (Initialize() != 0)
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Google Dino Run Copy Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트를 현재 스레드에 연결
    glfwMakeContextCurrent(window);

    // 오류 콜백 함수 설정
    glfwSetErrorCallback(errorCallback);

    // 키보드 입력 콜백 함수 설정
    glfwSetKeyCallback(window, keyCallback);

    // OpenGL 초기화
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, 1.0f);

    // 렌더링 루프
    while (!glfwWindowShouldClose(window))
    {
        // 이벤트 처리
        glfwPollEvents();

        // 렌더링 함수 호출
        Render();
    }

    // GLFW 정리
    glfwTerminate();
    return 0;
}