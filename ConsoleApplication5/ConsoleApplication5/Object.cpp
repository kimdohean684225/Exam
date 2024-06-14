#include "Object.h"

Player::Player(float posX, float posY, float size)
    : posX_(posX), posY_(posY), size_(size)
{
    // 생성자에서는 초기화가 필요한 경우 초기화 작업을 수행합니다.
}

void Player::draw()
{
    // 플레이어를 그리는 코드 추가
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색 설정
    glLineWidth(3.0f); // 선 두께 설정

    glBegin(GL_LINE_LOOP); // 빨간색 테두리를 그리는 코드
    glVertex2f(posX_, posY_);
    glVertex2f(posX_ + size_, posY_);
    glVertex2f(posX_ + size_, posY_ + size_);
    glVertex2f(posX_, posY_ + size_);
    glEnd();
}