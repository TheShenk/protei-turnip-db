FROM ubuntu:lunar
RUN apt update && apt install -y \
    cmake \
    git \
    g++ \
    libboost1.81-dev \
    libboost-system1.81-dev \
    libboost-program-options1.81-dev \
    libboost-log1.81-dev \
    libasio-dev \
    libtbb-dev

ADD src src
ADD tests tests
ADD CMakeLists.txt CMakeLists.txt

RUN mkdir build

WORKDIR build
RUN cmake ../ && cmake --build .
RUN ./tests

CMD ["./turnip-server"]
