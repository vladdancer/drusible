#!/usr/bin/env bash
# Enable the canonical partner repo.
sed -i "/^# deb .*partner/ s/^# //" /etc/apt/sources.list
# Update apt-cache.
apt-get update
# Install skype.
apt-get install skype
