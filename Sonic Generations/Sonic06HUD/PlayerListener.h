#pragma once

class PlayerListener
{
public:
    static void** const CSonicContext;

    static bool IsContextSafe();
    static const uint32_t GetContext();
    static float* GetBoost();
};