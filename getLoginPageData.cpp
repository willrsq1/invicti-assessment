#include "invicti_assessment.hpp"

bool getUnameAndPass(std::string const & loginPageHtml, std::string & uname, std::string & pass)
{
    std::string line = getLineFromText(loginPageHtml, "Please use the username"); // get the line containing uname and pass

    if (line.empty())
    {
        std::cerr << "Unable to retrieve uname/pass line in html content" << std::endl;
        return (false);
    }

    uname = getSubstringBetweenTwoXChar(line, '>', '<'); // get the uname

    int startSubstr = line.find("and the password") + std::string("and the password").length();
    line = line.substr(startSubstr); // get the second part of the line (after the uname)
    pass = getSubstringBetweenTwoXChar(line, '>', '<'); // get the pass

    if (uname.empty() || pass.empty())
    {
        std::cerr << "Unable to retrieve uname/pass" << std::endl;
        return (false);
    }

    return (true);
}

bool getConnectionUrl(std::string const & loginPageHtml, std::string & connectionUrl)
{

    std::string line = getLineFromText(loginPageHtml, "loginform");

    int pos = line.find("action");

    if (pos == std::string::npos)
    {
        std::cerr << "Couldn't find the redierction to get connectionUrl" << std::endl;
        return (false);
    }

    line = line.substr(pos);

    connectionUrl = getSubstringBetweenTwoXChar(line, '"', '"');

    if (connectionUrl.empty())
    {
        std::cerr << "Couldn't retrieve the connectionUrl" << std::endl;
        return (false);
    }

    return (true);
}

bool getLoginPageData(std::string const & url, std::string & uname, std::string & pass, std::string & connectionUrl)
{
    cpr::Response loginPageResponse = cpr::Get(cpr::Url{url});

    if (loginPageResponse.status_code != 200)
    {
        std::cerr << "Failed to get loginPage Html" << std::endl;
        return (false);
    }

    if (getUnameAndPass(loginPageResponse.text, uname, pass) == false)
        return (false);

    if (getConnectionUrl(loginPageResponse.text, connectionUrl) == false)
        return (false);

    return (true);
}
