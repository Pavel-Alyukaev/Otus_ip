
#include <iostream>
#include <vector>


#include "IpFilter.h"

int main(int argc, char const *argv[])
{
    try
    {
        IpFilter ipPool;

        ipPool.loadIpPool();
        ipPool.sortIpPool();
        ipPool.printIp();
        {
            std::vector<short> mask{ 1 };
            ipPool.printIp(ipPool.filter(mask));
            std::cout << "---------------------------" << std::endl;

        }
        {
            std::vector<short> mask{ 46, 70 };
            ipPool.printIp(ipPool.filter(mask));
            std::cout << "---------------------------" << std::endl;

        }
        {
            std::vector<short> mask;
            ipPool.printIp(ipPool.filter( mask, 46));
            std::cout << "---------------------------" << std::endl;

        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
