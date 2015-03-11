<?php
/**
 * This is an include file.  These are the "callback" functions that drush
 * uses to get the job done.  See quickstart.drush.inc for the definition of
 * the commands.
 *
 * Example make file for d7 http://drupal.org/node/852412
 *
 * site-install issues:
 *  - http://drupal.org/node/992928 - Drupal Core
 *  - http://drupal.org/node/983914 - Drush
 * @file
 */

/**
 * Helper function for executing shell commands.  Throws exceptions on error.
 *
 * @param <type> $cmd the command to run
 * @param <type> $throwexception throw exception on error?
 */
function quickstart_shell_exec($cmd, $throwexception=true) {
  // Note: for shell commands: 0=success, non-zero=error code
  $ret = drush_shell_exec($cmd);
  if ($throwexception && !$ret) {
    $msg = "Command returned unexpected result: $cmd";
    $output = drush_shell_exec_output();
    foreach ($output as $line) {
      $msg="\n  $line";
    }
    throw new Exception($msg);
  }
}

/**
 * Helper function for dereferencing paths.
 *
 * @param <type> $pathin
 * @return <type>
 */
function quickstart_fixpath($pathin) {
  // fix ~'s
  $homedir = "/home/" . exec('whoami');
  $pathout = str_replace("~", $homedir, $pathin);
  // realpath fails on non-existant folders.  So it's hard to fix .'s and ..'s
  return $pathout;
}

/**
 * Create the DNS.  Edits /etc/hosts on local machine.
 * Entries in file are marked with #quickstart
 *
 * @param <type> $domain the domain to DNS
 * @param <type> $params
 */
function quickstart_create_dns($domain, $params) {
  $file = file_get_contents("/etc/hosts");
  // make sure to test for fully spaces parsed domain in hosts file.
  // otherwise shortened partial domains will throw an exception.
  $domainplus = " " . $domain . " ";
  if(!strpos($file, $domainplus)) {
    quickstart_shell_exec("echo '127.0.0.1 $domain #drusible' | sudo tee -a /etc/hosts");
  }else{
    $msg = $domain . " already exists...doing nothing";
    throw new Exception($msg);
  }
}

/**
 * Destroy the DNS.  Edit /etc/hosts file on local machine
 *
 * @param <type> $domain
 * @param <type> $params
 */
function quickstart_destroy_dns($domain, $params) {
  quickstart_shell_exec("sudo sed -i \"/ $domain .*#drusible/d\" /etc/hosts");
}

/**
 * Configure nginx virtualhost file using the template.
 * Files put in /etc/nginx/sites-available/$domain.
 * Runs: apache2 restart
 *
 * @param <type> $domain
 * @param <type> $params 'codepath'
 */
function quickstart_create_nginx($domain, $params) {
  // get codepath and make sure it exists.
  $codepath = $params['codepath'];

  if (!file_exists($codepath)) mkdir($codepath, 0770, true);

  // get template
  $str_config = file_get_contents(dirname(__FILE__) . '/nginx.template');

  // make our own :-)
  $str_config = str_replace("#DOMAIN#", $domain, $str_config);
  $str_config = str_replace("#CODEPATH#", $codepath, $str_config);

  $config_handle = fopen("/etc/nginx/sites-available/$domain", "w+");
  fwrite($config_handle, $str_config);

  // enable using nginx_ensite
  quickstart_shell_exec("sudo nginx_ensite $domain");

  // restart nginx
  // use sysvinit scripts instead of upstart for more compatibility(debian, etc)
  quickstart_shell_exec("sudo service nginx restart");
}

/**
 * Destroy the apache virtual hosts config. a2dissite, then rm file.
 * Runs: apache2 restart
 *
 * @param <type> $domain
 * @param <type> $params
 */
function quickstart_destroy_apache($domain, $params) {
  quickstart_shell_exec("sudo a2dissite $domain", false);
  $filename = "/etc/apache2/sites-available/$domain";
  if (file_exists($filename)) unlink($filename);  // unlink = delete file
  // use sysvinit scripts instead of upstart for more compatibility(debian, etc)
  quickstart_shell_exec("sudo /etc/init.d/apache2 restart");
}
