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
#include "ifc/CommandLineParser.h"

/*! \class Cli
 * @brief Module handling everything related to our Command line interface.
 */
class Cli : CommandLineParser
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
    Request process() override;
    Request interprete(std::vector<std::string> &) override;

    Request process(std::string &) override;
    void verifyUploadTest(Request &request, std::vector<std::string> &i) {
        setProperties(request, i);
    }
private:
    const std::string TITLE = "title";
    const std::string GENRE = "genre";
    const std::string ACTOR = "actor";
    const std::string DIRECTOR = "director";
    const std::string FILENAME = "filename";

    std::string MOVIE = "movie";
    std::string SERIES = "series";

    const std::string DOWNLOAD = "download";
    const std::string UPLOAD = "upload";
    const std::string SEARCH = "search";
    const std::string DELETE = "delete";
    const std::string HELP = "help";
    const std::string EXIT = "exit";

    const std::vector<std::string> EVENT_ARGS = {UPLOAD, DOWNLOAD, SEARCH, DELETE, HELP, EXIT};


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
    int checkValidEvent(std::vector<std::string> &input, Event &event){
        auto result = RET::ERROR;
        auto eventStr = input.front();
        std::transform(eventStr.begin(), eventStr.end(), eventStr.begin(), ::tolower);

        auto it = std::find(EVENT_ARGS.begin(), EVENT_ARGS.end(), eventStr);
        if(it != EVENT_ARGS.end())
        {
            long val = std::distance(EVENT_ARGS.begin(),it);
            event = castTypeToEvent(val);
            pop_front(input);
            result = RET::OK;
        }
        return result;
    }

    int checkValidCategory(std::vector<std::string> &input, Category &category){
        auto result = RET::ERROR;
        auto vec = {MOVIE, SERIES};
        auto str = input.front();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        auto it = std::find(vec.begin(), vec.end(), str);
        if(it != vec.end())
        {
            long val = std::distance(vec.begin(),it);

            category = castTypeToCategory(val);
            pop_front(input);
            result = RET::OK;
        }
        return result;
    }

    int checkValidType(Request &request, std::string &type) {
        Event e = request.getEvent();

        if(e == Event::UPLOAD) {
            auto found = type.find(FILENAME);
            if(found == std::string::npos) {
                return RET::ERROR;
            }
        }
        else if (e == Event::DOWNLOAD || e == Event::DELETE) {
            auto found = type.find(TITLE);
            if(found == std::string::npos) {
                return RET::ERROR;
            }
        }
        else if (e == Event::SEARCH) {
            auto vec = {TITLE, GENRE, DIRECTOR, ACTOR};
            auto found = std::find(vec.begin(), vec.end(), type);
            if(found == vec.end()) {
                return RET::ERROR;
            }
        }
        else {
            return RET::ERROR;
        }
        return RET::OK;
    }


    int verifyObjectExists(Category &category, const std::string &type, const std::string &value) {
        auto found =  JsonParser::getInstance().find(category, value);

        if(!found) { return RET::ERROR; }

        return RET::OK;
    }

    /*! \private Cli::getType(Request &, std::vector<std::string>&)
     *
     * @param req - object containing all info for request
     * @param input - cli input
     * @return - property type for request
     */
    int getTypeOfValue(Request &request, std::vector<std::string> &input, std::string &type) {
        type = input.front();

        std::transform(type.begin(), type.end(), type.begin(), ::tolower);
        if(type == TITLE || type == GENRE || type == ACTOR || type == DIRECTOR || type == FILENAME) {
            pop_front(input);
            return RET::OK;
        }
        type = "";
        return RET::ERROR;
    }

    int getValueOfType(std::vector<std::string> &input, std::string &type, std::string &val) {

        if(input.size() > 1) {
            return RET::ERROR;
        }else {
            val = input.front();
        }

        if(val.empty()) {
            return RET::ERROR;
        }
        pop_front(input);
        return RET::OK;
    }

    void setFileName(Request &request, std::string &val) {
        std::string path = "../data/";
        val = path + val;
        request.setFilename(val);
    }

    void setProperties(Request &request, std::vector<std::string> &item) {
        request.setTitle(item.at(ORDER::TITLE_POS));
        request.setGenre(item.at(ORDER::GENRE_POS));
        request.setDirector(item.at(ORDER::DIRECTOR_POS));
        pop_front(item); // not relevant anymore
        pop_front(item);
        pop_front(item);
        std::vector<std::string> vec;
        vec.insert(vec.begin(), item.begin(), item.end());
        request.setActors(vec);
    }

    /*! \private Cli::verifyUpload(Request &)
     *
     * @return OK or ERROR
     */
    int verifyUpload(Request &request) {

        const auto filename = request.getFileName();
        if (filename.empty()) { return false; }
        if(access( filename.c_str(), F_OK ) == RET::ERROR) {
            request.setError(RET::ERROR);
            request.setErrorDesc("File not found");
            return RET::ERROR;
        }
        std::cout << "To confirm your upload add the following info: \n"
                     "<title> <genre> <director> {<actor> <actor>.. } " << std::endl;

        std::string info;
        std::string answer;

        std::getline(std::cin, info);
        auto parsedInfo = parseArg(info, ' ');
        std::cout << "Please confirm <title> " << parsedInfo.front() <<
                  " <genre> " << parsedInfo.at(1) << " <director> " << parsedInfo.at(2) << " and the following actors: " << std::endl;

        for (auto it = parsedInfo.begin() + 3; it != parsedInfo.end(); ++it){
            std::cout << *it << " " << std::endl;
        }

        std::cout << "\n y or n? ";
        std::getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answer == "n"){
            return RET::ERROR;
        }

        setProperties(request, parsedInfo);
        return RET::OK;
    }

    /*! \private Cli::printOptions()
    *   @brief Test A private method that prints all valid options for stdin.
    */
    void printOptions() {
        std::cout << "\n" << std::endl;

        auto choice {"<choice> = upload, download, search, delete\n"};

        auto upload = "<upload>:<movie/series>:<filename> \n\t*<filename> - absolute path to filename. \n";
        auto cmfupload = "\t To confirm your upload add the following info: \n\t <title> <genre> {<actor> <actor>.. } <director>\n\n";

        auto download = "<download>:<movie/series>:title:<title> \n";
        auto cfmdownload = "\t Title exists or did you mean 'abc'? \n\t Download completed\n\n";

        auto search {"<search>:<movie/series>:actor:Sandra Bullock. \n \t "};
        auto cfmsearch = "\t Found the following matches..\n\n";
        auto search2 {"<search>:<movie/series>:genre:Romance. \n \t "};

        auto deleted {"<delete>:<movie/series><title>\n"};
        auto cfmdelete = "\t Sure you want to delete, Y or n? \n\n";

        auto disconnect = "Write 'exit' to disconnect\n";

        std::cout << choice << "\nExample input..\n\n" << upload << cmfupload << download << cfmdownload << search
                  << cfmsearch << search2 << deleted << cfmdelete << std::endl;
        std::cout << disconnect << std::endl;
    }
};

#endif //MEDIAFW_CLI_H
