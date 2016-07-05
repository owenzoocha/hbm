<?php
/**
 * @file
 * Provides form functionality to Complete jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to Complete a job.
 */
function models_forms_complete_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);

  $desc = '<p>' . t('Hey !name, it looks like your job has ended. To set it to complete click <strong>Completed</strong> below!', array('!name' => $nw->author->field_first_name->value())) . '</p>';

  $desc .= '<p>' . t('We hope everything went well! If you have any questions feel free to get in touch with the HBM team anytime.. ') . '<i class="material-icons">sentiment_satisfied</i>' . '</p>';

  $form['form_description'] = array(
    '#markup' => $desc,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Completed'),
    '#attributes' => array(
      'class' => array('btn-success'),
      // 'data-loading-text' => array("removing.."),
      // 'data-complete-text' => array('remove!'),
    ),
  );
  return $form;
}

function models_forms_complete_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $uw = entity_metadata_wrapper('user', $user->uid);

  // Set job to admin & cancel.
  $nw->field_hb_status->set('Complete');
  $nw->field_hb_paused->set(0);
  $nw->field_hb_completed->set(1);
  $nw->save();

  // Calculate jobs running for user
  if ($uw->field_flags_running_posts->value()) {
    $posts = $uw->field_flags_running_posts->value() - 1;
    $uw->field_flags_running_posts->set($posts);
    $uw->save();
  }

  // Delete the scheduled complete flag action - because we're doing it manually.
  $task_identifier = 'flag_complete_' . $nw->getIdentifier() . '_' . $nw->author->getIdentifier();
  rules_action('schedule_delete', array('component' => 'rules_schedule_complete_finished_job'))->executeByArgs(array('task' => $task_identifier,));

  drupal_set_message(t($nw->label() . ' is now complete! Want to post another job? Click !link to continue!', array('!link' => l('here', 'job/create', array('attributes' => array('class' => array('a-link')))))), 'status', FALSE);
  // drupal_goto('user/' . $user->uid);
}
