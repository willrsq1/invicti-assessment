#include "invicti_assessment.hpp"

std::string getLoginUrl(std::string const & htmlContent)
{
    std::string line = getLineFromText(htmlContent, "login.php"); // get the html line with login in it

    if (line.empty()) // if no line found, return empty string
        return (line);

    std::string url = getSubstringBetweenTwoXChar(line, '"', '"');

    return (url);
}
