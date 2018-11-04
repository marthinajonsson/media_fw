//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

#include <Util.h>
#include "Request.h"

/*! \class Cli
 * @brief Module handling everything related to our Command line interface.
 */
class Cli
{
public:
    /*! \public Client()
     * @brief Cli default constructor.
     */
    Cli() {
        std::cout << "Cli constructor" << std::endl;
    }
    /*! \public ~Client()
     * @brief Cli default deconstructor.
     */
    ~Cli() = default;

    /*! \public Client::process()
     * @brief Public method processing input from stdin.
     * @return Vector of strings containing output from stdin.
     */
    Request process();
    Request process(std::string &line);

    Request interprete(std::vector<std::string> &input);

    template<typename T>
    void pop_front(std::vector<T>& vec)
    {
        assert(!vec.empty());
        vec.front() = std::move(vec.back());
        vec.pop_back();
    }

private:
    /*! \private Cli::parseArg(std::string &input)
     * @brief Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
    std::vector<std::string> parseArg(std::string &input, char delim);

    int checkValid(const std::string&, Event &event);

    /*! \private Cli::verifyParsed(std::vector<std::string> &)
     * @brief Verify parsed arguments. Varies on choice.
     */
    void verifyParsed(Request &);

    int verifyExists(Request &req);

    int verifyUpload(Request &);

    /*! \private Cli::printOptions()
     * @brief A private method that prints all valid options for stdin.
     */
    void printOptions();
};

#endif //MEDIAFW_CLI_H
