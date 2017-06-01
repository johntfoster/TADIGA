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

ADD src src
ADD cmake cmake 
ADD CMakeLists.txt .

RUN mkdir build

WORKDIR build/
RUN /opt/cmake-3.8.1-Linux-x86_64/bin/cmake \
    -D CMAKE_BUILD_TYPE:STRING=Debug \
    -D CMAKE_INSTALL_PREFIX:PATH=/usr/local/tadiga \
    -D BUILD_Trilinos:BOOL=ON \
    -D BUILD_OpenCASCADE:BOOL=ON \
    -D COVERAGE:BOOL=ON \
    ..; \
    make -j8 && make install

WORKDIR /
RUN rm -rf cmake CMakeLists.txt oce-download oce-build oce-src trilinos-src trilinos-build trilinos-download

WORKDIR /output
ENV PATH /usr/local/tadiga/bin:$PATH

CMD    ["/usr/sbin/sshd", "-D"]
