#include "Object.h"

Player::Player(float posX, float posY, float size)
    : posX_(posX), posY_(posY), size_(size)
{
    // �����ڿ����� �ʱ�ȭ�� �ʿ��� ��� �ʱ�ȭ �۾��� �����մϴ�.
}

void Player::draw()
{
    // �÷��̾ �׸��� �ڵ� �߰�
    glColor3f(1.0f, 0.0f, 0.0f); // ������ ����
    glLineWidth(3.0f); // �� �β� ����

    glBegin(GL_LINE_LOOP); // ������ �׵θ��� �׸��� �ڵ�
    glVertex2f(posX_, posY_);
    glVertex2f(posX_ + size_, posY_);
    glVertex2f(posX_ + size_, posY_ + size_);
    glVertex2f(posX_, posY_ + size_);
    glEnd();
}