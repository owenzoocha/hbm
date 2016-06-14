<?php
/**
 * @file
 * Provides form functionality to publish jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to publish a job.
 */
function models_forms_confirm_clients_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);

  $desc = t('You are confirming the following clients:');

  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p><ul id="selected-clients-popup"></ul>',
  );

  $form['clients_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'clients_hidden'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('continue'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("saving.."),
      'data-complete-text' => array('saved!'),
    ),
  );
  return $form;
}

function models_forms_confirm_clients_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  if (!empty($form_state['values']['clients_hidden'])) {
    $eids = explode(',', rtrim($form_state['values']['clients_hidden'], ','));
    foreach ($nw->field_hb_users_eck->getIterator() as $key => $uw) {
      if (in_array($uw->getIdentifier(), $eids)) {
        $uw->field_client_selected->set(1);
      }
      else {
        $uw->field_client_selected->set(0);
      }
      $uw->save();
    }
    if (!$nw->field_hb_assigned->value()) {
      $nw->field_hb_assigned->set(1);
    }
    $nw->field_hb_client_size->set(sizeof($eids));
  }
  else {
    $nw->field_hb_client_size->set(0);
  }
  $nw->save();

  drupal_set_message(t($nw->label() . ' has now been assigned.  To remove or add further clients, follow the same process and click continue.'), 'info', FALSE);
}
