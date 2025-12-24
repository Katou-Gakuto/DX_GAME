// 初期テスト
/*
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>

//#include "XmlArrange.h"

namespace fs = std::experimental::filesystem;

// 指定の拡張子のファイルを取得
std::string FileRxtension_Search(std::string folderPath, std::string fileRxtension)
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

int main()
{
    // フォルダ名取得
    /*
        // 調べたいフォルダのパス
    std::string folderPath = "./";

    // ディレクトリが存在するか確認
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "指定されたパスは存在しないか、ディレクトリではありません。        ";
        return 1;
    }

    std::cout << folderPath << " 内のフォルダ一覧:";

    // ディレクトリ内を走査
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_directory(entry.path())) {  // ディレクトリのみ表示
            std::cout << entry.path().filename().string() << "            ";
        }
    }

    return 0;* /

    // ファイル名取得
    / ** /
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
            return 0;
        }
        folderPath = folderPath + "../";
    }

    std::cout << FileRxtension_Search(folderPath + "x64/Debug/", projectName + ".xml") << std::endl;


    return 0;
}

#undef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
*/

// TODO: 本来のコード
/**/
#include "XmlArrange.h"

int main()
{
    XmlArrange* xmlArrange = new XmlArrange();

    xmlArrange->Arrange();

    delete xmlArrange;

    return 0;
}
/**/

// ファイル座標取得テスト
/**
#include <iostream>

void log_message(const std::string& message, const std::string& file, int line) {
    std::cout << "Error in file: " << file << ", line: " << line << " - Message: " << message << std::endl;
}

int main() {
    // ここでマクロを使用する
    log_message("Something happened", __FILE__, __LINE__);

    // ... 他のコード ...

    return 0;
}
/**/