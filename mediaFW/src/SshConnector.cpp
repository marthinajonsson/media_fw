//
// Created by mjonsson on 10/25/18.
//


#include <SshConnector.h>
#include <ConnectionStream.h>


ConnectionStream* SshConnector::connect(const uint16_t port, const std::string server) {
    std::string _password;
    const uint16_t *p_port;
    p_port = &port;

    m_session = ssh_new();
    if (m_session == nullptr)
    {
        m_logger->TRACE(Logger::ERR, "Failed to initiate ssh session");
    }

    std::string _username;
    std::cin >> _username;
    ssh_options_set(m_session, SSH_OPTIONS_PORT, p_port);
    ssh_options_set(m_session, SSH_OPTIONS_HOST, server.c_str());
    ssh_options_set(m_session, SSH_OPTIONS_USER, _username.c_str());

    if (ssh_connect(m_session) != SSH_OK)
    {
        m_logger->TRACE(Logger::ERR, "Failed to connect via ssh with error code ", ssh_get_error(m_session));
        ssh_free(m_session);
    }

    if (resolveHost(m_session) != SSH_OK)
    {
        disconnect();
    }

    _password = getpass("Password: ");
    auto _result = ssh_userauth_password(m_session, _username.c_str(), _password.c_str());
    if (_result != SSH_AUTH_SUCCESS)
    {
        m_logger->TRACE(Logger::ERR, "Failed to authenticate password with error code ", ssh_get_error(m_session));
        disconnect();
    }

    m_currentlyConnected = true;

    return new ConnectionStream(m_session);
}

int SshConnector::resolveHost(ssh_session session) {

    enum ssh_known_hosts_e _state;
    ssh_key _srvPubkey = nullptr;
    size_t _hLen;

    if (ssh_get_server_publickey(session, &_srvPubkey) < 0) {
        return SSH_ERROR;
    }
    auto _result = ssh_get_publickey_hash(_srvPubkey, SSH_PUBLICKEY_HASH_SHA1, &m_hash, &_hLen);
    ssh_key_free(_srvPubkey);
    if (_result < 0) {
        return SSH_ERROR;
    }

    _state = ssh_session_is_known_server(session);
    switch (_state) {
        case SSH_KNOWN_HOSTS_OK:
            break;
        case SSH_KNOWN_HOSTS_CHANGED: {
            m_logger->TRACE(Logger::ERR, "Host key for server changed: it is now: ");
            ssh_print_hexa("Public key hash", m_hash, _hLen);
            m_logger->TRACE(Logger::ERR, "For security reasons, connection will be stopped");
            ssh_clean_pubkey_hash(&m_hash);
            return SSH_ERROR;
        }
        case SSH_KNOWN_HOSTS_OTHER: {
            m_logger->TRACE(Logger::ERR, "The host key for this server was not found but an other type of key exists");
            std::string message = "An attacker might change the default server key to confuse your client into thinking the key does not exist";
            m_logger->TRACE(Logger::ERR, message);
            ssh_clean_pubkey_hash(&m_hash);
            return SSH_ERROR;
        }
        case SSH_KNOWN_HOSTS_NOT_FOUND:
            m_logger->TRACE(Logger::ERR,"Could not find known host file.If you accept the host key here, the file will be automatically created.");
            return SSH_ERROR;
        case SSH_KNOWN_HOSTS_UNKNOWN: {
            m_hexa = ssh_get_hexa(m_hash, _hLen);
            m_logger->TRACE(Logger::ERR, "The server is unknown. Do you trust the host key?");
            std::cerr << "Public key hash: \n" << m_hexa << std::endl;
            ssh_string_free_char(m_hexa);
            ssh_clean_pubkey_hash(&m_hash);

            std::string _answer;
            std::cin >> _answer;
            if (_answer.empty()) {
                return SSH_ERROR;
            }

            if (_answer.find("yes") != std::string::npos) {
                return SSH_ERROR;
            }

            if (ssh_session_update_known_hosts(session) < 0) {
                m_logger->TRACE(Logger::ERR, "Error ", ssh_get_error(m_session));
                return SSH_ERROR;
            }
            break;
        }
        case SSH_KNOWN_HOSTS_ERROR:
            m_logger->TRACE(Logger::ERR, "Error ", ssh_get_error(m_session));
            ssh_clean_pubkey_hash(&m_hash);
            return SSH_ERROR;
    }
    ssh_clean_pubkey_hash(&m_hash);
    return SSH_OK;
}

void SshConnector::disconnect() {
    m_currentlyConnected = false;
    ssh_disconnect(m_session);
    ssh_free(m_session);
}