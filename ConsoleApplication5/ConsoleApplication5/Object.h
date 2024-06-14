#ifndef OBJECT_H
#define OBJECT_H

#include <GLFW/glfw3.h>

class Player {
public:
    Player(float posX, float posY, float size); // 생성자
    void draw(); // 플레이어를 그리는 함수

private:
    float posX_; // X 좌표
    float posY_; // Y 좌표
    float size_; // 플레이어 크기
};

#endif // OBJECT_H