

#include "Inface.network.h"
#include <iostream>

void progress(int current, int total)
{
    float percent = (float)current / total;
    std::cout << "progress: " << current << "/" << total << " " << percent * 100 << "%" << std::endl;
}

int main()
{
    std::string url = "https://download.weixitianli.com/d/TianLiUpdateService_Local/cvAutoTrack/cvAutoTrack-7.12.2.zip";
    std::string path = "./cvAutoTrack-7.12.2.zip";
    if (download_file(url, path, progress))
    {
        std::cout << "download success" << std::endl;
    }
    else
    {
        std::cout << "download failed" << std::endl;
    }
    return 0;
}