# drusible
Local Ubuntu Drupal Development playbook

### Instalation
- Install ansible (run install_ansible.sh)
- ansible-galaxy install -r requirements.yml
- Run ansible-playbook main.yml -i inventory -s -U drusible -vvv -e "git_user_name='name' git_user_email='email'"
-

### Testing on VM (latest virtualbox)
http://askubuntu.com/questions/451805/screen-resolution-problem-with-ubuntu-14-04-and-virtualbox#answer-595192
Fix shared folder issue: sudo adduser drusible vboxsf
ansible-playbook main.yml -i inventory -K -s -vvvv -e "git_user_name='name' git_user_email='email'"
ansible-playbook main.yml -i inventory -K -s -vvv
ansible 127.0.0.1 -c local -s -K -m setup