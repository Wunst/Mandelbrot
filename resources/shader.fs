#version 450 core

in vec2 c;

out vec4 FragColor;

vec2 cmul(vec2 a, vec2 b) {
    return vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

float cabs(vec2 c) {
    return sqrt(dot(c, c));
}

vec2 cdiv(vec2 a, vec2 b) {
    float f = 1 / dot(b, b);
    return f * vec2(a.x*b.x + a.y*b.y, a.y*b.x - a.x*b.y);
}

vec2 cpow(vec2 c, float p) {
    vec2 result = vec2(1, 0);
    for(int i = 0; i < p; ++i) {
        result = cmul(result, c);
    }
    return result;
}

vec2 cexp(vec2 c) {
    return exp(c.x) * vec2(cos(c.y), sin(c.y));
}

int mandelbrot_iterations_til_escape(vec2 c) {
    vec2 z = vec2(0, 0);
    for(int i = 0; i < 100; ++i) {
        z = cmul(z, z) + c;
        if(cabs(z) > 2.0) return i;
    }
    return 100;
}

vec3 mandelbrot_color(vec2 c) {
    int iterations = mandelbrot_iterations_til_escape(c);
    if(iterations == 100) {
        return vec3(0, 0, 0);
    } else {
        float f = iterations / 100.0f;
        return vec3(cos(f), sin(f), 0);
    }
}

void main() {
    if(c == vec2(0, 0))
        FragColor = vec4(1, 0, 0, 1);
    else
        FragColor = vec4(mandelbrot_color(c), 1);
}
