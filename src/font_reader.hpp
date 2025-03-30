#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
#include <core/vmath.hpp>
#include <vector>
#include <iostream>
#include <fstream>

class FontReader {
public:
	FontReader(const std::string& fontPath, float pixelHeight) {
		std::ifstream file(fontPath, std::ios::binary | std::ios::ate);
		if (!file) {
			throw std::runtime_error("Failed to open font file!");
		}

		size_t size = file.tellg();
		file.seekg(0, std::ios::beg);
		fontBuffer.resize(size);
		file.read(reinterpret_cast<char*>(fontBuffer.data()), size);
		file.close();

		if (!stbtt_InitFont(&font, fontBuffer.data(), 0)) {
			throw std::runtime_error("Failed to initialize font!");
		}

		scale = stbtt_ScaleForPixelHeight(&font, pixelHeight);
	}

	std::vector<vmath::vec2> getGlyphPoints(char glyphChar) const {
		std::vector<vmath::vec2> points;
		int glyphIndex = stbtt_FindGlyphIndex(&font, glyphChar);
		if (glyphIndex == 0) {
			std::cerr << "Glyph not found!" << std::endl;
			return points;
		}

		stbtt_vertex* vertices;
		int numVerts = stbtt_GetGlyphShape(&font, glyphIndex, &vertices);

		int ascent, descent, lineGap;
		stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
		float baseline = ascent * scale; 

		for (int i = 0; i < numVerts; ++i) {
			points.push_back({
				vertices[i].x * scale,
				baseline - (vertices[i].y * scale) // Flip Y
			});
		}

		stbtt_FreeShape(&font, vertices);
		return points;
	}

private:
	stbtt_fontinfo font;
	std::vector<unsigned char> fontBuffer;
	float scale;
};
