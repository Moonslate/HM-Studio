#pragma once

#include <vector>

#include <wx/msgdlg.h>

#include "class_rom_file.hpp"
#include "class_finder.hpp"

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Color(const uint8_t& r, const uint8_t& g, const uint8_t& b)
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

	uint32_t GetRGB() const { return (red << 16) | (green << 8) | blue; }
	uint32_t GetBGR() const { return (blue << 16) |(green << 8) | red; }

	bool operator==(const Color other)
	{
		if (red != other.red)
			return false;
		if (green != other.green)
			return false;
		if (blue != other.blue)
			return false;

		return true;
	}
};

struct Palette {
	Color* m_Colors = nullptr;
	uint8_t m_Count = 0;

	Palette(uint16_t* colors, uint8_t bpp);
	Palette(const Palette& palette)
	{
		SetCount(palette.m_Count);
		memcpy(m_Colors, palette.m_Colors, m_Count*sizeof(Color));
	}
	Palette() = default;

	~Palette() { delete[] m_Colors; }

	void DecodeColors(uint16_t* colors, uint8_t bpp);

	void SetColor(const int& index, const uint8_t& red, const uint8_t& green, const uint8_t& blue)
	{
		m_Colors[index] = Color(red, green, blue);
	}

	const Color& operator[](const int& index) const
	{
		return m_Colors[index];
	}

	//size_t FindRGB(uint32_t rgb) const;
	size_t FindColor(const Color& c) const;

	uint8_t GetCount() const { return m_Count; }

	void SetCount(uint8_t count);
};

class Graphics
{
public:
	Graphics(uint32_t width, uint32_t height, uint8_t bpp = 4, bool reversed = true, bool planar = false);	
	Graphics(const Graphics& graphics);
	Graphics() = default;
	~Graphics();
private:		
	uint8_t* m_pRawData = nullptr;
	uint8_t m_PixelsPerByte;
	uint8_t m_Mask;
	uint8_t m_Bpp;
	bool m_Reversed = false;
	bool m_Planar = false;		
	uint32_t m_Width;
	uint32_t m_Height;
public:
	size_t GetWidth() const { return m_Width; }
	size_t GetHeight() const { return m_Height; }
	size_t GetLenght() const { return (m_Width*m_Height)/m_PixelsPerByte; }
	uint8_t GetBpp() const { return m_Bpp; }
	bool IsPlanar() const { return m_Planar; }
	bool IsReversed() const { return m_Reversed; }
	uint8_t GetPixel(size_t n) const;
	uint8_t GetPixel(size_t x, size_t y) const;
	const uint8_t* GetData() const { return m_pRawData; }
	uint8_t* GetData() { return m_pRawData; }

	void SetPixel(size_t n, uint8_t p);
	void SetPixel(size_t x, size_t y, uint8_t p);

	void SetWidth(uint32_t width);
	void SetHeight(uint32_t height);	
	void SetBpp(uint8_t bpp);
	void SetPlanar(bool planar);
	void SetReversed(bool reversed);		
	void SetData(uint8_t* data) { m_pRawData = data; }	
	void Create(uint32_t width, uint32_t height, uint8_t bpp = 4, bool reversed = true, bool planar = false);	

	//Blit a Graphics at x and y coordinates
	void Blit(const Graphics& other, const uint32_t& x, const uint32_t& y);
	//Blit a tile (8x8 Graphics) at tile-x*8 and tile-y*8 coordinates
	//This is faster than Blit.
	void BlitTile(const Graphics& tile, const uint32_t& tile_x, const uint32_t& tile_y);
public:
	//Compare two Graphics. This compare the palette index, so assume both use
	//same palette and the palette don't have duplicated colors.
	//Bpp difference don't necessary means that Graphics are not equal.
	bool operator==(const Graphics& graphics) const
	{
		if(GetWidth() != graphics.GetWidth())		
			return false;

		if(GetHeight() != graphics.GetHeight())
			return false;

		if(GetBpp() == graphics.GetBpp())
		{
			return memcmp(GetData(), graphics.GetData(), GetLenght()) == 0;
		} else 
		{
			//ToDo:
			//Pixel to pixel comparison
		}
	}

	void operator=(const Graphics& other)
	{
		SetBpp(other.GetBpp());

		if(!other.GetData())
			return;

		uint32_t lenght = GetLenght();

		m_pRawData = new uint8_t[lenght];

		memcpy(m_pRawData, other.GetData(), GetLenght());
	}
};