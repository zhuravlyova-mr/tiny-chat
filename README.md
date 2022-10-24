# TinyChat
<p>TinyChat is a small chat using Berkeley sockets created in Microsoft Visual Studio.</p>
<p>It consists of a server program and a client program.
Server takes a port number as a command line argument. Client takes a port number and host IP-address as command line arguments.
<p>One server can process many clients requests.</p>
<p>Messages are sent in json format. A few message types are used for chatting. Only clients with logins and passwords listed in LogsPassws [see server.cpp] container can send messages.
There is a simple json parser (parser.cpp, parser.h) that is used to parse and unparse messages that are sent and recevied.</p>
<p>Mixed С/С++ code is used in programs (included string & string.h - must be rewritten).</p>
<p>You can use one server and up to 20 clients. There are bugs in this project, it needs to be improved.</p>
