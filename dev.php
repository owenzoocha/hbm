<?php
/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

function testerr() {
  dpm('howdy!');
  return '';
}

//testerr();

menu_execute_active_handler();
// delete_out_of_date();
//owen_pp_refund();
//owen_pp_delayed();
