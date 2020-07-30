# Simple-UDP-Client-Server
Year 2 Semester 2 Distributed Systems Programming Task 1

      Compiling and Running
            gcc -o server UDP_Server.c
            gcc -o client UDP_Client.c
            gcc -o clientRW UDP_ClientReadWrite.c
            
            Run in two different interfaces simultaneously, starting server first:
            
            ./server max_iterations
                  (max_iterations = how many times the server will wait for requests)
            
            ./client client_message
                  (client_message is whatever you want to send to the server,
                      max length set to 48)
