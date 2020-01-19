#include "IpFilter.h"
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

void IpFilter::setIpPool()
{
    for (std::string line; std::getline(std::cin, line);)
    {
        if (line == "end")
            break;
        std::vector<std::string> v = split(line, '\t');
        std::vector<std::string> ipString = split(v.at(0), '.');
        std::vector<short> ip;
        for (const auto& item : ipString)
            ip.emplace_back(static_cast<short>(std::stoi(item)));
        m_ipPool.push_back(ip);
    }
}

void IpFilter::loadIpPool()
{
    std::ifstream file("C:\\Users\\User\\Downloads\\ip_filter.tsv");

    for (std::string line; std::getline(file, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        std::vector<std::string> ipString = split(v.at(0), '.');
        std::vector<short> ip;
        for (const auto& item : ipString)
            ip.emplace_back(static_cast<short>(std::stoi(item)));
        m_ipPool.push_back(ip);
    }
    file.close();
}

void IpFilter::printIp(const Pool& pool) const
{
    for (const auto& ip : pool)
    {
        bool isFirst = true;
        for (const auto& ip_part : ip)
        {
            if (!isFirst)
                std::cout << ".";
            else
                isFirst = false;

            std::cout << ip_part;
        }
        std::cout << std::endl;
    }
}
void IpFilter::printIp() const
{
    printIp(m_ipPool);
}


void IpFilter::sortIpPool()
{
    std::sort(m_ipPool.begin(), m_ipPool.end(), [](auto& a, auto& b) { return (a > b); });
}

Pool IpFilter::filter(std::vector<short> mask1, short mask2)
{
    Pool ip_pool = m_ipPool;
    for (unsigned short i = 0; i < 4 && i < mask1.size(); ++i)
    {
        auto result = std::remove_if(ip_pool.begin(), ip_pool.end(), [&](std::vector<short> ip)
            { return mask1[i] >= 0 ? ip[i] != mask1[i] : false; });
        ip_pool.erase(result, ip_pool.end());
    }

    auto result = std::remove_if(ip_pool.begin(), ip_pool.end(), [&](std::vector<short> ip)
        {
            return mask2 >= 0 ? std::find(ip.begin(), ip.end(), mask2) == ip.end() : false;
        });
    ip_pool.erase(result, ip_pool.end());

    return ip_pool;
}

