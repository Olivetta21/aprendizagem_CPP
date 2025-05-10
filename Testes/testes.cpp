#include<stdio.h>
#include<winsock2.h>
int main(int argc , char *argv[])
{
/*
 *
 *  Definição das estruturas de dados e inicialização da biblioteca winsock
 *
 */

    WSADATA winsock;
    SOCKET my_sock, new_sock;
    struct sockaddr_in servidor, cliente;
    int tam;
    char *message;

    printf("\nInicializando a biblioteca Winsock…\n");
    if (WSAStartup(MAKEWORD(2,2),&winsock) != 0)
    {
        printf("A inicialização falhou, código do erro: %d\n",WSAGetLastError());
        return 1;
    }
    printf("Winsock Inicializado.\n");

/*
 *
 * Criar o socket
 *
 */
    if((my_sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Erro ao criar o socket: %d\n" , WSAGetLastError());
        return 1;
    }
    printf("Socket criado.\n");

/*
 *
 * Ligar-se ao socket
 *
 */

    servidor.sin_addr.s_addr = INADDR_ANY; // em todos endereços IPs do host
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons( 8080 );
    if( bind(my_sock ,(struct sockaddr *)&servidor , sizeof(servidor)) == SOCKET_ERROR)
    {
       printf("A ligacao ao socket falhou, codigo de erro: %d" , WSAGetLastError());
    }
    puts("Ligacao ao socket feita!");

/*
 *
 * Escutando por conexões
 *
 */

    listen(my_sock , 3);
    puts("Esperando por conexoes...");
    tam = sizeof(struct sockaddr_in);

/*
 *
 * Conexão recebida
 *
 */

    new_sock = accept(my_sock , (struct sockaddr *)&cliente, &tam);
    if (new_sock == INVALID_SOCKET)
    {
        printf("erro ao aceitar a conexão, codigo de erro: %d" , WSAGetLastError());
    }
    printf("Conexao aceita. IP cliente: %s - porta %d\n",inet_ntoa(cliente.sin_addr),ntohs(cliente.sin_port));

/*
 *
 *  Enviando resposta para o cliente
 *
 */

    message = "Ola, Conexão recebida. Bye\n";
    if (send(new_sock , message , strlen(message) , 0)>0) {
        puts("Boas vindas enviada!");
    }

/*
 *
 * Fechando sockets e finalizando a biblioteca Winsock
 *
 */

    closesocket(new_sock);
    closesocket(my_sock);

    WSACleanup();

    return 0;
}