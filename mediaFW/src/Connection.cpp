//
// Created by mjonsson on 9/30/18.
//

/*
 * Run it like this:
 *
 * $ ./ssh2_echo 127.0.0.1 user password
 *
 * The code sends a 'cat' command, and then writes a lot of data to it only to
 * check that reading the returned data sums up to the same amount.
 *
 */
/* START OF THIRD LIB */
#include "libssh2_config.h"
#include <libssh2.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <sys/types.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>


//#include <boost/asio/io_service.hpp>
//#include <boost/asio/write.hpp>
//#include <boost/asio/buffer.hpp>
//#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>
#include <iostream>
//using namespace boost::asio;
//using namespace boost::asio::ip;
//
//io_service ioservice;
//tcp::resolver resolv{ioservice};
//tcp::socket tcp_socket{ioservice};
//std::array<char, 4096> bytes;


/* END OF THIRD LIB */

#include "Connection.h"
#include "Cli.h"

void write(std::string message){

    message = "Hej";

}
std::string read(){
    return "";
}



static int waitsocket(int socket_fd, LIBSSH2_SESSION *session) {
    struct timeval timeout{};
    int rc;
    fd_set fd;
    fd_set *writefd = nullptr;
    fd_set *readfd = nullptr;
    int dir;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&fd);

    FD_SET(socket_fd, &fd);

    /* now make sure we wait in the correct direction */
    dir = libssh2_session_block_directions(session);

    if (dir & LIBSSH2_SESSION_BLOCK_INBOUND){
        readfd = &fd;
    }

    if (dir & LIBSSH2_SESSION_BLOCK_OUTBOUND){
        writefd = &fd;
    }
    rc = select(socket_fd + 1, readfd, writefd, nullptr, &timeout);
    return rc;
}

void Connection::tryConnect() {
    std::cout << "Connecting.." << std::endl;
    //TODO: Setup connection to Network
//    tcp::resolver::query q{"theboostcpplibraries.com", "80"};
//    resolv.async_resolve(q, resolve_handler);
//    ioservice.run();

    //if(!ssh2Echo()) {
      //  std::cout << "SSH2 echo went wrong" << std::endl;
    //}

}
//
//void read_handler(const boost::system::error_code &ec,
//                  std::size_t bytes_transferred)
//{
//    if (!ec)
//    {
//        std::cout.write(bytes.data(), bytes_transferred);
//        tcp_socket.async_read_some(buffer(bytes), read_handler);
//    }
//}
//
//void connect_handler(const boost::system::error_code &ec)
//{
//    if (!ec)
//    {
//        std::string r =
//                "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
//        write(tcp_socket, buffer(r));
//        tcp_socket.async_read_some(buffer(bytes), read_handler);
//    }
//}
//
//void resolve_handler(const boost::system::error_code &ec,
//                     tcp::resolver::iterator it)
//{
//    if (!ec)
//        tcp_socket.async_connect(*it, connect_handler);
//}

