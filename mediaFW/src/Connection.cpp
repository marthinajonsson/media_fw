//
// Created by mjonsson on 9/30/18.
//

/**
 *  This module shall setup ssh connection to the server and sen remoote commands
 */
#include "Connection.h"



void Connection::establishSshConnect() {

    m_ssh_session = ssh_new();
    if (m_ssh_session == nullptr){

        std::cerr << "Failed to initiate ssh session" << std::endl;
    }
    ssh_options_set(m_ssh_session, SSH_OPTIONS_HOST, "localhost");

    m_result = ssh_connect(m_ssh_session);
    if (m_result != SSH_OK)
    {
        std::cerr << "Failed to connect via ssh with error code " << ssh_get_error(m_ssh_session) << std::endl;
        ssh_free(m_ssh_session);
        return;
    }

    if (verifyHost(m_ssh_session) < 0)
    {
        std::cerr << "Failed to verify host" << std::endl;
        ssh_disconnect(m_ssh_session);
        ssh_free(m_ssh_session);
        return;
    }

    m_password = getpass("Password: ");
    m_result = ssh_userauth_password(m_ssh_session, nullptr, m_password);
    if (m_result != SSH_AUTH_SUCCESS)
    {
        std::cerr << "Failed to authenticate password with error code " << ssh_get_error(m_ssh_session) << std::endl;
        ssh_disconnect(m_ssh_session);
        ssh_free(m_ssh_session);
        return;
    }
    this->m_currentlyConnected = true;
}

bool Connection::sendRemoteCommands(std::string request, std::string &result) {

    ssh_channel p_channel;
    int p_result;
    char buffer[256];
    int nbytes;

    p_channel = ssh_channel_new(m_ssh_session);
    if (p_channel == nullptr) {
        std::cerr << "Failed to initiate channel with error code " << ssh_get_error(m_ssh_session) << std::endl;
        return false;
    }

    p_result = ssh_channel_open_session(p_channel);
    if (p_result != SSH_OK)
    {
        std::cerr << "Failed to open channel with error code " << ssh_get_error(m_ssh_session) << std::endl;
        ssh_channel_free(p_channel);
        return false;
    }

    p_result = ssh_channel_request_exec(p_channel, "ps aux");
    if (p_result != SSH_OK)
    {
        std::cerr << "Failed to request execution with error code " << ssh_get_error(m_ssh_session) << std::endl;
        ssh_channel_close(p_channel);
        ssh_channel_free(p_channel);
        return false;
    }
    nbytes = ssh_channel_read(p_channel, buffer, sizeof(buffer), 0);
    while (nbytes > 0)
    {
        if (write(1, buffer, nbytes) != (unsigned int) nbytes)
        {
            std::cerr << "Failed to write with error code " << ssh_get_error(m_ssh_session) << std::endl;
            ssh_channel_close(p_channel);
            ssh_channel_free(p_channel);
            return false;
        }
        nbytes = ssh_channel_read(p_channel, buffer, sizeof(buffer), 0);
    }

    if (nbytes < 0)
    {
        std::cerr << "Failed to read with error code " << ssh_get_error(m_ssh_session) << std::endl;
        ssh_channel_close(p_channel);
        ssh_channel_free(p_channel);
        return false;
    }
    result = buffer;
    ssh_channel_send_eof(p_channel);
    ssh_channel_close(p_channel);
    ssh_channel_free(p_channel);
    return false;
}

int Connection::verifyHost(ssh_session session)
{
    enum ssh_known_hosts_e state;
    unsigned char *hash = nullptr;
    ssh_key srv_pubkey = nullptr;
    size_t hlen;
    char buf[10];
    char *hexa;
    char *p;
    int cmp;
    int p_result;

    p_result = ssh_get_server_publickey(session, &srv_pubkey);
    if (p_result < 0) {
        return -1;
    }
    p_result = ssh_get_publickey_hash(srv_pubkey,
                                SSH_PUBLICKEY_HASH_SHA1,
                                &hash,
                                &hlen);
    ssh_key_free(srv_pubkey);
    if (p_result < 0) {
        return -1;
    }
    state = ssh_session_is_known_server(session);
    switch (state) {
        case SSH_KNOWN_HOSTS_OK:
            /* OK */
            break;
        case SSH_KNOWN_HOSTS_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hexa("Public key hash", hash, hlen);
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            ssh_clean_pubkey_hash(&hash);
            return -1;
        case SSH_KNOWN_HOSTS_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other"
                            "type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to"
                            "confuse your client into thinking the key does not exist\n");
            ssh_clean_pubkey_hash(&hash);
            return -1;
        case SSH_KNOWN_HOSTS_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be"
                            "automatically created.\n");
            /* FALL THROUGH to SSH_SERVER_NOT_KNOWN behavior */
        case SSH_KNOWN_HOSTS_UNKNOWN:
            hexa = ssh_get_hexa(hash, hlen);
            fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
            fprintf(stderr, "Public key hash: %s\n", hexa);
            ssh_string_free_char(hexa);
            ssh_clean_pubkey_hash(&hash);
            p = fgets(buf, sizeof(buf), stdin);
            if (p == nullptr) {
                return -1;
            }
            cmp = strncasecmp(buf, "yes", 3);
            if (cmp != 0) {
                return -1;
            }
            p_result = ssh_session_update_known_hosts(session);
            if (p_result < 0) {
                fprintf(stderr, "Error %s\n", strerror(errno));
                return -1;
            }
            break;
        case SSH_KNOWN_HOSTS_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            ssh_clean_pubkey_hash(&hash);
            return -1;
    }
    ssh_clean_pubkey_hash(&hash);
    return 0;
}