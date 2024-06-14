#ifndef OBJECT_H
#define OBJECT_H

#include <GLFW/glfw3.h>

class Player {
public:
    Player(float posX, float posY, float size); // ������
    void draw(); // �÷��̾ �׸��� �Լ�

private:
    float posX_; // X ��ǥ
    float posY_; // Y ��ǥ
    float size_; // �÷��̾� ũ��
};

#endif // OBJECT_H