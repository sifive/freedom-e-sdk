FROM ubuntu:20.04

ARG USER

ARG TOOL_FOLDER

ENV TOOL_FOLDER ${TOOL_FOLDER:-/home/${USER}/sifive-tools}

RUN apt update
RUN export DEBIAN_FRONTEND=noninteractive && apt install -y locales sudo screen

ENV ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

RUN export DEBIAN_FRONTEND=noninteractive \
    && apt install -y nano git bash-completion bc curl python3 python3-pip python3-venv

RUN useradd -m -s /bin/bash ${USER} \
    && passwd -d ${USER} \
    && usermod -aG sudo ${USER}

USER ${USER}

RUN mkdir ${TOOL_FOLDER}

RUN curl https://static.dev.sifive.com/dev-tools/riscv-openocd-0.10.0-2020.04.6-x86_64-linux-ubuntu14.tar.gz -o ${TOOL_FOLDER}/openocd.tar.gz \
    && tar -zxvf ${TOOL_FOLDER}/openocd.tar.gz -C ${TOOL_FOLDER} --one-top-level=openocd --strip-components=1

RUN curl https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14.tar.gz -o ${TOOL_FOLDER}/gnu-tools.tar.gz \
    && tar -zxvf ${TOOL_FOLDER}/gnu-tools.tar.gz -C ${TOOL_FOLDER} --one-top-level=gnu-tools --strip-components=1

RUN curl https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv-qemu-5.1.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz -o ${TOOL_FOLDER}/riscv-qemu.tar.gz \
    && tar -zxvf ${TOOL_FOLDER}/riscv-qemu.tar.gz -C ${TOOL_FOLDER} --one-top-level=riscv-qemu --strip-components=1

ENV RISCV_OPENOCD_PATH ${TOOL_FOLDER}/openocd
ENV RISCV_PATH ${TOOL_FOLDER}/gnu-tools

ENV PATH=$PATH:RISCV_OPENOCD_PATH/bin:${RISCV_PATH}/bin:${TOOL_FOLDER}/riscv-qemu/bin