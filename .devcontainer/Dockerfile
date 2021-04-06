FROM ubuntu:20.04

ARG USER

RUN apt update
RUN export DEBIAN_FRONTEND=noninteractive && apt install -y locales sudo

ENV ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

RUN export DEBIAN_FRONTEND=noninteractive \
    && apt install -y nano git bash-completion bc curl python3 python3-pip python3-venv

RUN curl https://static.dev.sifive.com/dev-tools/riscv-openocd-0.10.0-2020.04.6-x86_64-linux-ubuntu14.tar.gz -o /root/openocd.tar.gz \
    && tar -zxvf /root/openocd.tar.gz -C /root --one-top-level=openocd --strip-components=1

RUN curl https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14.tar.gz -o /root/gnu-tools.tar.gz \
    && tar -zxvf /root/gnu-tools.tar.gz -C /root --one-top-level=gnu-tools --strip-components=1

ENV RISCV_OPENOCD_PATH /root/openocd
ENV RISCV_PATH /root/gnu-tools

RUN useradd -m -s /bin/bash felix

USER ${USER}
