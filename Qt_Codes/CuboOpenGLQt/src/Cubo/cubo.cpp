#include "cubo.hpp"

Cubo::~Cubo() {
    if (m_program) {
        delete m_program;
        m_program = nullptr;
    }
}

void Cubo::initialize() {
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       fragmentShaderSource);
    m_program->link();

    m_matrixUniform = m_program->uniformLocation("matrix");
    m_posAttr = m_program->attributeLocation("position");
    m_colAttr = m_program->attributeLocation("color");

    m_frame = 0.f;
}

void Cubo::render() {
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -5);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 1, 1, 1);

    m_program->setUniformValue(m_matrixUniform, matrix);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          vertices.data() + 3);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                   indices.data());

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    m_frame += 0.5f;
}
