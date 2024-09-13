FROM ubuntu:24.04

RUN apt update -y
RUN apt install make bison g++ -y
RUN apt install libpng-dev -y
RUN apt install flex -y
RUN apt install libicu-dev -y

RUN mkdir /context-free
WORKDIR /context-free
COPY Makefile .
COPY src-agg ./src-agg
COPY src-common ./src-common
COPY src-unix ./src-unix
COPY input ./input
RUN make
COPY ./runtests.sh .
RUN make test
