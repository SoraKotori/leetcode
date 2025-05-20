FROM ubuntu:24.04 AS base

RUN apt-get update

RUN apt-get install -y --no-install-recommends \
    cmake ninja-build

RUN apt-get install -y --no-install-recommends \
    gcc-14 g++-14

RUN apt-get install -y --no-install-recommends \
    libgtest-dev

FROM base AS development

RUN apt-get update

RUN apt-get install -y --no-install-recommends \
    gdb

RUN apt-get install -y --no-install-recommends \
    git \
    ca-certificates # for https
