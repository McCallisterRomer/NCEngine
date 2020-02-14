#ifndef RENDERING_SYSTEM
#define RENDERING_SYSTEM

#include <vector>
#include <windows.h>
#include "Transform.h"


struct RenderBuffer
{
    //Pixels are 32-bit | Mem Order: BB GG RR XX | Little Endian: XX RR GG BB
    BITMAPINFO info; //windows.h is included just for this, change?
    void *memory;    //should use smart pointer here just because
    int width;
    int height;
    int bytesPerRow;
};

class RenderingSystem
{
    private:
        RenderBuffer m_buffer;
        void (*CopyBufferToScreen)(void*, BITMAPINFO&, int, int);

        void AllocateRenderBuffer(int width, int height);
        void RenderTileMap();
        void RenderSprites(const std::vector<Transform> &transforms);
        int GetTileMapValueAtCoordinates(int x, int y, int tileWidth);

    public:
        RenderingSystem(void (*displayBuffer)(void*, BITMAPINFO&, int, int), int initialWidth, int initialHeight);
        void StartRenderCycle(const std::vector<Transform> &transforms);
        void ForceRender();
};

#endif