Drusible
==========
[![Build Status](https://travis-ci.org/drupalway/drusible.svg)](https://travis-ci.org/drupalway/drusible)
##Ubuntu Drupal Development playbook
inspired by:
- [mac-dev-playbook] [1]
- [lazydubuntu] [2]
- [Drupalpro] [3]

--------------------------------

### Instalation
```
sudo install_ansible.sh
sudo ansible-galaxy install -r requirements.yml
ansible-playbook main.yml -i inventory -s -K
```
### Testing on VM (latest virtualbox)
http://askubuntu.com/questions/451805/screen-resolution-problem-with-ubuntu-14-04-and-virtualbox#answer-595192
Fix shared folder issue: ```sudo adduser <some user> vboxsf```
To get a list of ansible host variables: 
``` ansible 127.0.0.1 -c local -s -K -m setup```


----------

### Table of contents
[TOC]

[1]: https://github.com/geerlingguy/mac-dev-playbook
[2]: http://lazydubuntu.com/ "lazydubuntu"
[3]: http://drupal.org/project/drupalpro "Drupalpro"
