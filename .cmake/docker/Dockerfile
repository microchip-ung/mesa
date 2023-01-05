# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

FROM ubuntu:20.04

# Suppress time zone questions during build
ENV TZ=Europe/Copenhagen

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
  && echo $TZ > /etc/timezone \
  && apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y \
# Packages sorted alphabetically
    build-essential \
    cmake \
    cmake-curses-gui \
    git \
    iputils-ping \
    libjson-c-dev \
    libpcap-dev \
    locales \
    ruby-full \
    ruby-parslet \
    sudo \
    wget \
    zlib1g-dev \
    zlibc \
# Cleanup
  && rm -rf /var/lib/apt/lists/* \
# Generate en_US.UTF-8 locale
  && locale-gen en_US.UTF-8 \
# Update locate to en_US.UTF-8
  && update-locale LANG=en_US.UTF-8 LANGUAGE=en \
# git needs a user
  && git config --system user.email "br@example.com" && git config --system user.name "Build Root" \
  # Support Microsemi version
  && ln -s /usr/local/bin/mchp-install-pkg /usr/local/bin/mscc-install-pkg

# TBD Use bundler instead?
RUN sudo gem install nokogiri -v '1.10.8' --source 'https://rubygems.org/'
RUN sudo gem install asciidoctor -v '2.0.8' --source 'https://rubygems.org/'
RUN sudo gem install mini_portile2 -v '2.4.0' --source 'https://rubygems.org/'

# Set locale
ENV LANG='en_US.UTF-8' LC_ALL='en_US.UTF-8'

# buildroot-layer needs this for installing missing toolchains
COPY ./mchp-install-pkg /usr/local/bin

# Add simple grid client as this is needed to dispatch sub-jobs in the internal
# mchp building environment
COPY ./SimpleGridClient /usr/local/bin

RUN gem install hexdump packetfu ox
ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/easytest/easytest/utils/:/easytest/easytest/test-setup-server/
RUN mkdir /easytest && cd /easytest && git clone https://bitbucket.microchip.com/scm/unge/sw-tools-easytest.git easytest

# A common entrypoint for setting up things before running the user command(s)
COPY ./entrypoint.sh /entrypoint.sh
RUN mkdir /mapped_home

ENV HOME=/tmp/$USER

ENTRYPOINT [ "/entrypoint.sh" ]
