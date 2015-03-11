#! /bin/bash

# Only install if not exists
if [ ! -x /usr/bin/ansible ]; then
  echo ">>> Installing ansible";

  apt-get update
  apt-get install python-pip python-dev git -y
  
  pip install PyYAML jinja2 paramiko
  git clone https://github.com/ansible/ansible.git
  
  cd ansible
  # fix error https://github.com/ansible/ansible/issues/5412
  git submodule update --init --recursive
  
  make install
  mkdir /etc/ansible
  
  cp ~/ansible/examples/hosts /etc/ansible/
  ln -s /root/ansible/bin/ansible /usr/bin/ansible
fi
