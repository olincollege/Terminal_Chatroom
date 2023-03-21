# Terminal_Chatroom

## Description

We created a chatroom in terminal using TCP sockets. The chatroom allows for a
server to be set up that allows multiple users to connect to it and communicate
to each other.

## Installation Instructions

There are no external libraries needed to run this project.

1. Clone the repository using one of the following commands:

```bash
git clone git@github.com:olincollege/Terminal_Chatroom.git
```

or

```bash
git clone https://github.com/olincollege/Terminal_Chatroom.git
```

2. Inside the directory, run the follow commands:

```bash
mkdir build
cd build
cmake ..
make
```

### To Run The Server

1. On the device you want to host the server on, go into the build directory and
   run the following command:

```bash
./src/server_exec
```

### To Run The Client

### Server and Client on Same Device

In the build directory, run the following command:

```bash
./src/client_exec
```

### Client is Connecting Remotely to Server

1. Get the IP of the device hosting the server.

2. In line 24 of `client_exec.c`, follow the instructions for commenting out and
   uncommenting the specific lines and replace the example IP with the IP of
   your server.

3. Rebuild the project as explained earlier.

4. In the build directory, run the following command:

```bash
./src/client_exec
```
