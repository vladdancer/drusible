#!/usr/bin/env bash
# If PHPStorm_templates not exist - install it, otherwise update.
if [ ! -d ~/drusible/PHPStorm_templates ]; then
  # Create directory for PHPStorm templates.
  mkdir ~/drusible/PHPStorm_templates
  # Clone PHPStorm templates repo into PHPStorm_templates directory.
  cd ~/drusible/PHPStorm_templates/
  git clone https://github.com/Sweetchuck/WebIdeConfigManager.git
  # Clone PHPStorm templates for Drupal
  cd WebIdeConfigManager/ConfigHome
  git clone --recursive --branch 7.x-1.x http://git.drupal.org/project/phpstorm_templates.git drupal
  # Push new templates to apply it to the PHPStorm IDE.
  cd ..
  ./WebIdeConfigManager.php push
  else
    cd ~/drusible/PHPStorm_templates/WebIdeConfigManager/ConfigHome/drupal
    git pull
    cd ../..
    ./WebIdeConfigManager.php push -h drupal
fi
