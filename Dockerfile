FROM ubuntu:20.04

WORKDIR /NestFuzzer
COPY . .
RUN apt-get update && apt-get -y install vim git wget curl