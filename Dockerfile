FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive    

# install base dependences    
RUN apt-get update && \
    apt-get install -y make cmake git curl build-essential m4 sudo gdbserver \
    gdb libreadline-dev bison flex zlib1g-dev tmux zile zip vim gawk wget \
    libgflags-dev libgoogle-glog-dev libgtest-dev libssl-dev   

# add postgres user and make data dir        
RUN groupadd -r postgres && useradd --no-log-init -r -m -s /bin/bash -g postgres -G sudo postgres
ENV PGDATA /home/postgres/data
RUN /bin/rm -Rf "$PGDATA" && mkdir "$PGDATA"
WORKDIR "/home/postgres"

# get postgres source and compile with debug and no optimization
RUN git clone --branch REL_14_STABLE https://github.com/postgres/postgres.git --depth=1 && \
    cd postgres && ./configure \
    --prefix=/usr/ \
#    --enable-debug \
#    --enable-depend --enable-cassert --enable-profiling \
#    CFLAGS="-ggdb -Og -g3 -fno-omit-frame-pointer" \
#    CFLAGS="-O3" \
    && make -j 4 && make install

RUN curl -s -L https://github.com/theory/pgtap/archive/v0.99.0.tar.gz | tar zxvf - && \   
    cd pgtap-0.99.0 && make && make install

# chown dependencies    
RUN chown -R postgres:postgres /home/postgres

RUN mkdir /absl
RUN git clone https://github.com/abseil/abseil-cpp.git && \
    cd abseil-cpp* && \
    mkdir build && cd build && \
    cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX=/absl .. && \
    cmake --build . --target install && ldconfig

RUN mkdir /s2lib
RUN curl -s -L https://github.com/google/s2geometry/archive/refs/tags/v0.9.0.tar.gz | tar xzvf - && \
    cd s2geometry* && \
    mkdir build && cd build && \
    cmake -DCMAKE_PREFIX_PATH=/absl -DCMAKE_INSTALL_PREFIX=/usr .. && \
    make && make install && make clean && ldconfig

# put test stuff into pg home        
RUN mkdir "/home/postgres/pgs2"
WORKDIR "/home/postgres/pgs2"
COPY . .

RUN make && make install && make clean

# chown just pgs2
RUN chown -R postgres:postgres /home/postgres/pgs2
    
# make postgres a sudoer        
RUN echo "postgres ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/user && \
    chmod 0440 /etc/sudoers.d/user

# start the database            
USER postgres
RUN initdb -D "$PGDATA"
EXPOSE 5432
# wait forever
CMD tail -f /dev/null
