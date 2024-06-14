#ifndef INVICTI_ASSESSMENT
# define INVICTI_ASSESSMENT

# include <cpr/cpr.h>
# include <iostream>


std::string getLoginUrl(std::string const & htmlContent);

bool getLoginPageData(std::string const & url, std::string & uname, std::string & pass, std::string & connectionUrl);

std::string getLineFromText(std::string const & htmlContent, std::string const & textToFind);
std::string getSubstringBetweenTwoXChar(std::string const & line, char c1, char c2);


#endif