#include <iostream>
#include <string>
#include <unordered_map>

class TinyURL
{
    std::unordered_map<std::string, std::string> URLMap;

public:
    void Insert(std::string key_url, std::string value_url)
    {
        URLMap[key_url] = value_url;

        std::cout << "The url, <" << value_url << "> compressed as <"
        << key_url << "> inserted." << std::endl;
    }

    void Search(const std::string url)
    {
        auto iter = URLMap.find(url);

        if(iter == URLMap.end())
            std::cout << "Searching <"<< url << "> failed." << std::endl;

        else std::cout << "Searching <"<< url << "> successed, value = <" 
        << iter->second << ">." << std::endl;
    }
};

int main()
{
    TinyURL TinyURLContainer;

    TinyURLContainer.Insert("blackhand", "www.blackhand.com");
    TinyURLContainer.Search("blackhand");

    TinyURLContainer.Search("_Grammer");
    return 0;
}