//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <string>
#include <vector>


/*! Module handling everything related to our Command line interface.  */
class Cli
{
public:
    /*! \public Client()
     * @brief Cli default constructor.
     */
    Cli() = default;
    /*! \public ~Client()
     * @brief Cli default deconstructor.
     */
    ~Cli() = default;

    /*! \public Client::process()
     * @brief Public method processing input from stdin.
     * @return Vector of strings containing output from stdin.
     */
    std::vector<std::string> process();
    std::vector<std::string> process(std::string &test);

private:
    /*! \private Cli::parseArg(std::string &input)
     * @brief Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
    std::vector<std::string> parseArg(std::string &input);

    /*! \private Cli::printOptions()
     * @brief A private method that prints all valid options for stdin.
     */
    void printOptions();
};

#endif //MEDIAFW_CLI_H
