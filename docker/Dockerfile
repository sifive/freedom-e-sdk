FROM ubuntu:16.04 AS download-tarballs

ARG SIFIVE_TOOLS_URL=https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08

ARG RISCV_TOOLS_TARBALL=riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz
ARG RISCV_SEGGER_LIBC_TARBALL=segger_libc-2020.08.2.tar.bz2
ARG QEMU_TARBALL=riscv-qemu-5.1.0-2020.08.1-x86_64-linux-ubuntu14.tar.gz

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
    bzip2 \
    rsync \
    wget

# Install RISC-V Toolchain
RUN wget --no-verbose ${SIFIVE_TOOLS_URL}/${RISCV_TOOLS_TARBALL} && \
    tar xzf ${RISCV_TOOLS_TARBALL} && \
    mkdir -p /tools && \
    rsync -a ${RISCV_TOOLS_TARBALL%.tar.gz}/* /tools/

# Install Segger libc
COPY ./segger-libc/${RISCV_SEGGER_LIBC_TARBALL} ./
RUN tar xjf ${RISCV_SEGGER_LIBC_TARBALL} && \
    cd ${RISCV_SEGGER_LIBC_TARBALL%.tar.bz2} && \
    RISCV_TOOL_PATH=/tools ./libc_segger_install.sh

# Install QEMU
RUN wget --no-verbose ${SIFIVE_TOOLS_URL}/${QEMU_TARBALL} && \
    tar xzf ${QEMU_TARBALL} && \
    mkdir -p /tools && \
    rsync -a ${QEMU_TARBALL%.tar.gz}/* /tools/

FROM ubuntu:16.04

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
    build-essential \
    device-tree-compiler \
    git \
    jq \
    libfdt-dev \
    python3 \
    python3-pip \
    python3-venv \
# QEMU dependencies
    libpixman-1-0 \
    libnuma1 \
    libpng12-0 \
    libglib2.0-0 \
    libjpeg8

# Copy RISC-V toolchain and QEMU from first-stage
COPY --from=download-tarballs /tools /

# Copy freedom-e-sdk into container
RUN mkdir freedom-e-sdk
COPY ./ freedom-e-sdk/

# Set up the Python Virtualenv
RUN make -C ./freedom-e-sdk virtualenv

# Build and install freedom-devicetree-tools
RUN cd ./freedom-e-sdk/freedom-devicetree-tools && \
    ./configure --prefix=/tools/ && \
    make -j$(nproc) install

ENV PATH=/tools/bin:$PATH

WORKDIR ./freedom-e-sdk
