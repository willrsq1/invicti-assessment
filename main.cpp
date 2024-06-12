#include <cpr/cpr.h>
#include <iostream>

int main()
{
    cpr::Response r = cpr::Get(cpr::Url{"http://testphp.vulnweb.com/login.php"});
    std::cout << r.text << std::endl;
    return (0);
}
