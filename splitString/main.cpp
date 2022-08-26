#include <iostream>
#include <list>
#include <fstream>
#include <chrono>

std::list<std::string> splitString(const std::string &str, const std::string &delim)
{
    if (delim.size() == 0)
        return {str};

    std::list<std::string> result;
    size_t startPosition = 0, findPosition;

    while( (findPosition = str.find(delim, startPosition)) != std::string::npos)
    {
        if (findPosition != startPosition)
            result.push_back(str.substr(startPosition, findPosition - startPosition));

        startPosition = findPosition + delim.size();
    }

    if (result.size() == 0)
        return {str};

    result.push_back(str.substr(startPosition, findPosition - startPosition));

    return result;
}

int main()
{
    std::ifstream file("war_and_piece.txt");
    std::string str = "Hello C++ ! ! !";//( (std::istreambuf_iterator<char>(file) ), (std::istreambuf_iterator<char>()    ) );
//    {
//        int avg = 0;
//        for (int i = 0; i < 1000000; i++)
//        {
//            QString q_str = str.c_str();
//            auto start = std::chrono::system_clock::now();
//            auto list = q_str.split(" ");
//            auto stop = std::chrono::system_clock::now();
//            avg += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
//        }

//        avg /= 10;

//        std::cout << "QString split: " << avg << std::endl;
//    }

    {
        int avg = 0;
        for (int i = 0; i < 1000000; i++)
        {
            auto start = std::chrono::system_clock::now();
            auto list = splitString(str, " ");
            auto stop = std::chrono::system_clock::now();
            avg += std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        }

        avg /= 10;

        std::cout << "std::string split: " << avg << std::endl;
    }


    file.close();
}
