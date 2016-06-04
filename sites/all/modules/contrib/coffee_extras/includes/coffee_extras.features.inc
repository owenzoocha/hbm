<?php
/**
 * @file
 * Adds features commands to Coffee Extras.
 */

/**
 * Add coffee commands for features.
 *
 * @param array $commands
 *   The commands array from hook_coffee_commands(), which is
 *   passed by reference.
 */
function coffee_extras_add_features_commands(array &$commands) {
  $features = features_get_features(NULL, TRUE);
  // Have to load this file in order to check feature status.
  module_load_include('inc', 'features', 'features.export');

  $command = ':features';
  if (is_array($features)) {
    foreach ($features as $feature) {
      // Return the actual status of the feature
      // (e.g. overridden or needs review),
      // not just whether the feature is enabled.
      $status = features_get_storage($feature->name);

      // Only add links for non-hidden features.
      if (empty($feature->info['hidden'])) {
        $commands[] = array(
          'value' => 'admin/structure/features/' . $feature->name,
          'label' => t('View @feature feature', array('@feature' => $feature->info['name'])),
          'command' => $command . ' ' . drupal_strtolower($feature->name),
        );
        $commands[] = array(
          'value' => 'admin/structure/features/' . $feature->name . '/recreate',
          'label' => t('Recreate @feature feature', array('@feature' => $feature->info['name'])),
          'command' => $command . ' ' . drupal_strtolower($feature->name),
        );
        // If feature is in an "overridden" or "needs review",
        // add a link to the diff page.
        if (in_array($status, array(FEATURES_OVERRIDDEN, FEATURES_NEEDS_REVIEW)) && module_exists('diff')) {
          $commands[] = array(
            'value' => 'admin/structure/features/' . $feature->name . '/diff',
            'label' => t('Review overrides for @feature feature', array('@feature' => $feature->info['name'])),
            'command' => $command . ' ' . drupal_strtolower($feature->name),
          );
        }
      }
    }
  }
}
