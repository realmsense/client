#pragma once

#include <string>
#include <d3d11.h>

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

class GuiImage
{
public:
    GuiImage(std::string file_name);
    ID3D11ShaderResourceView* load();

    std::string file_name;
    bool init;
    bool failed;
    int width;
    int height;
    ID3D11ShaderResourceView* texture;
};