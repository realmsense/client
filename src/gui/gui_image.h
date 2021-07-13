#pragma once

#include <string>
#include <d3d11.h>

class GuiImage
{
public:
    GuiImage(std::string file_name);
    GuiImage(unsigned char* bytes, int bytes_len);

    ID3D11ShaderResourceView* load();

    std::string file_name;
    unsigned char* bytes;
    int bytes_len;

    bool init;
    bool failed;
    int width;
    int height;
    ID3D11ShaderResourceView* texture;
private:
    void loadTexture(unsigned char* image_data, ID3D11ShaderResourceView*& out_srv, int image_width, int image_height);
    bool loadFromFile(const char* filename, ID3D11ShaderResourceView*& out_srv, int& image_width, int& image_height);
    void loadFromMemory(unsigned char* bytes, int len, ID3D11ShaderResourceView*& out_srv, int& image_width, int& image_height);
};