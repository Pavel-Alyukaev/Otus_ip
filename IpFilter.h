#pragma once
#include <vector>
#include <string>

typedef std::vector<std::vector<short> > Pool;

class IpFilter
{
private:
    Pool m_ipPool;
public:
    IpFilter() {};
    ~IpFilter() {};

    //Чтение ip адресов
    void setIpPool();
    void loadIpPool();

    //Печать ip адресов
    void printIp(const Pool& pool) const;
    void printIp() const;

    void saveIp(const Pool& pool, std::ofstream& file) const;
    void saveIp(std::ofstream& file) const;

    void sortIpPool();
    Pool filter(std::vector<short> mask1, short mask2 = -1);

    friend std::vector<std::string> split(const std::string& str, char d);
};

