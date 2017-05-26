FROM ubuntu:trusty

MAINTAINER John Foster <johntfosterjr@gmail.com>

ENV HOME /root

RUN apt-get -qq update
RUN apt-get -yq install gcc \
                        build-essential \
                        libopenmpi-dev \
                        openmpi-bin \
                        libblas-dev \
                        liblapack-dev \
                        libboost-dev \
                        python \
                        git \
                        libyaml-cpp0.5 \
                        libyaml-cpp-dev \
                        openssh-server \
                        liboce-foundation-dev \ 
                        liboce-foundation8 \
                        liboce-modeling-dev \ 
                        liboce-modeling8 \
                        liboce-ocaf-dev \
                        liboce-ocaf8 \
                        curl

RUN curl -sSL https://cmake.org/files/v3.8/cmake-3.8.1-Linux-x86_64.tar.gz | sudo tar -xzC /opt;

RUN rm -rf cmake*

#Build Tadiga
WORKDIR /

ADD src src
ADD cmake cmake 
ADD CMakeLists.txt .

RUN mkdir build

WORKDIR build/
RUN /opt/cmake-3.8.1-Linux-x86_64/bin/cmake \
    -D CMAKE_BUILD_TYPE:STRING=Release \
    -D CMAKE_INSTALL_PREFIX:PATH=/usr/local/tadiga \
    -D BUILD_Trilinos:BOOL=ON \
    ..; \
    make -j8 && make install

WORKDIR /
RUN rm -rf build src cmake CMakeLists.txt

WORKDIR /output
ENV PATH /usr/local/tadiga/bin:$PATH

CMD    ["/usr/sbin/sshd", "-D"]
