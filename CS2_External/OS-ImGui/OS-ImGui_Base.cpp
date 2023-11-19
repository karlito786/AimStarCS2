﻿#include "OS-ImGui_Base.h"
#include "..\Font\fontArray.h"
#include "..\Font\IconsFontAwesome5.h"
#include "..\Sources\WeaponIcon.h"
#include "..\Sources\Language.h"

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_Base.cpp
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/6/18	11:21
****************************************************/

namespace OSImGui
{
    bool OSImGui_Base::InitImGui(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontDefault();
        (void)io;

        ImFontAtlas* fontAtlas = new ImFontAtlas();
        ImFontConfig arialConfig;
        arialConfig.FontDataOwnedByAtlas = false;
        ImFont* arialFont = fontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 16.0f, &arialConfig, io.Fonts->GetGlyphRangesAll());
        
        ImFontConfig iconConfig;
        static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        iconConfig.MergeMode = true;
        iconConfig.PixelSnapH = true;
        iconConfig.OversampleH = 3;
        iconConfig.OversampleV = 3;
        iconConfig.GlyphRanges = iconRanges;
        iconConfig.FontDataOwnedByAtlas = false;
        ImFont* iconFont = fontAtlas->AddFontFromMemoryTTF((void*)faData, sizeof(faData), 16.f, &iconConfig, iconRanges);

        ImFontConfig WeaponFontConfig;
        static const ImWchar WeaponCharRanges[] = { 0xE000, 0xE226, 0xE031, 0xE031 };
        WeaponFontConfig.MergeMode = true;
        WeaponFontConfig.PixelSnapH = false;
        WeaponFontConfig.OversampleH = 5;
        WeaponFontConfig.OversampleV = 5;
        WeaponFontConfig.RasterizerMultiply = 1.2f;
        iconConfig.FontDataOwnedByAtlas = false;
        ImFont* WeaponIconFont = fontAtlas->AddFontFromMemoryTTF((void*)cs_icon, sizeof(cs_icon), 25.0f, &WeaponFontConfig, WeaponCharRanges);

        io.Fonts = fontAtlas;

        ImGui::StyleColorsEnemyMouse();
        io.LogFilename = nullptr;

        if (!ImGui_ImplWin32_Init(Window.hWnd))
            throw OSException("ImGui_ImplWin32_Init() call failed.");
        if (!ImGui_ImplDX11_Init(device, device_context))
            throw OSException("ImGui_ImplDX11_Init() call failed.");

        // Language initialize
        Lang::English();

        return true;
    }

    void OSImGui_Base::CleanImGui()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        g_Device.CleanupDeviceD3D();
        DestroyWindow(Window.hWnd);
        UnregisterClassA(Window.ClassName.c_str(), Window.hInstance);
    }

    std::wstring OSImGui_Base::StringToWstring(std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }
}