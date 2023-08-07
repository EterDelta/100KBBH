#version 330 core

#define GLYPH_OFFSET 0.45

vec2 glyphSize = vec2(16, 16);
vec2 atlasSize = vec2(256, 64);
vec2 resolution = vec2(512, 512);

int creditText[18] = int[](21, 53, 63, 52, 63, 52, -1, 11, -1, 30, 19, 4, 17, 29, 4, 11, 19, 0);
int titleText[7] = int[](53, 52, 52, 36, 27, 27, 33);
int scoreText[6] = int[](44, 2, 14, 17, 4, 62);

uniform bool stopped;
uniform bool booted;
uniform int score[3];
uniform sampler2D atlas;
out vec4 fragColor;

float glyph(vec2 uv, int glyphIndex) {
    vec2 gridSize = atlasSize / glyphSize;
    if (glyphIndex != -1 && uv.x > 0.0 && uv.x < 1.0 && uv.y > 0.0 && uv.y < 1.0) {
        return texture(atlas, vec2(
            uv.x / gridSize.x + fract(float(glyphIndex) / gridSize.x),
            uv.y / gridSize.y + fract((gridSize.y - 1.0 - floor(float(glyphIndex) / gridSize.x)) / gridSize.y)
        )).x;
    } else {
        return 0.0;
    }
}

float fixedOffset(int glyphIndex) {
    if (glyphIndex == 11 || glyphIndex == 63) {
        return GLYPH_OFFSET - 0.26;
    } else {
        return GLYPH_OFFSET;
    }
}

void main() {
    vec2 uv = (gl_FragCoord.xy - resolution.xy * 0.5) / resolution.y;
    vec4 color = vec4(0.0);

    if (stopped) {
        color.w = 0.5;
        if (booted) {
            vec2 textOffset = vec2(0.0);
            float titleScale = 4.0;
            float titleWidth = float(titleText.length()) * GLYPH_OFFSET;

            vec2 tiledUV = uv * glyphSize / titleScale;

            textOffset.x = -(titleWidth / 2.0);

            if (uv.y > 0.0 && uv.y < 0.335) {
                color = vec4(1.0, 0.32, 0.64, 1.0);
            }
            for (int i = 0; i < titleText.length(); i++) {
                int index = titleText[i];
                color += glyph(tiledUV - textOffset, index);
                textOffset.x += GLYPH_OFFSET;
            }
        }
    }
    if (!booted) {
        uv = gl_FragCoord.xy / resolution.y;
        vec2 textOffset = vec2(0.0);
        float scoreScale = 1.5;
        float scoreWidth = float(scoreText.length()) * GLYPH_OFFSET;

        vec2 tiledUV = uv * glyphSize / scoreScale;

        textOffset.x += 0.32;

        for (int i = 0; i < scoreText.length(); i++) {
            int index = scoreText[i];
            color += glyph(tiledUV - textOffset, index);
            textOffset.x += GLYPH_OFFSET;
        }

        textOffset.x = 0;
        textOffset.x += scoreWidth + 0.32;

        for (int i = 0; i < score.length(); i++) {
            int index = score[i];
            color += glyph(tiledUV - textOffset, index);
            textOffset.x += GLYPH_OFFSET;
        }
    } else {
        uv = gl_FragCoord.xy / resolution.y;
        vec2 textOffset = vec2(0.0);

        vec2 tiledUV = uv * glyphSize / 1.0;

        textOffset.x += 0.32;

        for (int i = 0; i < creditText.length(); i++) {
            int index = creditText[i];
            color.xyz += glyph(tiledUV - textOffset, index);
            textOffset.x += fixedOffset(index);
        }
    }
    fragColor = color;
}
