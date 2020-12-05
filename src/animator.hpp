#pragma once

#include <vector>
#include <ctype.h>

#include "animation.hpp"
#include "class_graphics.hpp"

struct AnimRange
{
    uint16_t length;
    uint16_t start;
};

struct AnimInstruction
{
    uint16_t frame;
    uint16_t time;
};

struct AnimAff
{
    uint16_t data[4];
};

struct FrameInfo
{
    AnimRange oam;
    AnimRange tile;
    AnimRange color;
    AnimRange affine;
};

struct SpriteAttribute
{
    uint16_t attributes[3];
private:
    uint16_t unused;
public:
	uint16_t GetX()
    {
		return 0x1FF & attributes[1];
    }

	uint8_t GetY()
    {
		return 0xFF & attributes[0];
    }

	uint16_t GetTile()
    {
		return 0x3FF & attributes[2];
    }

	uint8_t GetPalette()
    {
		return 0xF & (attributes[2] >> 12);
    }

	uint8_t GetShape()
    {
		return 0x3 & (attributes[0] >> 14);
    }

	uint8_t GetSize()
    {
		return 0x3 & (attributes[1] >> 14);
    }	
};

class Animator
{
private:
    uint16_t m_FrameCount = 0;
    uint32_t m_OldSize = 0;

    std::vector<AnimAff> m_Affines;
    std::vector<Palette> m_Palettes;
    std::vector<Graphics> m_Tiles;
    std::vector<Graphics> m_Frames;
    std::vector<FrameInfo> m_FrameInfos;
    std::vector<Animation> m_Animations;
    std::vector<AnimRange> m_AnimRanges;
    std::vector<SpriteAttribute> m_Attributes;
    std::vector<AnimInstruction> m_Instructions;
public:
    void LoadFromRom(RomFile& rom, uint32_t offset);
    void GenerateFrames();

    Graphics& GetFrame(size_t n) { return m_Frames[n]; }
    std::vector<Graphics>& GetFrames() { return m_Frames; }
    FrameInfo& GetFrameInfo(size_t n) { return m_FrameInfos[n]; }

    size_t GetTileCount() { return m_Tiles.size(); }
    Graphics& GetTile(size_t n) { return m_Tiles[n]; }    
    std::vector<Graphics>& GetTiles() { return m_Tiles; } 

    Palette& GetPalette(size_t n) { return m_Palettes[n]; }

    void SetRange(size_t n, const AnimRange& range) { m_AnimRanges[n] = range; }
    AnimRange GetAnimRange(size_t n) { return m_AnimRanges[n]; }
    std::vector<AnimRange>& GetAnimRanges() { return m_AnimRanges; }
    size_t GetAnimCount() { return m_AnimRanges.size(); }

    void SetInstruction(size_t n, const AnimInstruction& instruction) { m_Instructions[n] = instruction; }
    AnimInstruction GetInstruction(size_t n) { return m_Instructions[n]; }
    std::vector<AnimInstruction>& GetInstructions() { return m_Instructions; }

    void WriteToRom(RomFile& file, const uint32_t& offset);
public:
    Animation& operator[](size_t n)
    {
        return m_Animations[n];
    }
};