#ifndef INVICTI_ASSESSMENT
# define INVICTI_ASSESSMENT

# include <cpr/cpr.h>
# include <iostream>

// findingLoginPage.cpp
std::string getLoginUrl(std::string const & htmlContent);

//getLoginPageData.cpp
bool getLoginPageData(std::string const & url, std::string & uname, std::string & pass, std::string & connectionUrl);

//parsing.cpp
std::string getLineFromText(std::string const & htmlContent, std::string const & textToFind);
std::string getSubstringBetweenTwoXChar(std::string const & line, char c1, char c2);


#endif