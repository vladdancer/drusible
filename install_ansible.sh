#! /bin/bash

# Only install if not exists
if [ ! -x /usr/bin/ansible ]; then
  echo ">>> Installing ansible";

  #apt-get install software-properties-common
  apt-add-repository ppa:ansible/ansible -y
  apt-get update
  apt-get install ansible -y
fi
