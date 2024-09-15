FROM ubuntu:24.04

RUN apt update -y
RUN apt upgrade -y
RUN apt install git -y
RUN git clone --depth=1 https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
RUN apt install python3 -y
RUN apt install xz-utils -y
RUN ./emsdk install latest
RUN ./emsdk activate latest
ENV EMSDK=/emsdk
ENV PATH="/emsdk:/emsdk/upstream/emscripten:/emsdk/node/18.20.3_64bit/bin:${PATH}"
RUN echo 'int main(){return 0;}' > hello.cpp && em++ -s USE_LIBPNG=1 -s USE_ICU=1 hello.cpp && rm a.out.wasm a.out.js

RUN apt install flex bison make g++ vim -y

RUN cp /usr/include/FlexLexer.h /usr/local/include

RUN mkdir /context-free
WORKDIR /context-free
COPY Makefile .
COPY src-agg ./src-agg
COPY src-common ./src-common
COPY src-unix ./src-unix
RUN mkdir ./input
COPY ./input/*.cfdg ./input
RUN TARGET=wasm emmake make
RUN mv cfdg cfdg.js
COPY src-js/main.js cfdg
RUN touch cfdg # avoid make recompiling stuff
COPY ./input/*.SKIP ./input
COPY ./input/tests ./input/tests
COPY ./runtests.sh .
RUN make test
