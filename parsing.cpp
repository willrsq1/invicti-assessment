
#include "invicti_assessment.hpp"

std::string getLineFromText(std::string const & htmlContent, std::string const & textToFind)
{
    std::string line;

    for (char c : htmlContent) // get the html line with text to find in it
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
