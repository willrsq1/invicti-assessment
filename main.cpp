#include <cpr/cpr.h>
#include <iostream>

//https://docs.libcpr.org/introduction.html#post-requests

std::string getLineFromText(std::string const & htmlContent, std::string const & textToFind)
{
    std::string line;

    for (char c : htmlContent) // get the html line with login in it
    {
        if (c == '\n')
        {
            if (line.find(textToFind) != std::string::npos)
            {
                return (line);
            }
            line.clear();
        }
        else
        {
            line += c;
        }
    }

    return ("");
}

std::string getSubstringBetweenTwoXChar(std::string const & line, char c1, char c2)
{
    std::string substr;
    int i = 0;

    while (line[i]) // get the substr part, contained between specified char
    {
        if (line[i] == c1)
        {
            i += 1;
            while (line[i] && line[i] != c2)
            {
                substr += line[i];
                i++;
            }
            return (substr);
        }
        i++;
    }

    return ("");
}

std::string getLoginUrl(std::string const & htmlContent)
{
    std::string line = getLineFromText(htmlContent, "login.php"); // get the html line with login in it

    if (line.empty()) // if no line found, return empty string
        return (line);

    std::string url = getSubstringBetweenTwoXChar(line, '"', '"');

    return (url);
}

bool getUnameAndPass(std::string const & url, std::string & uname, std::string & pass)
{
    cpr::Response loginPageResponse = cpr::Get(cpr::Url{url});

    if (loginPageResponse.status_code != 200)
    {
        std::cerr << "Failed to get loginPage Html" << std::endl;
        return (false);
    }

    std::string line = getLineFromText(loginPageResponse.text, "Please use the username"); // get the line containing uname and pass

    if (line.empty())
        return (false);

    uname = getSubstringBetweenTwoXChar(line, '>', '<'); // get the uname

    int startSubstr = line.find("and the password") + std::string("and the password").length();
    line = line.substr(startSubstr); // get the second part of the line (after the uname)
    pass = getSubstringBetweenTwoXChar(line, '>', '<'); // get the pass

    if (uname.empty() || pass.empty())
        return (false);

    std::cout << uname + " and " + pass << std::endl;
    
    return (true);
}

int main()
{
    std::string url = "http://testphp.vulnweb.com/";

    cpr::Response landingPageResponse = cpr::Get(cpr::Url{url});

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
    
    url += loginUrl;

    std::cout << url << std::endl;

    std::string uname, pass;
    
    if (getUnameAndPass(url, uname, pass) == false)
    {
        std::cerr << "Failed to retrieve uname and pass" << std::endl;
        return (1);
    }

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
