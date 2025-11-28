#pragma once
#include <string>

class XmlArrange
{
public:
    XmlArrange();
    ~XmlArrange();

    // xmlファイルを読み込み用に整理する
    void Arrange(std::string fileName = "");

private:
    // 指定の拡張子のファイルを取得
    std::string FileRxtension_Search(std::string folderPath, std::string fileRxtension);
};