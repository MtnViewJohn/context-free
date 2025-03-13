FROM ubuntu:24.04

RUN apt update -y
RUN apt upgrade -y
RUN apt install flex bison g++ make libpng-dev libicu-dev -y

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
