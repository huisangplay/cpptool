#include <iostream>
#include <curl/curl.h>

// WriteCallback函数，用于从libcurl接收数据
size_t WriteCallback(char *buf, size_t size, size_t nmemb, void *userdata)
{
    std::string *str = static_cast<std::string *>(userdata);
    size_t totalSize = size * nmemb;
    str->append(buf, totalSize);
    return totalSize;
}

int main()
{
    CURL *curl;
    CURLcode res;
    std::string url = "https://www.baidu.com/s?wd=";
    std::string keyword = "libcurl";
    std::string result;

    // 初始化curl
    curl = curl_easy_init();
    if (curl)
    {
        // 设置URL
        curl_easy_setopt(curl, CURLOPT_URL, (url + keyword).c_str());

        // 设置WriteCallback函数
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // 将接收到的数据写入result字符串中
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

        // 执行HTTP请求
        res = curl_easy_perform(curl);

        // 检查是否出错
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // 输出搜索结果
            std::cout << result << std::endl;

            // 查找第一个链接
            std::string::size_type pos = result.find("<a href=\"/link?url=");
            if (pos != std::string::npos)
            {
                // 提取链接URL
                std::size_t start = pos + 16;
                std::size_t end = result.find_first_of('"', start);
                std::string link = result.substr(start, end - start);

                // 访问链接
                curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
                res = curl_easy_perform(curl);

                // 检查是否出错
                if (res != CURLE_OK)
                {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                }
                else
                {
                    // 输出链接内容
                    std::cout << result << std::endl;
                }
            }
        }

        // 清理curl
        curl_easy_cleanup(curl);
    }

    return 0;
}