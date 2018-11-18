//
// Created by mjonsson on 11/16/18.
//

#include <sys/wait.h>
#include <unistd.h>
#include <iterator>
#include <algorithm>
#include <JsonParser.h>
#include "HttpConnector.h"

std::string HttpConnector::compileLogin() {

    const auto filename = "../data/config.json"; //"~/syno/config.yaml";
    int a = access( filename, F_OK );
    if(a != RET::OK) {
        m_logger->TRACE(Logger::ERR, "Http config file not found");
        return const_cast<char *>("");
    }
    JsonParser::getInstance().load(Category::Config);
    auto result = JsonParser::getInstance().getConfig();

    if(result.size() == 0){
        m_logger->TRACE(Logger::ERR, "No configuration file loaded");
    }

    m_pwd = result["config"].s_pwd;
    m_name = result["config"].s_user;
    m_port = result["config"].s_port;
    m_server = result["config"].s_url;

    std::string opt = " --url ";
    std::string style = " --pretty";

    return style + opt + "http://" + m_name + ":" + m_pwd + "@" + m_server + ":" + m_port;
}

std::string HttpConnector::compilePayload(Request &request) {

    std::string payload = " --payload ";
    auto event = request.getEvent();
    auto category = request.getCategory();
    std::string method;
    auto vec = m_mapMethod[event];

    if(vec.empty()) {
        request.setError(RET::ERROR);
        request.setErrorDesc("Failed to map to Syno Method");
        return "";
    }
    int option = 0;
    if(category == Category::Series) {option = 1;}
    method = vec.at(option);

    if(method.empty()) {
        request.setError(RET::ERROR);
        request.setErrorDesc("Failed to map to Syno Method");
        return "";
    }

    std::string property;
    std::string val;
    auto mapProp = request.getProperties();

    std::vector<std::string> searchVec;
    std::vector<std::string>::iterator it;
    if(event == Event::UPLOAD) {
        searchVec = uploadProperties;
    }else if(event == Event::DOWNLOAD) {
        searchVec = downloadProperties;
    }else if(event == Event::SEARCH) {
        searchVec = searchProperties;
    }else if(event == Event::DELETE) {
        searchVec = deleteProperties;
    }

    for(it = searchVec.begin(); it != searchVec.end(); it++) {
        if(!mapProp[*it].empty()) {
            property = *it;
            val = mapProp[*it];
            break;
        }
    }

    std::string payloadStr = "'{" + property + ":" + val + "}'";
    auto result = method + payload + payloadStr;
    return result;
}

std::string HttpConnector::compile(Request &request) {
    std::string url = compileLogin();

    std::string payload = compilePayload(request);

    std::string argv = payload + url;
    return argv;
}

void HttpConnector::send(Request &request) {
    char* CMD = const_cast<char *>("syno vs ");

    auto argv = compile(request);
    char* ARGV = const_cast<char *>(argv.c_str());


    if(!argv.empty()) {
        ch_pid = fork();
    }

    if(ch_pid >= 0) {
        if( ch_pid == 0) {
            char* cmd[]= {CMD, ARGV};
            execv("~/syno/bin/", cmd);
        }
        else {
            wait(&status);
        }
    }
    else {
        m_logger->TRACE(Logger::ERR, "failed to fork");
    }
}



