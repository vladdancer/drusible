<?php 

include("quickstart.inc");

/**
 * Simple helper function to keep all the arguments in a list.
 * @return <type>
 */
function _quickstart_arg_list() {
  return array('code'=>'code', 'database'=>'database', 'apache'=>'apache', 'dns'=>'dns', 'install'=>'install');
}

/**
 * Implements hook_drush_command()
 * @return array
 */
function quickstart_drush_command() {
  $items = array();

  $items['quickstart-create'] = array(
          'description' => "Create a development website (" . implode(', ', _quickstart_arg_list()) . ").",
          'arguments' => array(
                  'what' => 'Optional. One or more items to create: [' . implode('|', _quickstart_arg_list()) . '|all] Defaults to "all"',
          ),
          'options' => array(
                  'domain'       => 'Required (all).  Domain name of new site.  Use this to reference site with other commands.  Becomes dns, dbname, dbuser, dbpass, site-name, and kitchen-sink',
                  'codepath'     => 'Optional (apache,code,install).  Path to drupal code.  Defaults to "~/websites/[domain]"',
          ),
          'examples' => array(),
          'aliases' => array('qc'),
          'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  $items['quickstart-destroy'] = array(
          'description' => "Destroy a development website (" . implode(', ', _quickstart_arg_list()) . ").",
          'arguments' => array(
                  'what' => 'Optional. One or more items to destroy: [' . implode('|', _quickstart_arg_list()) . '|all] Defaults to "all"',
          ),
          'options' => array(
                  'domain' => 'Domain name to destroy.',
                  'codepath' => 'Path to drupal code.  Defaults to ~/websites/[domain]',
                  'yes'      => 'Optional. Skip confirmation',
          ),
          'examples' => array(
                  'Simplest format' => 'drush qd --domain=example.dev',
                  'Complete format' => 'drush quickstart-destroy all --domain=example.dev --codepath=/path/to/drupal',
                  'Only Remove Apache (/etc/apache2/sites-enabled/)' => 'drush quickstart-destroy apache --domain=example.dev',
          ),
          'aliases' => array('qd'),
          'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );

  $items['quickstart-fixperms'] = array(
          'description' => "Fix permissions for a development website:
  \$ sudo chown -R :www-data <codepath>
  \$ sudo chmod -R a=,u=rwX,g=rX <codepath>
  \$ sudo find <codepath>/sites -type d -name files -exec chmod -R a=,ug=rwX '{}' \;
  \$ sudo find <codepath>/sites -type d -name files_private -exec chmod -R a=,ug=rwX '{}' \;",
          'arguments' => array(
          ),
          'options' => array(
                  'domain' => 'Domain name to fix permissions.',
                  'codepath' => 'Path to drupal code.  Defaults to ~/websites/[domain]',
          ),
          'examples' => array(
                  'Simplest format' => 'drush qf --domain=example.dev',
                  'Use different codepath' => 'drush quickstart-fixperms --domain=example.dev --codepath=/path/to/drupal',
          ),
          'aliases' => array('qf'),
          'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap at all.
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function quickstart_drush_help($section) {
  switch ($section) {
  }
}

/**
 * Helper function to check input parameters
 * @param  $required any parameters that are required
 * @return array  if $ret['fail'] is true, then check failed, and an error was logged.
 */
function _quickstart_params($required) {
  // check arguments
  $commands = drush_get_arguments();
  $options = drush_get_context('cli');
  $ret = array();

  // Commands

  // what steps do we take: "" -> "all" -> all our setup steps.
  if (count($commands)==1) {
    $commands = array("all");
  }
  if(array_search("all", $commands)!==false) {
    $commands = _quickstart_arg_list();
  }

  // Options

  // Domain always required
  // remove /'s
  $options['domain'] = str_replace('/', '', $options['domain']);
  if (strlen($options['domain']) > 15) {
    $ret['fail'] = true;
    drush_log("  '--domain' must be less than 16 characters long, for mysql user name to work.", 'error');
  }
  if (strlen($options['domain']) < 3) {
    $ret['fail'] = true;
    drush_log("  '--domain' must be at least 3 characters long.", 'error');
  }
  if (strpos($options['domain'], '.')===false) {
    $ret['fail'] = true;
    drush_log("  '--domain' must include a . for drupal installer to work.", 'error');
  }

  // defaults
  $defaults['domain_'] = $domain_ = str_replace('.','_',$options['domain']);
  // apache, code, install
  $defaults['codepath'] = quickstart_fixpath("~/websites/" . $options['domain']);

  // Merge it all together - 2nd array overwrites first.
  $ret = array_merge($ret, $commands);
  $ret = array_merge($ret, $defaults);
  $ret = array_merge($ret, $options);

  // Check required
  foreach($required as $require) {
    if (empty($ret[$require])) {
      $ret['fail'] = true;
      drush_log("  '--$require' is a required option for this command.", 'error');
    }
  }
  return $ret;
}
