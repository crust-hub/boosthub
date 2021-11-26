#include"tool.h"
tool_bucket::tool_bucket(){
    BOOST_LOG=new boost_log();
    ARG_PROCESS=new arg_process();
    FILE_OPERATOR=new file_operator();
}
tool_bucket::~tool_bucket(){
    delete BOOST_LOG;
    delete ARG_PROCESS;
    delete FILE_OPERATOR;
}


void* socket_process_thread(void* client_socket){
    int client_socket_id=*(int*)client_socket;
    free(client_socket);
    std::cout<<"开启socket处理线程 client_socket "<<client_socket_id<<"\n";
    //每次接收到请求都因该开辟新的线程 对其做出处理 包括接收数据与发送数据
    //读取内容
    char buffer[512]={0};
    size_t len=0;
    tool_bucket TOOL;
    
    while(1){
       len=recv(client_socket_id,buffer,sizeof(buffer),0);
       if(len<=0){
	  close(client_socket_id);
       	  break;
       }
       printf("%s\n",buffer);
    }
    
    TOOL.BOOST_LOG->close();
    printf("\n");
    //断开连接
    shutdown(client_socket_id,SHUT_WR);
    close(client_socket_id);
    return (void*)"sucess";
}

int new_socket_process_thread(int client_socket){
	std::cout<<client_socket<<std::endl;
    pthread_t thread;
    int* arg=(int*)malloc(sizeof(int));
    *arg=client_socket;
    int create_res=pthread_create(&thread, NULL, socket_process_thread, (void*)arg);
    if(create_res<0){
        std::cout<<"socket线程创建失败\n";
        shutdown(client_socket,SHUT_WR);
        close(client_socket);
    }
    return create_res;
}