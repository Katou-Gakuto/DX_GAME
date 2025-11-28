#include <iostream>
#include <string>

#include "XmlArrange.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

XmlArrange::XmlArrange()
{
}
XmlArrange::~XmlArrange()
{
}

// xmlファイルを読み込み用に整理する
void XmlArrange::Arrange(std::string fileName)
{
    std::string folderPath = "./"; // 取得したいフォルダパス    
    std::string projectName = "";// 取得したプロジェクトファイル名
   
    // プロジェクト名取得
    projectName = FileRxtension_Search(folderPath, ".vcxproj.filters");
    projectName = projectName.substr(0, projectName.size() - 16);

    int max = 10;
    for (int count = 0; count < max; count++)
    {
        if (FileRxtension_Search(folderPath, ".sln") != "")
        {
            break;
        }
        else if ((count + 1) >= max)
        {
            return;
        }
        folderPath = folderPath + "../";
    }

    std::cout << FileRxtension_Search(folderPath + "x64/Debug/", projectName + ".xml") << std::endl;
}

// 指定の拡張子のファイルを取得
std::string XmlArrange::FileRxtension_Search(std::string folderPath, std::string fileRxtension)
{
   try {
       // フォルダが存在するか確認
       if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
           std::cout << "指定されたフォルダは存在しません。" << std::endl;
           return "";
       }

       // ディレクトリを走査
       for (const auto& entry : fs::directory_iterator(folderPath)) {
           if (fs::is_regular_file(entry.status())) { // 通常ファイルのみ
               std::string forTemporaryStorage_File = entry.path().filename().string();
               if ((forTemporaryStorage_File.size() >= fileRxtension.size()) && forTemporaryStorage_File.substr(forTemporaryStorage_File.size() - fileRxtension.size(), fileRxtension.size()) == fileRxtension)
               {
                   return forTemporaryStorage_File;
               }
           }
       }
   }
   catch (const fs::filesystem_error& e) {
       std::cerr << "エラー: " << e.what() << std::endl;
   }

   return "";
}

#undef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING