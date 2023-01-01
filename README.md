# TinyChat
<p>TinyChat is a small chat using Berkeley sockets created in Microsoft Visual Studio.</p>
<p>It consists of a server program and a client program.
Server takes a port number as a command line argument. Client takes a port number and host IP-address as command line arguments.
<p>One server can process many clients requests.</p>
<p>Messages are sent in json format. A few message types are used for chatting. Only clients with logins and passwords listed in LogsPassws [see server.cpp] container can send messages.
There is a simple json parser (parser.cpp, parser.h) that is used to parse and unparse messages that are sent and recevied.</p>
<p>You can use one server and up to 20 clients. </p>
<p>To create executable for server code do next steps (in Windows OS):
cd /src/server
mkdir build
cd dir
cmake ..
cmake --build .
You can find the main.exe in /build/debug directory
Usage: main.exe <port>
Example of usage: main.exe 9090 </p>
<p>To create executable for client code do next steps (in Windows OS):
cd /src/client
mkdir build
cd dir
cmake ..
cmake --build .
You can find the main.exe in /build/debug directory
Usage: main.exe <port> <IP-address>, server must be already executed
Example of usage: main.exe 9090 127.0.0.1
</p>
