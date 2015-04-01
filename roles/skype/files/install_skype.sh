#!/usr/bin/env bash
# Enable the canonical partner repo.
sudo sed -i "/^# deb .*partner/ s/^# //" /etc/apt/sources.list
# Update apt-cache.
sudo apt-get update -y
# Install skype.
sudo apt-get install skype -y
