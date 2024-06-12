#include <cpr/cpr.h>
#include <iostream>

#define SHOW_STATUS_CODE false //toggle from true to false to show the exit code

//https://docs.libcpr.org/introduction.html#post-requests

int main()
{
    cpr::Response r = cpr::Post(cpr::Url{"http://testphp.vulnweb.com/userinfo.php"},
                                cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                                cpr::Body{"uname=test&pass=test"});

    std::cout << r.text;

    SHOW_STATUS_CODE ? std::cout << r.status_code << std::endl : std::cout << std::endl;

    if (r.status_code != 200)
        return (1);

    return (0);

    //for future usage, if there is a need to access the user's session

    std::string loginCookieValue;
    for (const auto &cookie : r.cookies) {
        if (cookie.GetName() == "login")
        {
            loginCookieValue = cookie.GetValue();
            break ;
        }
    }

    std::cout << "User identification cookie: " << loginCookieValue << std::endl;

    return (0);
}

//Not using the url asked in the assessement. Need to find a way to connect by using ..../login.php instead


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
