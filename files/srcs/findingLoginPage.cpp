#include "../includes/invicti_assessment.hpp"

std::string getLoginUrl(std::string const & htmlContent)
{
    // get the html line with login in it
    std::string line = getLineFromText(htmlContent, "login");

    if (line.empty()) // if no line found, return empty string
        return (line);

    std::string url = getSubstringBetweenTwoXChar(line, '"', '"');

    return (url);
}
