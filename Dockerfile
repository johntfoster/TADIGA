FROM ubuntu:trusty

MAINTAINER John Foster <johntfosterjr@gmail.com>

ENV HOME /root

RUN apt-get -qq update
RUN apt-get -yq install software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get -qq update
RUN apt-get -yq install gcc-5 \
                        g++-5 \
                        build-essential \
                        libblas-dev \
                        liblapack-dev \
                        libboost-dev \
                        python \
                        git \
                        libyaml-cpp0.5 \
                        libyaml-cpp-dev \
                        openssh-server \
                        curl

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 90
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 90

RUN curl -sSL https://cmake.org/files/v3.8/cmake-3.8.1-Linux-x86_64.tar.gz | sudo tar -xzC /opt;

RUN rm -rf cmake*

#Build Tadiga
WORKDIR /

RUN git clone https://github.com/johntfoster/TaDIgA.git
WORKDIR /TaDIgA
RUN git checkout trilinos
RUN git checkout origin/master -- cmake/*

RUN mkdir -p /TaDIgA/build

WORKDIR /TaDIgA/build/
RUN /opt/cmake-3.8.1-Linux-x86_64/bin/cmake ..; make -j8

WORKDIR /
RUN rm -rf cmake CMakeLists.txt trilinos-src trilinos-build trilinos-download
