#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <glad/glad.h>

class Table {
public:
    Table(float size);
    ~Table();

    void draw();

private:
    GLuint vao, vbo;
    float tableSize;

    void generateTable();
};

#endif // TABLE_H
