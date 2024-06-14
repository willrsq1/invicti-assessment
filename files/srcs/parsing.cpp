
#include "../includes/invicti_assessment.hpp"

std::string getLineFromText(std::string const & htmlContent, std::string const & textToFind)
{
    // get the html line from the html content
    std::string line;

    for (char c : htmlContent)
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
    //get the string contained between c1 and c2 of the given html line
    std::string substr;
    int i = 0;

    while (line[i])
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
