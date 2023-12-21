attribute vec3 position;
attribute vec3 color;
varying vec3 fragColor;
uniform mat4 matrix;

void main() {
    gl_Position = matrix * vec4(position, 1.0);
    fragColor = color;
}
