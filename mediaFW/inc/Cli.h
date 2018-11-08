//
// Created by mjonsson on 9/30/18.
//

#ifndef MEDIAFW_CLI_H
#define MEDIAFW_CLI_H

#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Util.h"
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
    Request process(std::string &);
    void verifyUploadTest(Request &request, std::vector<std::string> &i) {
        setProperties(request, i, false);
    }
    Request interprete(std::vector<std::string> &, bool);

private:
    /*! \private Cli::parseArg(std::string &input)
     *
     * @brief Parses argv and splits into strings.
     * @param input A long input string containing argv from stdin.
     * @return Private vector of strings containing parsed words from stdin.
     */
    std::vector<std::string> parseArg(std::string &_input, char _delim) {
        std::stringstream m_stream(_input);
        std::vector<std::string> seglist;
        std::string segment;
        seglist.reserve(15);
        seglist.clear();

        while(std::getline(m_stream, segment, _delim))
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
    int checkValidEvent(std::vector<std::string> &_input, Event &_event){
        auto result = RET::ERROR;
        auto it = std::find(VALID.begin(), VALID.end(), _input.front());
        if(it != VALID.end())
        {
            long val = std::distance(VALID.begin(),it);
            _event = mapIntToEnum(val);
            pop_front(_input);
            result = RET::OK;
        }
        return result;
    }


    int verifyObjectExists(std::string &_type, std::string &_value) {
        auto found =  JsonParser::getInstance().find(_type, _value);

        if(!found) { return RET::ERROR; }

        return RET::OK;
    }

    /*! \private Cli::getType(Request &, std::vector<std::string>&)
     *
     * @param req - object containing all info for request
     * @param input - cli input
     * @return - property type for request
     */
    std::string getType(Request &_req, std::vector<std::string> &_input) {
        auto type = _input.front();

        if(type == TITLE || type == GENRE || type == ACTOR || type == DIRECTOR || type == FILENAME) {
            pop_front(_input);
            return type;
        }
        else return "";
    }

    void setFileName(Request &_request, std::vector<std::string> &_input, std::string &_type) {
        if(_request.getEvent() == Event::UPLOAD || _type == FILENAME) {
            _request.setFilename(_input.front());
            pop_front(_input); // remove value of filename
        }
    }

    void setProperties(Request &_request, std::vector<std::string> &_item, bool removeCategory) {
       if(removeCategory) {
           pop_front(_item); // remove search category
       }
        _request.setTitle(_item.at(ORDER::TITLE_POS));
        _request.setGenre(_item.at(ORDER::GENRE_POS));
        _request.setDirector(_item.at(ORDER::DIRECTOR_POS));
        pop_front(_item); // not relevant anymore
        pop_front(_item);
        pop_front(_item);
        std::vector<std::string> vec;
        vec.insert(vec.begin(), _item.begin(), _item.end());
        _request.setActors(vec);
    }

    std::string setSearchCategory(Request &_request, std::vector<std::string> &_input) {
        auto category = _input.front();
        if(category == SERIES) {
            _request.setCategory(Category::Series);
        } else { _request.setCategory(Category::Movie); }

        pop_front(_input);
        return category;
    }

    std::map<std::string, std::vector<std::string>> filterResult(std::string &_category) {
        auto resultMap = JsonParser::getInstance().getLatestResult();
        std::map<std::string, std::vector<std::string>> filtered;

        for (auto m : resultMap) {
            auto found = std::find(m.second.begin(), m.second.end(), _category);
            if(found != m.second.end()) {
                pop_front(m.second);
                filtered[m.first] = m.second;
            }
        }

        return filtered;
    }

    /*! \private Cli::verifyUpload(Request &)
     *
     * @return OK or ERROR
     */
    int verifyUpload(Request &_request) {

        const auto filename = _request.getFileName();
        if (filename.empty()) { return false; }
        if(access( filename.c_str(), F_OK ) == RET::ERROR) {
            _request.setError(RET::ERROR);
            _request.setErrorDesc("File not found");
            return RET::ERROR;
        }
        std::cout << "To confirm your upload add the following info: \n"
                     "\t <title> <genre> <director> {<actor> <actor>.. } <category> " << std::endl;

        std::string info;
        std::string answer;

        std::getline(std::cin, info);
        auto parsedInfo = parseArg(info, ' ');
        std::cout << "Please confirm <title> " << parsedInfo.front() <<
                  "\n <genre> " << parsedInfo.at(1) << " <director> " << parsedInfo.at(2) << " and the following actors: \n" << std::endl;

        for (auto it = parsedInfo.begin() + 2; it != parsedInfo.end(); ++it){
            std::cout << *it << " " << std::endl;
        }

        std::cout << "Y or n? ";
        std::getline(std::cin, answer);
        if(answer.find('n') == std::string::npos)
        {
            return RET::ERROR;
        }

        _request.setCategory(Category::Movie);
        if(parsedInfo.front() == SERIES){
            _request.setCategory(Category::Series);
        }

        return RET::OK;
    }

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
