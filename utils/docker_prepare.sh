#!/usr/bin/env bash
set -xe

if [[ -f "/etc/centos-release" ]]; then
    rpm --import https://repo.almalinux.org/almalinux/RPM-GPG-KEY-AlmaLinux
    dnf config-manager --set-enabled powertools
    dnf install -y epel-release

    for i in $(seq 1 5); do
        yum install -y zlib-devel curl-devel expat-devel libpng-devel curl zip unzip tar ninja-build && s=0 && break || s=$? && sleep 15;
    done

    [ $s -eq 0 ] || exit $s

elif [[ -f "/etc/alpine-release" ]]; then
    apk add curl-dev expat-dev zlib-dev libpng-dev zip unzip tar ninja-build
fi

# Setup sccache cache directory
curl -L https://github.com/mozilla/sccache/releases/download/v0.10.0/sccache-v0.10.0-x86_64-unknown-linux-musl.tar.gz | tar xz
mv sccache*/sccache /usr/local/bin/
chmod +x /usr/local/bin/sccache

mkdir -p /output

HOST_SCCACHE_DIR="/host${HOST_SCCACHE_DIR:-/home/runner/work/rollnw-py/rollnw-py/.sccache}"
if [ -d "$HOST_SCCACHE_DIR" ]; then
    cp -R "$HOST_SCCACHE_DIR" /output/.sccache
fi

ls -la /output/

export SCCACHE_DIR=/output/.sccache
