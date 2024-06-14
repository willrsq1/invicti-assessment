#include "../includes/invicti_assessment.hpp"

bool getUnameAndPass(std::string const & loginPageHtml, std::string & uname, std::string & pass)
{
    // get the line containing uname and pass
    std::string line = getLineFromText(loginPageHtml, "Please use the username");

    if (line.empty())
    {
        std::cerr << "Unable to retrieve uname/pass line in html content" << std::endl;
        return (false);
    }

    // get the uname
    uname = getSubstringBetweenTwoXChar(line, '>', '<');


    // get the pass
    int startSubstr = line.find("and the password") + std::string("and the password").length();
    line = line.substr(startSubstr); // get the second part of the line (after the uname)
    pass = getSubstringBetweenTwoXChar(line, '>', '<');

    // check for errors
    if (uname.empty() || pass.empty())
    {
        std::cerr << "Unable to retrieve uname/pass" << std::endl;
        return (false);
    }

    return (true);
}

bool getConnectionUrl(std::string const & loginPageHtml, std::string & connectionUrl)
{

    // get the line containing the conneciton redirection form
    std::string line = getLineFromText(loginPageHtml, "loginform");

    int pos = line.find("action");

    if (pos == std::string::npos)
    {
        std::cerr << "Couldn't find the redierction to get connectionUrl" << std::endl;
        return (false);
    }

    // get the redirection url
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
    // get the login page html content
    cpr::Response loginPageResponse = cpr::Get(cpr::Url{url});

    if (loginPageResponse.status_code != 200)
    {
        std::cerr << "Failed to get loginPage Html" << std::endl;
        return (false);
    }

    // find the credentials
    if (getUnameAndPass(loginPageResponse.text, uname, pass) == false)
        return (false);

    // find the page where to input the credentials
    if (getConnectionUrl(loginPageResponse.text, connectionUrl) == false)
        return (false);

    return (true);
}
