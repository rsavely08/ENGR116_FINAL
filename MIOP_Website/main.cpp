#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>

#pragma commment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

std::map<std::string, std::string> url_mappings = {
	{"/", "templates/index.html"},
	{"/about", "templates/about.html"}
};


#ifdef _WIN32
	void handle_post_request(SOCKET client_socket, int content_length, const std::string& post_data){
		std::istringstream stream(post_data);

		std::string line;
		std::map<std::string, std::string> parsed_data;

		while(std::getline(stream, line, '&')){
			size_t pos = line.find('=');
			if (pos != std::string::npos){
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos + 1);

				parsed_data[key] = value; 
			}
		}

		std::string name = parsed_data ["name"];
		std::string response_data = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
		response_data += "<h1>Hello: " + name + " !</h1";

		std::ifstream file("templates/index.html");
		if (file.is_open()){
			response_data += std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
			file.close();
		}

		send(client_socket, response_data.c_str(), response_data.size(), 0);
		closesocket(client_socket);
	}
#else
	void handle_post_request(int client_socket, int content_length, const std::string& post_data){
		std::istringstream stream(post_data);

		std::string line;
		std::map<std::string, std::string> parsed_data;

		while(std::getline(stream, line, '&')){
			size_t pos = line.find('=');
			if (pos != std::string::npos){
				std::string key = line.substr(0, pos);
				std::string value = line.substr(pos + 1);

				parsed_data[key] = value; 
			}
		}

		std::string name = parsed_data ["name"];
		std::string response_data = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
		response_data += "<h1>Hello: " + name + " !</h1";

		std::ifstream file("templates/index.html");
		if (file.is_open()){
			response_data += std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
			file.close();
		}

		send(client_socket, response_data.c_str()), response_data.size(, 0);
		closesocket(client_socket);
	}

#endif

#ifdef _WIN32
	void handle_request(SOCKET client_socket, const std::string& request_path, int content_length, const std::string& post_data){
		if(url_mappings.find(request_path) != url_mappings.end() && content_length != 0){
			handle_post_request(client_socket, content_length, post_data);
		}
		
		else{
			std::string response_data;

			if (url_mappings.find(request_path) != url_mappings.end()){
				std::ifstream file(url_mappings[request_path]);

				if(file.is_open()){
					response_data = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" +
									std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); 
					file.close(); 
				}
			}	else{
				response_data="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Not found</h1>";
			}
			
			send(client_socket, response_data.c_str(), response_data.size(), 0);
			closesocket(client_socket);
		}
	}
#else
	void handle_request(int client_socket, const std::string& request_path, int content_length, const std::string& post_data){
		std::string response_data;

		if (url_mappings.find(request_path) != url_mappings.end()){
			std::ifstream file(url_mappings[request_path]);

			if(file.is_open()){
				response_data = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" +
								std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); 
				file.close(); 
			}
		}	else{
			response_data="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Not found</h1>";
		}
			
		send(client_socket, response_data.c_str(), response_data.size(), 0);
		closesocket(client_socket);
	}
#endif

std::pair<std::string, std::string> parse_request(const std::string& request_path){
	std::istringstream stream(request_path);

	std::string line;
	std::getline(stream, line);

	std::istringstream line_stream(line);

	std::vector<std::string> tokens;
	std::string token;
	
	while (line_stream>>token){
		tokens.push_back(token);
	}

	std::string method = tokens.size()> 0 ? tokens[0] : "";
	std::string path = tokens.size() > 0 ? tokens[1] : "";

	return std::make_pair(method, path);
}

void run_server(){
	const char* host = "127.0.0.1";
	const int port = 7654;

#ifdef _WIN32

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize WINSOCK" << std::endl;
		return;
	}

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) {
		std::cerr << "Failed to create server socket" << std::endl;
		WSACleanup();
		return;
	}

#else

	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {
		std::cerr << "Failed to create server socket" << std::endl;
		WSACleanup();
		return;

#endif


		sockaddr_in server_address{};

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = inet_addr(host);
		server_address.sin_port = htons(port);

		if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
			std::cerr << "Failed to bind socket" << std::endl;
			closesocket(server_socket);

#ifdef _WIN32

			WSACleanup();
#endif

			return;
		}


		if (listen(server_socket, 1) == SOCKET_ERROR) {
			std::cerr << "Failed to listen" << std::endl;
			closesocket(server_socket);

#ifdef _WIN32

			WSACleanup();
#endif

			return;
		}

		std::cout << "Server listening on " << host << ":" << port << std::endl;

		try{
			while (true){
				sockaddr_in client_address{};
				int client_address_size = sizeof(client_address);

				#ifdef _WIN32
					SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
				
					if (client_socket == INVALID_SOCKET){
						std::cerr << "Error acception connection" << std::endl;
						continue;
					}
				#else
					int (client_socket) = accept(server_socket, (struct sockaddr*)&client_address, &client_addrees_size);
					if (client_socket == -1){
						std::cerr << "Error acception connection" << std::endl;
						continue;
					}
				#endif

				std::cout << "Accept connection from" << inet_ntoa(client_address.sin_addr) << std::endl;

				char buffer[1024];
				int bytes_recieved = recv(client_socket, buffer, sizeof(buffer), 0);

				#ifdef _WIN32
					if (bytes_recieved == SOCKET_ERROR || bytes_recieved == 0){
						std::cerr << "Error recieving data" << std::endl;
						closesocket(client_socket);
						continue;
					}
				#else
					if (bytes_recieved == -1 || bytes_recieved == 0){
						std::cerr << "Error recieving data" << std::endl;
						closesocket(client_socket);
						continue;
					}
				#endif

				std::string request_data(buffer, bytes_recieved);
				auto [method, path] = parse_request(request_data);

				std::cout << "Recieved " << method << "from " << path << std::endl;

				int content_length= 0; 
				std::string post_data;
				size_t pos;

				if (method == "POST"){
					pos = request_data.find("\r\n\r\n");
				

					if (pos != std::string::npos){
						std::string headers = request_data.substr(0, pos);
						std::istringstream headers_stream(headers);

						std::string header; 

						while (std::getline(headers_stream, header, '\r')){
							if (header.find("Content-Length") != std::string::npos){
								content_length = std::stoi(header.substr(16));
								break;
							}
						}

						post_data = request_data.substr(pos + 4);
					}

				}

				handle_request(client_socket, path, content_length, post_data);
			}
		} 
		
		catch (const std::exception& e){
			std::cerr << "Exception: " << e.what() << std::endl;
		}	catch(...){
			 std::cerr << "Unknown exception" << std::endl;
		}

		closesocket(server_socket);

		#ifdef _WIN32
			WSACleanup();
		#endif
}


int main() {
	run_server();
}