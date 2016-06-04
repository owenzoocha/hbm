<?php
/**
 * @file
 * Adds views commands to Coffee Extras.
 */

/**
 * Add coffee commands for views.
 *
 * @param array $commands
 *   The commands array from hook_coffee_commands(), which is
 *   passed by reference.
 */
function coffee_extras_add_views_commands(array &$commands) {
  $views = views_get_all_views();

  $command = ':views';
  foreach ($views as $view) {
    if (empty($view->disabled) || !$view->disabled) {
      // For enabled views, add an edit link.
      $commands[] = array(
        'value' => 'admin/structure/views/view/' . $view->name . '/edit',
        'label' => t('Edit @view view', array('@view' => $view->human_name)),
        'command' => $command . ' ' . drupal_strtolower($view->name),
      );
    }
  }
}
