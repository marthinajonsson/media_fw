//
// Created by mjonsson on 11/16/18.
//

#include <sys/wait.h>
#include <iterator>
#include <algorithm>
#include <JsonParser.h>
#include "HttpConnector.h"

std::string HttpConnector::compileLogin() {

    const auto filename = "~/syno/config.yaml";
    if(access( filename, F_OK ) == RET::ERROR) {
        m_logger->TRACE(Logger::ERR, "Http config file not found");
        return const_cast<char *>("");
    }
    JsonParser::getInstance().load(Category::Config);
    auto result = JsonParser::getInstance().getLatestResult();

    if(result["config"].empty()){
        m_logger->TRACE(Logger::ERR, "No configuration file loaded");
    }

    m_pwd = result["config"].at(0);
    m_name = result["config"].at(1);
    m_port = result["config"].at(2);
    m_server = result["config"].at(3);

    std::string opt = " --url ";
    std::string style = " --pretty";

    std::string argv = opt + m_name + ":" + m_pwd + "@" + m_server + ":" + m_port + style;
    return argv;
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
    auto requestProp = request.m_properties;
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
        auto found = std::find(requestProp.begin(), requestProp.end(), *it);
        if(found == requestProp.end()) {
            request.setError(RET::ERROR);
            request.setErrorDesc("Failed to find correct property");
        }

        property = *found;
        found++;
        val = *found;
    }

    std::string payloadStr = "'{" + property + ":" + val + "}'";
    return method + payload + payloadStr;
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



