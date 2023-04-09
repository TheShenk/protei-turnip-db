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
    libtbb-dev \
    doxygen

RUN git clone https://github.com/TheShenk/protei-turnip-db.git
WORKDIR protei-turnip-db

RUN mkdir build

WORKDIR build
RUN cmake ../ && cmake --build .

CMD ["./turnip-server"]
