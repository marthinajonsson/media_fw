//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <Util.h>
#include "Request.h"
#include "JsonParser.h"

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

private:
    /*! \private Cli::parseArg(std::string &input)
     *
     * @brief Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
    std::vector<std::string> parseArg(std::string &input, char delim) {
        std::stringstream m_stream(input);
        std::vector<std::string> seglist;
        std::string segment;
        seglist.reserve(15);
        seglist.clear();

        while(std::getline(m_stream, segment, delim))
        {
            seglist.push_back(segment);
        }
        return seglist;
    }


    /*! \private Cli::checkValidEvent(const std::string&, Event &)
     *
     * @param choice - event in string
     * @param event - interpreted event from cli input
     * @return - OK or ERROR
     */
    int checkValidEvent(const std::string &choice, Event &event){
        auto result = RET::ERROR;
        auto it = std::find(VALID.begin(), VALID.end(), choice);
        if(it != VALID.end())
        {
            long val = std::distance(VALID.begin(),it);
            event = mapIntToEnum(val);
            result = RET::OK;
        }
        return result;
    }


    /*! \private Cli::verifyExists(Request &, std::string &, std::vector<std::string> &)
     *
     * @param req - object containing all info for request
     * @param type - property type for request
     * @param value - value of property for request
     * @return - OK or ERROR
     */
    int verifyExists(Request &req, std::string &type, std::vector<std::string> &value) {

        Category cat = Category::Movie;
        bool result =  JsonParser::getInstance().find(MOVIE, type, value.front());
        if(result) {
            req.setCategory(cat);
        }
        else {
            result =  JsonParser::getInstance().find(SERIES, type, value.front());
            if(!result) { return RET::ERROR;}
            else {
                cat = Category::Series;
                req.setCategory(cat);
            }
        }
        return RET::OK;
    }


    /*! \private Cli::getType(Request &, std::vector<std::string>&)
     *
     * @param req - object containing all info for request
     * @param input - cli input
     * @return - property type for request
     */
    std::string getType(Request &req, std::vector<std::string> &input) {
        auto type = input.front();
        if(type == "title" || type == "genre" || type == "actor" || type == "director" ||
           type == "filename") {
            pop_front(input);
            if(input.front().empty()) {
                req.setError(RET::ERROR); // no value for type
            }
            return type;
        }
        else return "";
    }


    /*! \private Cli::verifyUpload(Request &)
     *
     * @return OK or ERROR
     */
    int verifyUpload(Request &);


    /*! \private Cli::printOptions()
    *   @brief Test A private method that prints all valid options for stdin.
    */
    void printOptions() {
        std::cout << "\n" << std::endl;

        auto choice {"<choice> = upload, download, search, delete\n"};

        auto upload = "<upload>:<filename> \n\t*<filename> - absolute path to filename. \n";
        auto cmfupload = "\t To confirm your upload add the following info: \n\t <title> <genre> {<actor> <actor>.. } <director>\n\n";

        auto download = "<download>:<movie/series>:title:<title> \n";
        auto cfmdownload = "\t Title exists or did you mean 'abc'? \n\t Download completed\n\n";

        auto search {"<search>:<movie/series>:actor:Sandra Bullock. \n \t "};
        auto cfmsearch = "\t Found the following matches..\n\n";
        auto search2 {"<search>:<movie/series>:genre:Romance. \n \t "};

        auto deleted {"<delete>:<title>\n"};
        auto cfmdelete = "\t Sure you want to delete, Y or n? \n\n";

        auto disconnect = "Write 'exit' to disconnect\n";

        std::cout << choice << "\nExample input..\n\n" << upload << cmfupload << download << cfmdownload << search
                  << cfmsearch << search2 << deleted << cfmdelete << std::endl;
        std::cout << disconnect << std::endl;
    }
};

#endif //MEDIAFW_CLI_H
