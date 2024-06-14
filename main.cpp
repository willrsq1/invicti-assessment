#include <cpr/cpr.h>
#include <iostream>

//https://docs.libcpr.org/introduction.html#post-requests

std::string getLoginUrl(std::string const & htmlContent)
{
    std::string line;

    for (char c : htmlContent) // get the html line with login in it
    {
        if (c == '\n')
        {
            if (line.find("login.php") != std::string::npos)
            {
                break;
            }
            line.clear();
        }
        else
        {
            line += c;
        }
    }

    if (line.empty()) // if no line found, return empty string
        return (line);

    std::string url;
    int i = 0;

    while (line[i]) // get the login url part, contained between db quotes
    {
        if (line[i] == '"')
        {
            i += 1;
            while (line[i] && line[i] != '"')
            {
                url += line[i];
                i++;
            }
            return (url);
        }
        i++;
    }

    return (url);
}

int main()
{
    std::string url = "http://testphp.vulnweb.com/";

    cpr::Response landingPageResponse = cpr::Post(cpr::Url{url});

    if (landingPageResponse.status_code != 200)
    {
        std::cerr << "Failed to connect to the website: code " << landingPageResponse.status_code << std::endl;
        return (1);
    }

    std::string loginUrl = getLoginUrl(landingPageResponse.text);

    if (loginUrl.empty())
    {
        std::cerr << "No url found" << std::endl;
        return (1);
    }
    
    std::cout << "Login page URL: " << loginUrl << std::endl;

    return (0);

    //for future usage, if there is a need to access the user's session

    // std::string loginCookieValue;
    // for (const auto &cookie : r.cookies) {
    //     if (cookie.GetName() == "login")
    //     {
    //         loginCookieValue = cookie.GetValue();
    //         break ;
    //     }
    // }

    // std::cout << "User identification cookie: " << loginCookieValue << std::endl;

    // return (0);
}

//Not using the url asked in the assessement. Need to find a way to connect by using ..../login.php instead


    // cpr::Response r = cpr::Post(cpr::Url{"http://testphp.vulnweb.com/userinfo.php"},
    //                             cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
    //                             cpr::Body{"uname=test&pass=test"});

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
