
#include <iostream>
#include <vector>
#include "IpFilter.h"
#include <fstream>

int main()
{
    try
    {
        std::ofstream file("ip_filter_out.tsv");

        IpFilter ipPool;

        ipPool.loadIpPool();
        ipPool.sortIpPool();
        ipPool.printIp();
        ipPool.saveIp(file);
        {
            std::vector<short> mask{ 1 };
            ipPool.printIp(ipPool.filter(mask));
            std::cout << "---------------------------" << std::endl;
            ipPool.saveIp(ipPool.filter(mask), file);
        }
        {
            std::vector<short> mask{ 46, 70 };
            ipPool.printIp(ipPool.filter(mask));
            std::cout << "---------------------------" << std::endl;
            ipPool.saveIp(ipPool.filter(mask), file);
        }
        {
            std::vector<short> mask{};
            ipPool.printIp(ipPool.filter( mask, 46));
            std::cout << "---------------------------" << std::endl;
            ipPool.saveIp(ipPool.filter(mask, 46), file);
        }
        file.close();

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