bool Connection::ssh2Echo(){

    return true;

    const char *hostname =  "127.0.0.1"; //"10.40.188.250";
    const char *commandline = "cat";
    const char *username    = "a501822";
    const char *password    = "xhfypf6Q";
    const int BUFSIZE = 32000;
    in_addr_t hostaddr;
    int sock;
    struct sockaddr_in sin{};
    const char *fingerprint;
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    int rc;
    char *exitsignal=(char *)"none";
    size_t len;
    LIBSSH2_KNOWNHOSTS *nh;
    int type;


    rc = libssh2_init (0);

    if (rc != 0) {
        fprintf (stderr, "libssh2 initialization failed (%d)\n", rc);
    }


    hostaddr = inet_addr(hostname);
    /* Ultra basic "connect to port 22 on localhost"
    * Your code is responsible for creating the socket establishing the
    * connection
    */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = hostaddr;
    if (connect(sock, (struct sockaddr*)(&sin),
                sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "Failed to connect!\n");
        return -1;
    }

    /* Create a session instance */
    session = libssh2_session_init();
    if (!session)
    {
        fprintf(stderr, "Failed to create session instance\n");
        return false;
    }

    /* tell libssh2 we want it all done non-blocking */
    libssh2_session_set_blocking(session, 0);


    /* ... start it up. This will trade welcome banners, exchange keys,
     * and setup crypto, compression, and MAC layers
     */
    while ((rc = libssh2_session_handshake(session, sock)) ==

           LIBSSH2_ERROR_EAGAIN);
    if (rc) {
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
        return false;
    }

    nh = libssh2_knownhost_init(session);

    if(!nh) {
        /* eeek, do cleanup here */
        return false;
    }

    /* read all hosts from here */
    libssh2_knownhost_readfile(nh, "known_hosts",

                               LIBSSH2_KNOWNHOST_FILE_OPENSSH);

    /* store all known hosts to here */
    libssh2_knownhost_writefile(nh, "dumpfile",

                                LIBSSH2_KNOWNHOST_FILE_OPENSSH);

    fingerprint = libssh2_session_hostkey(session, &len, &type);

    if(fingerprint) {
        struct libssh2_knownhost *host;
        int check = libssh2_knownhost_checkp(nh, hostname, 22,

                                             fingerprint, len,
                                             LIBSSH2_KNOWNHOST_TYPE_PLAIN|
                                             LIBSSH2_KNOWNHOST_KEYENC_RAW,
                                             &host);

        fprintf(stderr, "Host check: %d, key: %s\n", check,
                (check <= LIBSSH2_KNOWNHOST_CHECK_MISMATCH)?
                host->key:"<none>");

        /*****
         * At this point, we could verify that 'check' tells us the key is
         * fine or bail out.
         *****/
    }
    else {
        /* eeek, do cleanup here */
        return false;
    }
    libssh2_knownhost_free(nh);


    if ( strlen(password) != 0 ) {
        /* We could authenticate via password */
        while ((rc = libssh2_userauth_password(session, username, password)) ==

               LIBSSH2_ERROR_EAGAIN);
        if (rc) {
            fprintf(stderr, "Authentication by password failed.\n");
            exit(1);
        }
    }

    libssh2_trace(session, LIBSSH2_TRACE_SOCKET);


    /* Exec non-blocking on the remove host */
    while( (channel = libssh2_channel_open_session(session)) == nullptr &&

           libssh2_session_last_error(session,nullptr,nullptr,0) ==

           LIBSSH2_ERROR_EAGAIN ) {
        waitsocket(sock, session);
    }
    if( channel == nullptr ) {
        fprintf(stderr,"Error\n");
        exit( 1 );
    }
    while( (rc = libssh2_channel_exec(channel, commandline)) ==

           LIBSSH2_ERROR_EAGAIN )
        waitsocket(sock, session);

    if( rc != 0 ) {
        fprintf(stderr, "exec error\n");
        exit( 1 );
    }
    else {
        LIBSSH2_POLLFD *fds;
        int running = 1;
        int bufsize = BUFSIZE;
        char buffer[BUFSIZE];
        int totsize = 1500000;
        int totwritten = 0;
        int totread = 0;
        int partials = 0;
        int rereads = 0;
        int rewrites = 0;
        int i;

        for (i = 0; i < BUFSIZE; i++)
            buffer[i] = 'A';
//
//        if ((fds = malloc (sizeof (LIBSSH2_POLLFD))) == NULL) {
//            fprintf(stderr, "malloc failed\n");
//            exit(1);
//        }

        fds[0].type = LIBSSH2_POLLFD_CHANNEL;
        fds[0].fd.channel = channel;
        fds[0].events = LIBSSH2_POLLFD_POLLIN | LIBSSH2_POLLFD_POLLOUT;

        do {
            int rc = (libssh2_poll(fds, 1, 10));

            int act = 0;

            if (rc < 1)
                continue;

            if (fds[0].revents & LIBSSH2_POLLFD_POLLIN) {
                ssize_t n = libssh2_channel_read(channel, buffer, sizeof(buffer));

                act++;

                if (n == LIBSSH2_ERROR_EAGAIN) {
                    rereads++;
                    fprintf(stderr, "will read again\n");
                }
                else if (n < 0) {
                    fprintf(stderr, "read failed\n");
                    exit(1);
                }
                else {
                    totread += n;
                    fprintf(stderr, "read %zd bytes (%d in total)\n",
                            n, totread);
                }
            }

            if (fds[0].revents & LIBSSH2_POLLFD_POLLOUT) {
                act++;

                if (totwritten < totsize) {
                    /* we have not written all data yet */
                    int left = totsize - totwritten;
                    size_t size = (left < bufsize) ? left : bufsize;
                    ssize_t n = libssh2_channel_write_ex(channel, 0, buffer, size);


                    if (n == LIBSSH2_ERROR_EAGAIN) {
                        rewrites++;
                        fprintf(stderr, "will write again\n");
                    }
                    else if (n < 0) {
                        fprintf(stderr, "write failed\n");
                        exit(1);
                    }
                    else {
                        totwritten += n;
                        fprintf(stderr, "wrote %zd bytes (%d in total)",
                                n, totwritten);
                        if (left >= bufsize && n != bufsize) {
                            partials++;
                            fprintf(stderr, " PARTIAL");
                        }
                        fprintf(stderr, "\n");
                    }
                } else {
                    /* all data written, send EOF */
                    rc = libssh2_channel_send_eof(channel);


                    if (rc == LIBSSH2_ERROR_EAGAIN) {
                        fprintf(stderr, "will send eof again\n");
                    }
                    else if (rc < 0) {
                        fprintf(stderr, "send eof failed\n");
                        exit(1);
                    }
                    else {
                        fprintf(stderr, "sent eof\n");
                        /* we're done writing, stop listening for OUT events */
                        fds[0].events &= ~LIBSSH2_POLLFD_POLLOUT;
                    }
                }
            }

            if (fds[0].revents & LIBSSH2_POLLFD_CHANNEL_CLOSED) {
                if (!act) /* don't leave loop until we have read all data */
                    running = 0;
            }
        } while(running);

        int exitcode = 127;
        while( (rc = libssh2_channel_close(channel)) == LIBSSH2_ERROR_EAGAIN )

            waitsocket(sock, session);

        if( rc == 0 ) {
            exitcode = libssh2_channel_get_exit_status( channel );

            libssh2_channel_get_exit_signal(channel, &exitsignal,

                                            nullptr, nullptr, nullptr, nullptr, nullptr);
        }

        if (exitsignal)
            fprintf(stderr, "\nGot signal: %s\n", exitsignal);

        libssh2_channel_free(channel);

        channel = nullptr;

        fprintf(stderr, "\nrereads: %d rewrites: %d totwritten %d\n",
                rereads, rewrites, totwritten);

        if (totwritten != totread) {
            fprintf(stderr, "\n*** FAIL bytes written: %d bytes "
                            "read: %d ***\n", totwritten, totread);
            exit(1);
        }
    }

    libssh2_session_disconnect(session,

                               "Normal Shutdown, Thank you for playing");
    libssh2_session_free(session);


    close(sock);
    fprintf(stderr, "all done\n");
    libssh2_exit();
    return true;
}
