# KeePassXC Linux Release Build Dockerfile
# Copyright (C) 2017 KeePassXC team <https://keepassxc.org/>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 or (at your option)
# version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# TIP: check this Dockerfile using this online tool: https://www.fromlatest.io

FROM ubuntu:14.04

ENV REBUILD_COUNTER=2

ENV QT5_VERSION=53
ENV QT5_PPA_VERSION=${QT5_VERSION}2

RUN set -x \
     && apt-get update -y \
     && apt-get -y install software-properties-common

RUN set -x \
    && add-apt-repository ppa:beineri/opt-qt${QT5_PPA_VERSION}-trusty \
    && add-apt-repository ppa:phoerious/keepassxc

RUN set -x \
    && apt-get -y update \
    && apt-get -y --no-install-recommends install \
      build-essential \
      clang-3.6 \
      libclang-common-3.6-dev \
      clang-format-3.6 \
      cmake3 \
      make \
      libgcrypt20-18-dev \
      libargon2-0-dev \
      libsodium-dev \
      qt${QT5_VERSION}base \
      qt${QT5_VERSION}tools \
      qt${QT5_VERSION}x11extras \
      qt${QT5_VERSION}translations \
      zlib1g-dev \
      libyubikey-dev \
      libykpers-1-dev \
      libxi-dev \
      libxtst-dev \
      xvfb

ENV CMAKE_PREFIX_PATH="/opt/qt${QT5_VERSION}/lib/cmake"
ENV CMAKE_INCLUDE_PATH="/opt/libgcrypt20-18/include:/opt/gpg-error-127/include"
ENV CMAKE_LIBRARY_PATH="/opt/libgcrypt20-18/lib/x86_64-linux-gnu:/opt/gpg-error-127/lib/x86_64-linux-gnu"
ENV LD_LIBRARY_PATH="/opt/qt${QT5_VERSION}/lib:/opt/libgcrypt20-18/lib/x86_64-linux-gnu:/opt/gpg-error-127/lib/x86_64-linux-gnu"
RUN set -x \
    && echo "/opt/qt${QT_VERSION}/lib" > /etc/ld.so.conf.d/qt${QT5_VERSION}.conf \
    && echo "/opt/libgcrypt20-18/lib/x86_64-linux-gnu" > /etc/ld.so.conf.d/libgcrypt20-18.conf \
    && echo "/opt/gpg-error-127/lib/x86_64-linux-gnu" > /etc/ld.so.conf.d/libgpg-error-127.conf

RUN set -x \
    && apt-get autoremove --purge \
    && rm -rf /var/lib/apt/lists/*

VOLUME ["/keepassxc"]
WORKDIR /keepassxc
