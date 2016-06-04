<?php
/**
 * @file
 * Adds block type commands to Coffee Extras.
 */

/**
 * Add coffee commands for beans.
 *
 * @param array $commands
 *   The commands array from hook_coffee_commands(), which is
 *   passed by reference.
 */
function coffee_extras_add_bean_commands(array &$commands) {
  $command = ':beans';

  foreach (bean_get_types() as $bean_type) {
    $bean_type_label = $bean_type->getLabel();
    // Add the edit bean type page.
    $commands[] = array(
      'value' => 'admin/structure/block-types/manage/' . $bean_type->type,
      'label' => t('Manage @bean_type', array('@bean_type' => $bean_type_label)),
      'command' => $command . ' ' . drupal_strtolower($bean_type->type),
    );
    // Add the 'Manage fields' page for each bean type.
    $commands[] = array(
      'value' => 'admin/structure/block-types/manage/' . $bean_type->type . '/fields',
      'label' => t('Manage fields for @bean_type', array('@bean_type' => $bean_type_label)),
      'command' => $command . ' ' . drupal_strtolower($bean_type->type),
    );
    // Add the 'Manage display' page for each bean type.
    $commands[] = array(
      'value' => 'admin/structure/block-types/manage/' . $bean_type->type . '/display',
      'label' => t('Manage display for @bean_type', array('@bean_type' => $bean_type_label)),
      'command' => $command . ' ' . drupal_strtolower($bean_type->type),
    );
  }
}
