#!/usr/bin/env bash
# If PHPStorm_templates not exist - install it, update otherwise.
if [ ! -d ~/drusible/PHPStorm_templates ]; then
  # Clone PHPStorm templates repo into PHPStorm_templates directory.
  git clone https://github.com/Sweetchuck/WebIdeConfigManager.git ~/drusible/PHPStorm_templates
  # Clone PHPStorm templates for Drupal.
  git clone --recursive -b 7.x-1.x http://git.drupal.org/project/phpstorm_templates.git ~/drusible/PHPStorm_templates/ConfigHome/drupal
  # Push new templates to apply it to the PHPStorm IDE.
  ~/drusible/PHPStorm_templates/WebIdeConfigManager.php push
else
  cd ~/drusible/PHPStorm_templates/ConfigHome/drupal
  git pull
  cd ../..
  ./WebIdeConfigManager.php push -h drupal
  # Go back to the home directory.
  cd ~
fi
