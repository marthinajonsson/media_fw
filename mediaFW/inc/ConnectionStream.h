//
// Created by mjonsson on 10/25/18.
//

#ifndef MEDIAFW_CONNECTIONSTREAM_H
#define MEDIAFW_CONNECTIONSTREAM_H

#include <StatusLogger.h>
#include <libssh/libssh.h>
#include <iostream>
#include <string>

class ConnectionStream
{
public:
    explicit ConnectionStream(ssh_session session) : m_session(session), m_logger(new StatusLogger) {
        if(m_session == nullptr) {
            m_logger->TRACE(Logger::ERR, "Connection lost");
        }

        try {
            m_channel = ssh_channel_new(m_session);
            if (m_channel == nullptr) {
                m_logger->TRACE(Logger::ERR, "Failed to initiate channel with error code ", ssh_get_error(m_session));
            }
        }catch (std::exception) { }
    }

    ~ConnectionStream() {
        ssh_channel_close(m_channel);
        ssh_channel_free(m_channel);
    };


    bool sendRemoteCommands(std::string &request, std::string &result) {

        int p_result;
        char buffer[256];
        int nbytes;

        p_result = ssh_channel_open_session(m_channel);
        if (p_result != SSH_OK)
        {
            m_logger->TRACE(Logger::ERR, "Failed to open channel with error code ", ssh_get_error(m_session));
            ssh_channel_free(m_channel);
            return false;
        }

        p_result = ssh_channel_request_exec(m_channel, request.c_str());
        if (p_result != SSH_OK)
        {
            m_logger->TRACE(Logger::ERR, "Failed to request execution with error code ", ssh_get_error(m_session));
            closeChannel(m_channel);
            return false;
        }
        nbytes = ssh_channel_read(m_channel, buffer, sizeof(buffer), 0);
        while (nbytes > 0)
        {
            if (write(1, buffer, nbytes) != (unsigned int) nbytes)
            {
                m_logger->TRACE(Logger::ERR, "Failed to write with error code ", ssh_get_error(m_session));
                closeChannel(m_channel);
                return false;
            }
            nbytes = ssh_channel_read(m_channel, buffer, sizeof(buffer), 0);
        }

        if (nbytes < 0)
        {
            m_logger->TRACE(Logger::ERR, "Failed to read with error code ", ssh_get_error(m_session));
            closeChannel(m_channel);
            return false;
        }
        result = buffer;
        ssh_channel_send_eof(m_channel);
        closeChannel(m_channel);
        return false;
    }

private:
    ssh_session m_session;
    ssh_channel m_channel;
    StatusLogger* m_logger;

    void closeChannel(ssh_channel channel) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }
};

#endif //MEDIAFW_CONNECTIONSTREAM_H
