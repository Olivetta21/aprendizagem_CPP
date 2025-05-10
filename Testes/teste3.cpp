#include<stdio.h>
#include<winsock2.h>

#define BUFLEN 2048

int main(int argc , char *argv[])
{
    WSADATA winsock;
    SOCKET server_socket, client_socket;
    struct sockaddr_in servidor, cliente;
    int tam, rec_size, send_size;
    char menssagem[1024];

    char recvbuf[BUFLEN];
    int  recvbuflen = BUFLEN;

    printf("\nIniciando Winsock…\n");

    if (WSAStartup(MAKEWORD(2,2),&winsock) != 0)
    {
        printf("A inicializaçao falhou, codigo do erro: %d\n",WSAGetLastError());
        return 1;
    }
    printf("Winsock Iniciado.\n");
    if((server_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Erro ao criar o socket: %d\n" , WSAGetLastError());
        return 1;
    }
    printf("Socket criado.\n");
    servidor.sin_addr.s_addr = INADDR_ANY; // em todos endereços IPs do host
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons( 8080 );
    if( bind(server_socket ,(struct sockaddr *)&servidor , sizeof(servidor)) == SOCKET_ERROR)
    {
      printf("A ligacao ao socket falhou, codigo de erro: %d" , WSAGetLastError());
    }
    puts("Ligacao ao socket feita!");

/*
 *
 * escutando por conexões
 *
 */

    listen(server_socket , 2);
    puts("Esperando por conexoes...");
    tam = sizeof(struct sockaddr_in);
    while( (client_socket = accept(server_socket , (struct sockaddr *)&cliente, &tam)) != INVALID_SOCKET )
    {
        printf("Conexao aceita. IP cliente: %s - porta %d\n",inet_ntoa(cliente.sin_addr),ntohs(cliente.sin_port));

/*
 *
 *  enviando resposta para o cliente
 *
 */

        strcpy(menssagem , "Ola, Conexao recebida.\n");
        if (send(client_socket , menssagem , strlen(menssagem) , 0)>0) {
            puts("Boas vindas enviada!");
        }

        do {

           rec_size = recv(client_socket, recvbuf, recvbuflen, 0);
           if (rec_size > 0) {
               printf("Bytes recebidos: %d\n", rec_size);

               send_size  = send( client_socket, recvbuf, rec_size, 0 );
               if (send_size == SOCKET_ERROR) {
                  printf("Falha ao enviar, codigo de erro: %d\n", WSAGetLastError());
                  closesocket(client_socket);
                  WSACleanup();
                  return 1;
               }
               printf("Bytes enviados: %d\n", send_size);
           }
           else if (rec_size == 0)
                   printf("Conexao Fechada...\n");
                else  {
                   printf("Falha ao receber, codigo de erro: %d\n", WSAGetLastError());
                   closesocket(client_socket);
                   WSACleanup();
                   return 1;
                }

        } while (rec_size > 0);

        puts("Esperando por conexoes...");
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;

}