/*
    Copyright 2010 Etay Meiri
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    Tutorial 02 - Hello dot!
*/

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //обратно привязываем наш буфер, приготавливая его для отрисовки
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //вызов говорит конвейеру как воспринимать данные внутри буфера

    glDrawArrays(GL_POINTS, 0, 1); //функцию для отрисовки

    glDisableVertexAttribArray(0); //отключение каждого атрибута вершины

    glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[1]; //массив из одного экземпляра
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f); //задается точка в середине экрана

    glGenBuffers(1, &VBO); //генерация объектов переменных типов
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Параметр GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //После связывания нашего объекта, мы наполняем его данными
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 02");

    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit(); // инициализируем GLEW и проверяем на ошибки
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

    glutMainLoop();

    return 0;
}