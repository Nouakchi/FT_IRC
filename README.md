# ft_irc - Internet Relay Chat Server

## Summary

This project involves creating your own IRC (Internet Relay Chat) server. IRC is a text-based communication protocol on the Internet that supports real-time messaging, public or private, and allows users to join group channels.

## Version

Version: 8

## Contents

- [Chapter I - Introduction](#chapter-i-introduction)
- [Chapter II - General Rules](#chapter-ii-general-rules)
- [Chapter III - Mandatory Part](#chapter-iii-mandatory-part)
- [Chapter IV - Bonus Part](#chapter-iv-bonus-part)
- [Chapter V - Submission and Peer-evaluation](#chapter-v-submission-and-peer-evaluation)

## Chapter I - Introduction

Internet Relay Chat (IRC) is a text-based communication protocol that enables users to communicate in real-time via channels or direct messaging. This project involves creating a functional IRC server using C++.

## Chapter II - General Rules

- Your program must handle all scenarios without crashing, including handling out-of-memory situations.
- Provide a Makefile that compiles your source files without relinking.
- The Makefile must include at least the rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- Compile your code with C++ and the flags `-Wall -Wextra -Werror`.
- Your code must comply with the C++ 98 standard and should compile with the flag `-std=c++98`.
- Use C++ features over C functions where possible.
- External libraries, including Boost, are not allowed.

## Chapter III - Mandatory Part

### Program Details

Program name: `ircserv`

### Turn in files

- `Makefile`
- `*.{h, hpp}`
- `*.cpp`
- `*.tpp`
- `*.ipp`
- (optional) Configuration file

### Makefile Requirements

- `NAME`, `all`, `clean`, `fclean`, `re`

### Arguments

- `port`: The listening port for the IRC server.
- `password`: Connection password required by IRC clients.

### External Functions (C++ 98)

- `socket`, `close`, `setsockopt`, `getsockname`, `getprotobyname`, `gethostbyname`, `getaddrinfo`, `freeaddrinfo`, `bind`, `connect`, `listen`, `accept`, `htons`, `htonl`, `ntohs`, `ntohl`, `inet_addr`, `inet_ntoa`, `send`, `recv`, `signal`, `sigaction`, `lseek`, `fstat`, `fcntl`, `poll` (or equivalent).

### Description

An IRC server implemented in C++ 98.

### Requirements

- The server must handle multiple clients simultaneously without hanging.
- All I/O operations must be non-blocking; forking is not allowed.
- Use only one `poll()` (or equivalent) for handling read, write, listen operations.
- Implement basic IRC functionalities similar to official IRC servers:
  - Authentication, nickname and username setting.
  - Joining channels, sending and receiving private messages.
  - Forward messages to all clients in a channel.
  - Support for operators and regular users.
  - Implement commands specific to channel operators (e.g., KICK, INVITE, TOPIC, MODE).

### Evaluation

Your IRC server must function seamlessly with a chosen reference IRC client.

## Chapter IV - Bonus Part

### Additional Features (Optional)

Enhance your IRC server with these bonus features:

- File transfer capabilities.
- Implementing a bot.

These features will only be evaluated if the mandatory requirements are fully implemented without any issues.

## Chapter V - Submission and Peer-evaluation

Submit your project according to the guidelines provided by your instructor for evaluation.

