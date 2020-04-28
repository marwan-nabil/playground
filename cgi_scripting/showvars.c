#include <stdio.h>

char evars[20][80]={"SERVER_SOFTWARE", "SERVER_NAME", "SERVER_PROTOCOL", 
                    "SERVER_PORT",
                    "GATEWAY_INTERFACE", "REQUEST_METHOD", 
                    "PATH_INFO", "PATH_TRANSLATED", "SCRIPT_NAME", 
                    "QUERY_STRING", 
                    "REMOTE_HOST", "REMOTE_ADDR", "REMOTE_USER", 
                    "REMOTE_IDENT",
                    "AUTH_TYPE", "CONTENT_TYPE", "CONTENT_LENGTH", 
                    "HTTP_ACCEPT", "HTTP_USER_AGENT", "HTTP_REFERER"};


int main(void) {
    const numvars=20;
    int i;
  
    printf("Content-type: text/plain\n\n");
    for (i=0;i<numvars;i++) printf("%s = %s\n", evars[i], getenv(evars[i]));
    return 0;
}
