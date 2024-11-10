# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

###############################################################################
FROM ubuntu:oracular-20241009 AS ubuntu_base

ENV TZ=Europe/Copenhagen LANG='en_US.UTF-8' LC_ALL='en_US.UTF-8' LANGUAGE=en

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
  && echo $TZ > /etc/timezone \
  && apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y \
    build-essential \
    ca-certificates \
    curl \
    git \
    git-lfs \
    gpg \
    iputils-ping \
    jq \
    locales \
    wget \
  && locale-gen en_US.UTF-8 \
  && update-locale LANG=en_US.UTF-8 LANGUAGE=en

# Needed when running from within Microchip network
# From https://pitstop.microchip.com/Certs/
COPY ./.cmake/docker/mchp-ca.cer /usr/share/ca-certificates/mchp-ca.crt
COPY ././.cmake/docker/Cisco_Umbrella_Root_CA.cer /usr/share/ca-certificates/cisco-umbrella-primary.crt

RUN sh -c "echo mchp-ca.crt >> /etc/ca-certificates.conf" \
 && sh -c "echo cisco-umbrella-primary.crt >> /etc/ca-certificates.conf" \
 && update-ca-certificates --fresh


###############################################################################
FROM ubuntu_base AS build-env-oss

RUN apt-get install -y \
    cmake \
    cmake-curses-gui \
    libjson-c-dev \
    libpcap-dev \
    ninja-build \
    ruby-full \
    ruby-parslet \
    sudo \
    zlib1g-dev

RUN gem install nokogiri -v '1.15.3' --source 'https://rubygems.org/' \
 && gem install asciidoctor -v '2.0.8' --source 'https://rubygems.org/' \
 && gem install mini_portile2 -v '2.8.2' --source 'https://rubygems.org/' \
 && gem install json_schemer -v '2.3.0' --source 'https://rubygems.org/' \
 && gem install hexdump packetfu ox

ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/easytest/easytest/utils/:/easytest/easytest/test-setup-server/
RUN mkdir /easytest \
 && cd /easytest \
 && git clone https://bitbucket.microchip.com/scm/unge/sw-tools-easytest.git easytest

# A common entrypoint for setting up things before running the user command(s)
COPY ./.cmake/docker/entrypoint.sh /entrypoint.sh
RUN mkdir /mapped_home

# TODO, remove once backwards compatibility is not needed any longer
COPY ./.cmake/docker/SimpleGridClient /usr/local/bin
COPY ./.cmake/docker/mscc-download-pkg /usr/local/bin/.
COPY ./.cmake/docker/mscc-install-pkg /usr/local/bin

ENTRYPOINT [ "/entrypoint.sh" ]


###############################################################################
FROM ubuntu_base AS build-env-bsp

RUN mkdir /opt/mchp
RUN mkdir /opt/mscc

RUN chown root:users /opt/mchp
RUN chown root:users /opt/mscc

RUN chmod 775  /opt/mchp
RUN chmod 775  /opt/mscc

COPY ./.cmake/deps-toolchain.json .
COPY ./.cmake/toolchain-install.sh .
RUN ./toolchain-install.sh
RUN rm deps-toolchain.json toolchain-install.sh

###############################################################################
FROM scratch AS build-env-mchp

COPY --from=build-env-oss / /
COPY --from=build-env-bsp /opt/ /opt/

ENTRYPOINT [ "/entrypoint.sh" ]
