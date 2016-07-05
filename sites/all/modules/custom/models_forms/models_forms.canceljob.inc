<?php
/**
 * @file
 * Provides form functionality to cancel jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to cancel a job.
 */
function models_forms_cancel_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);

  $desc = t('You are cancelling this job - any requestees will be notified.  Are you sure you want to continue?');

  $form['form_description'] = array(
    '#markup' => '<p>' . $desc . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes, cancel this job'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("removing.."),
      'data-complete-text' => array('remove!'),
    ),
  );
  return $form;
}

function models_forms_cancel_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $uw = entity_metadata_wrapper('user', $user->uid);
  $nw->status->set(1);

  // Schedule for the job to be deleted in 10 days.
  rules_invoke_component('rules_set_schedule_schedule_the_job_delete', $nw->value());

  if ($nw->field_hb_users->value()) {
    $subject = t('Job Cancelled');
    foreach ($nw->field_hb_users->getIterator() as $key => $uw) {
      $msg = t('Sorry - my job is no longer available.');
      // Send the messages to requestees..
      rules_invoke_component('rules_pm_job_cancelled', $msg, $uw, $nw->author->value(), $nw->value(), $subject);
    }
  }

  // Set job to admin & cancel.
  $nw->field_hb_cancelled->set(1);
  $nw->field_hb_status->set('Closed');
  $nw->field_hb_paused->set(0);

  // Set the author to admin so we can control it...
  $nw->author->set(1);
  $nw->status->set(0);
  $nw->save();

  // Calculate jobs running for user
  if ($uw->field_flags_running_posts->value()) {
    $posts = $uw->field_flags_running_posts->value() - 1;
    $uw->field_flags_running_posts->set($posts);
    $uw->save();
  }

  // Delete the scheduled complete flag action.
  $task_identifier = 'flag_complete_' . $nw->getIdentifier() . '_' . $nw->author->getIdentifier();
  rules_action('schedule_delete', array('component' => 'rules_schedule_complete_finished_job'))->executeByArgs(array('task' => $task_identifier,));

  drupal_set_message(t($nw->label() . ' has now been cancelled - any client have been notified.'), 'info', FALSE);
  drupal_goto('user/' . $user->uid);
}
