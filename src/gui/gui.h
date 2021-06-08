#pragma once

#include <d3d11.h>

extern HWND g_hWindow;
extern ID3D11Device* g_pDevice;

void GUI_WrapInLoop(int i, int length);

bool InitGui();
void RemoveGui();