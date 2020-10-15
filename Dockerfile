FROM debian:latest

WORKDIR /root
ADD exploit.c ./
ADD pwned.txt ./

RUN apt update
RUN apt -y install gcc

RUN gcc exploit.c -o exploit

CMD ["/root/exploit"]
