FROM johntfoster/tadiga:trilinos

MAINTAINER John Foster <johntfosterjr@gmail.com>

ENV HOME /root

RUN apt-get -qq update
RUN apt-get -yq install libgl2ps-dev libfreeimage-dev libtbb-dev


WORKDIR /

RUN git clone https://github.com/johntfoster/TaDIgA.git
WORKDIR /TaDIgA
RUN git checkout opencascade
RUN git checkout origin/master -- cmake/*

RUN mkdir -p /TaDIgA/build

WORKDIR /TaDIgA/build/
RUN /opt/cmake-3.8.1-Linux-x86_64/bin/cmake ..; make -j8

WORKDIR /
RUN rm -rf TaDIgA
