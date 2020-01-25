
#include <iostream>
#include <vector>
#include "IpFilter.h"
#include <fstream>

void test()
{
    std::ofstream file("ip_filter_out.tsv");

    IpFilter ipPool;
    ipPool.loadIpPool(std::move(std::ifstream("ip_filter.tsv")));

    ipPool.sortIpPool();
    ipPool.saveIp(file);
    {
        std::vector<short> mask{ 1 };
        ipPool.saveIp(ipPool.filter(mask), file);
    }
    {
        std::vector<short> mask{ 46, 70 };
        ipPool.saveIp(ipPool.filter(mask), file);
    }
    {
        std::vector<short> mask{};
        ipPool.saveIp(ipPool.filter(mask, 46), file);
    }
    file.close();
}


int main()
{
    try
    {
        IpFilter ipPool;
        ipPool.loadIpPool(std::move(std::cin));

        ipPool.sortIpPool();
        ipPool.printIp();
        {
            std::vector<short> mask{ 1 };
            ipPool.printIp(ipPool.filter(mask));
        }
        {
            std::vector<short> mask{ 46, 70 };
            ipPool.printIp(ipPool.filter(mask));
        }
        {
            std::vector<short> mask{};
            ipPool.printIp(ipPool.filter( mask, 46));
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
