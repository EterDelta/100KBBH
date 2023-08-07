#version 330 core

#define LAYER_AMOUNT 6.0
#define LAYER_POPULATION 0.2

vec3 backColor = vec3(1.0, 0.69, 0.50);
vec3 accentColor = vec3(1.0, 0.92, 0.69);
vec2 resolution = vec2(512, 512);

uniform float time;
out vec4 fragColor;

float random(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float diamond(vec2 uv, float width, float height) {
    float diamondShape = 0.2 - (abs(uv.x) / width + abs(uv.y) / height);
    float diamond = step(0.001, diamondShape);
    return diamond;
}

vec3 diamondLayer(vec2 uv, int tiles) {
    uv *= float(tiles);

    vec3 color = vec3(0.0);
    vec2 tiledUV = fract(uv) - 0.5;
    vec2 tileID = floor(uv);

    float tileRandom = random(tileID);
    float tileRandom2 = fract(tileRandom * 345.32);

    if (tileRandom2 > 1.0 - LAYER_POPULATION) {
        float diamond = diamond(tiledUV, 0.6 + tileRandom * 1.2, 0.6 + tileRandom * 1.2);
        color += diamond * accentColor;
    }
    return color;
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;
    vec3 color = backColor;
    float time = time * 0.25;

    for (float i = 0.0; i < 1.0; i += 1.0 / LAYER_AMOUNT) {
        float layerDepth = fract(i) + 1.0 / LAYER_AMOUNT;
        float layerScale = mix(5.0, 0.5, i);
        uv.y += time;
        color += diamondLayer(uv * layerScale, 2) * layerDepth;
    }
    fragColor = vec4(color, 1.0);
}
