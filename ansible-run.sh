#!/usr/bin/env bash
echo ">>> Prepare installation"
sudo sh install_ansible.sh
sudo ansible-galaxy install -r requirements.yml --force
echo ">>> Starting installation"
ansible-playbook main.yml -i inventory -s -K
echo ">>> Installation complete"
