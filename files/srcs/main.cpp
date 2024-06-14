#include "../includes/invicti_assessment.hpp"

int main()
{
    std::string url = "http://testphp.vulnweb.com/";

    // get landing page html content
    cpr::Response landingPageResponse = cpr::Get(cpr::Url{url});

    if (landingPageResponse.status_code != 200)
    {
        std::cerr << "Failed to connect to the website: code " << landingPageResponse.status_code << std::endl;
        return (1);
    }

    // get login url
    std::string loginUrl = getLoginUrl(landingPageResponse.text);

    if (loginUrl.empty())
    {
        std::cerr << "No url found" << std::endl;
        return (1);
    }

    // get uname and pass and connection Url
    std::string uname, pass, connectionUrl;
    if (getLoginPageData(url + loginUrl, uname, pass, connectionUrl) == false)
        return (1);

    std::string body = "uname=" + uname + "&pass=" + pass;

    // do the actual login request with right credentials
    cpr::Response connectionResponse = cpr::Post(cpr::Url{url + connectionUrl},
                                    cpr::Body{body});

    if (connectionResponse.status_code != 200)
    {
        std::cerr << "Failed to log in" << std::endl;
        return (1);
    }

    //print the connected html response
    std::cout << connectionResponse.text << std::endl; // logged in !

    return (0);
}
