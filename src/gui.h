#pragma once

#include <d3d11.h>

bool InitGui();
void RemoveGui();

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

struct Image
{
    Image(std::string file_name);
    ID3D11ShaderResourceView* Load();

    std::string file_name;
    bool init;
    int width;
    int height;
    ID3D11ShaderResourceView* texture;
};
