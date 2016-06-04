<?php
/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

function testerr() {
  $res = db_query("SELECT info FROM system WHERE type = 'module' AND status = 1 ORDER BY name");
  $result2 = $res->fetchAll();
  dpm($result2);
  foreach ($result2 as $key => $value) {
    dpm($value->info);
  }
  // return '';
}

testerr();

menu_execute_active_handler();
// delete_out_of_date();
//owen_pp_refund();
//owen_pp_delayed();
