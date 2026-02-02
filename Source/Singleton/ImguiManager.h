#pragma once

#if _DEBUG
class ImguiManager
{
public:
    ImguiManager();
    ~ImguiManager();

    /// <summary>‰Šú‰»</summary>
    void Initilize();
    /// <summary>I—¹</summary>
    void Finalize();

    /// <summary>XV</summary>
    void Update();
    /// <summary>•`‰æ</summary>
    void Draw();
};
#endif