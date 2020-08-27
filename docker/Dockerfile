FROM ubuntu:16.04 AS download-tarballs

ARG RISCV_TOOLS_TARBALL=riscv64-unknown-elf-gcc-10.1.0-2020.07.0-x86_64-linux-ubuntu14.tar.gz
ARG RISCV_PICOLIBC_TARBALL=riscv64-unknown-elf-picolibc-1.4.6-2020.07.0-x86_64-linux-ubuntu14.tar.gz
ARG QEMU_TARBALL=riscv-qemu-4.1.0-2019.08.0-x86_64-linux-ubuntu14.tar.gz

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
    rsync \
    wget

# Install picolibc
RUN wget --no-verbose https://github.com/keith-packard/picolibc/releases/download/1.4.6/${RISCV_PICOLIBC_TARBALL} && \
    tar xzf ${RISCV_PICOLIBC_TARBALL}

# Install RISC-V Toolchain
RUN wget --no-verbose https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.07/${RISCV_TOOLS_TARBALL} && \
    tar xzf ${RISCV_TOOLS_TARBALL} && \
    mkdir -p /tools && \
    rsync -a ${RISCV_TOOLS_TARBALL%.tar.gz}/* /tools/

# Install QEMU
RUN wget --no-verbose https://static.dev.sifive.com/dev-tools/${QEMU_TARBALL} && \
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
