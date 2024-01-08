#include "Table.h"
#include <iostream>

Table::Table(float size) : tableSize(size) {
    generateTable();
}

Table::~Table() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Table::generateTable() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    // Vertices for a simple quad (table)
    float vertices[] = {
        -tableSize / 2, 0.0f, -tableSize / 2,
         tableSize / 2, 0.0f, -tableSize / 2,
         tableSize / 2, 0.0f,  tableSize / 2,
        -tableSize / 2, 0.0f,  tableSize / 2,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Table::draw() {
    glBindVertexArray(vao);
    glDrawArrays(GL_QUADS, 0, 4);
    glBindVertexArray(0);
}
