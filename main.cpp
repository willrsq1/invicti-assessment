#include <cpr/cpr.h>
#include <iostream>

int main()
{
    cpr::Response r = cpr::Post(cpr::Url{"http://testphp.vulnweb.com/userinfo.php"},
                                cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"},
                                            {"Cookie", "login=test%2Ftest"}},
                                cpr::Body{"uname=test&pass=test"});
    std::cout << r.text << std::endl;
    std::cout << r.status_code << std::endl;
    return (0);
}


// curl 'http://testphp.vulnweb.com/userinfo.php' \
//   -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7' \
//   -H 'Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7' \
//   -H 'Cache-Control: no-cache' \
//   -H 'Connection: keep-alive' \
//   -H 'Content-Type: application/x-www-form-urlencoded' \
//   -H 'Cookie: login=test%2Ftest' \
//   -H 'Origin: http://testphp.vulnweb.com' \
//   -H 'Pragma: no-cache' \
//   -H 'Referer: http://testphp.vulnweb.com/login.php' \
//   -H 'Upgrade-Insecure-Requests: 1' \
//   -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36' \
//   --data-raw 'uname=test&pass=test' \
//   --insecure
