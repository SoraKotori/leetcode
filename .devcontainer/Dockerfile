FROM ubuntu:24.04 as base

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
    cmake ninja-build

RUN apt-get install -y --no-install-recommends \
    gcc-14 g++-14

FROM base as development

RUN apt-get install -y --no-install-recommends \
    gdb

RUN apt-get install -y --no-install-recommends \
    git \
    ca-certificates # for https
