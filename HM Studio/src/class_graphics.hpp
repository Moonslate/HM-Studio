#pragma once

#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Color(const uint8_t r, const uint8_t g, const uint8_t b)
	{
		red = r;
		green = g;
		blue = b;
	}

	Color()
	{
		red = 00;
		green = 00;
		blue = 00;
	}

	Color& operator=(const Color color)
	{
		memcpy(this, &color, 3);

		return *this;
	}
};

struct Palette {
	Color* colors = nullptr;

	Palette()
	{
		colors = new Color[256];
	}

	void SetColor(const int index, const uint8_t red, const uint8_t green, const uint8_t blue)
	{
		colors[index] = Color(red, green, blue);
	}

	Color& operator[](const int index)
	{
		return colors[index];
	}
};

struct Tile {
	Color colors[64];

	Color& operator[](const int index)
	{
		return colors[index];
	}

	Tile& operator=(uint8_t* rawData)
	{
		memcpy(&rawData, rawData, 64 * 3);
		return *this;
	}
};


class Graphics
{
public:
	Graphics(uint8_t* bytes, const uint8_t bpp, const uint32_t width, const uint32_t height, const bool reversed = true, const bool planar = false);
	~Graphics();

private:

public:
	uint8_t m_bpp;
	bool m_reversed = false;
	bool m_planar = false;
	uint32_t m_width;
	uint32_t m_height;

	uint8_t* m_data = nullptr;
	Palette m_pal;
	uint32_t m_palIndex;
public:
	//Returns a 24 bits rgb data	
	void SetPalette(const Palette& palette, const int index);
	void SetPaletteIndex(const int index) { m_palIndex = index; }
public:
	Tile* Decode();
	void DecodePalette(uint8_t* bytes);
	wxImage ToImage();	
};
