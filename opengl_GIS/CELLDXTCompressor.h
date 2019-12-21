
#pragma once

#include <Windows.h>

namespace DXTC
{
    // DXT compressor (scalar version).
    void CompressImageDXT1(const BYTE* inBuf, BYTE* outBuf, int width, int height);
    void CompressImageDXT5(const BYTE* inBuf, BYTE* outBuf, int width, int height, unsigned int rowPitch = 0);
    WORD ColorTo565(const BYTE* color);
    void EmitByte(BYTE*& dest, BYTE b);
    void EmitWord(BYTE*& dest, WORD s);
    void EmitDoubleWord(BYTE*& dest, DWORD i);
    void ExtractBlock(const BYTE* inPtr, int width, BYTE* colorBlock);
    void GetMinMaxColors(const BYTE* colorBlock, BYTE* minColor, BYTE* maxColor);
    void GetMinMaxColorsWithAlpha(const BYTE* colorBlock, BYTE* minColor, BYTE* maxColor);
    void EmitColorIndices(const BYTE* colorBlock, BYTE*& outBuf, const BYTE* minColor, const BYTE* maxColor);
    void EmitAlphaIndices(const BYTE* colorBlock,  BYTE*& outBuf, const BYTE minAlpha, const BYTE maxAlpha);

    void CompressImageDXT1SSE2(const BYTE* inBuf, BYTE* outBuf, int width, int height);
    void CompressImageDXT5SSE2(const BYTE* inBuf, BYTE* outBuf, int width, int height, unsigned int rowPitch = 0);
    void ExtractBlock_SSE2(const BYTE* inPtr, int width, BYTE* colorBlock);
    void GetMinMaxColors_SSE2(const BYTE* colorBlock, BYTE* minColor, BYTE* maxColor);
    void EmitColorIndices_SSE2(const BYTE* colorBlock, BYTE*& outBuf, const BYTE* minColor, const BYTE* maxColor);
    void EmitAlphaIndices_SSE2(const BYTE* colorBlock, BYTE*& outBuf, const BYTE minAlpha, const BYTE maxAlpha);
}