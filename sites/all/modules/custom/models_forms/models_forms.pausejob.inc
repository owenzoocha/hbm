<?php
/**
 * @file
 * Provides form functionality to pause jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to pause a job.
 */
function models_forms_pause_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);

  $desc = t('You are pausing this job - any requestees will be notified.  Are you sure you want to continue?' );

  $form['form_description'] = array(
    '#markup' => '<p>' . $desc . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes, pause this job.'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("pausing.."),
      'data-complete-text' => array('pause!'),
    ),
  );
  return $form;
}

function models_forms_pause_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $nw->status->set(1);
  if ($nw->field_hb_users->value()) {
    $subject = t('Job Paused');
    foreach ($nw->field_hb_users->getIterator() as $key => $uw) {
      $msg = t('My job has been paused until further notice.');
      rules_invoke_component('rules_pm_job_paused', $msg, $uw, $nw->author->value(), $nw->value(), $subject);
    }
  }

  // Set job to admin & pause.
  $nw->field_hb_paused->set(1);
  // $nw->author->set(1);
  $nw->status->set(0);
  $nw->save();

  // drupal_set_message(t($nw->label() . ' has now been paused - any requestees have been notified.  To resume this job, click <strong>publish now!</strong>'), 'info', FALSE);
  // drupal_goto('user/' . $user->uid);
}
