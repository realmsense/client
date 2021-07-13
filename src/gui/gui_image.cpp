#include "pch.h"

#include "gui.h"
#include "gui_image.h"

#include <d3d11.h>
#define STB_IMAGE_IMPLEMENTATION
#include "other/stb_image.h"

GuiImage::GuiImage(std::string file_name)
{
    this->file_name = file_name;
    this->bytes = nullptr;
    this->bytes_len = 0;

    this->init = false;
    this->failed = false;
}

GuiImage::GuiImage(unsigned char* bytes, int bytes_len)
{
    this->file_name = "";
    this->bytes = bytes;
    this->bytes_len = bytes_len;

    this->init = false;
    this->failed = false;
}

ID3D11ShaderResourceView* GuiImage::load()
{
    if (this->failed)
        return nullptr;

    if (this->init)
        return this->texture;

    if (this->file_name != "")
    {
        bool ret = this->loadFromFile(this->file_name.c_str(), this->texture, this->width, this->height);
        if (!ret)
        {
            std::cout << "Failed to load GUI Image: " << this->file_name << std::endl;
            this->failed = true;
            return nullptr;
        }

        this->init = true;
        return this->texture;
    }

    if (this->bytes_len > 0)
    {
        this->loadFromMemory(this->bytes, this->bytes_len, this->texture, this->width, this->height);
        this->init = true;
        return this->texture;
    }

    this->failed = true;
    std::cout << "GUI Image has no file or bytes loaded!" << std::endl;
    return nullptr;
}

void GuiImage::loadTexture(unsigned char* image_data, ID3D11ShaderResourceView*& out_srv, int image_width, int image_height)
{
    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pDevice->CreateShaderResourceView(pTexture, &srvDesc, &out_srv);
    pTexture->Release();
}

bool GuiImage::loadFromFile(const char* filename, ID3D11ShaderResourceView*& out_srv, int& image_width, int& image_height)
{
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    this->loadTexture(image_data, out_srv, image_width, image_height);
    return true;
}

void GuiImage::loadFromMemory(unsigned char* bytes, int len, ID3D11ShaderResourceView*& out_srv, int& image_width, int& image_height)
{
    unsigned char* image_data = stbi_load_from_memory(bytes, len, &image_width, &image_height, nullptr, 4);
    this->loadTexture(image_data, out_srv, image_width, image_height);
}