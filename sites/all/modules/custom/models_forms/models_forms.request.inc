<?php
/**
 * @file
 * Provides form functionality to request a job after creation.
 */

/**
 * Implements hook_form().
 * Provides functionality to request a job.
 */
function models_forms_request_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);
  foreach ($nw->field_hb_users_eck->getIterator() as $k => $v) {
    if($v->field_feedb_user->getIdentifier() == $user->uid){
      $requested = TRUE;
      $form_state['requested'] = $v->getIdentifier();
      break;
    }
  }

  if ($nw->field_hb_type->value() != 'personal') {
    $desc = !isset($requested) ? t('Hey !name, to show you\'re interested in this job, leave a message for the job owner below and hit <strong>sign me up</strong>!', array('!name' => $uw->field_first_name->value())) : t('To remove your request select <strong>remove request</strong> below - we\'ll let the job owner know.', array('!name' => $uw->field_first_name->value()));
  }
  else {
    $desc = !isset($requested) ? t('Hey !name, if you\'re interested in this last minute model and want to offer a job, get in touch below and hit <strong>send</strong>!', array('!name' => $uw->field_first_name->value())) : t('Hey !name, your message has been sent, if you\'d like to remove your job offer select <strong>remove request</strong> - we\'ll let the job owner know.', array('!name' => $uw->field_first_name->value()));
  }
  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  if(!isset($requested)){
    $form['msg'] = array(
      '#type' => 'textarea',
      // '#title' => t('Message'),
      '#description' => t('... send a private message to !author.', array('!author' => $nw->author->field_first_name->value())),
    );
  }

  if ($nw->field_hb_type->value() != 'personal') {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => !isset($requested) ? t('sign me up') : t('remove request'),
      '#attributes' => array(
        'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
        'data-loading-text' => array("Sending request.."),
        'data-complete-text' => array('Sent!'),
      ),
    );
  }
  else {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => !isset($requested) ? t('send message') : t('remove job offer'),
      '#attributes' => array(
        'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
        'data-loading-text' => array("Sending message.."),
        'data-complete-text' => array('Sent!'),
      ),
    );
  }
  return $form;
}

function models_forms_request_form_submit($form, &$form_state){
  global $user;
  dpm($form_state);

  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $uw = entity_metadata_wrapper('user', $user->uid);
  $subject = $nw->field_hb_type->value() != 'personal' ? t('Job Request') : t('Job Offer');
  $msg = isset($form_state['values']['msg']) ? $form_state['values']['msg'] : false;
  $removed = 1;

  if (!isset($form_state['requested'])) {
    $uw_label = str_replace(' ', '_', strtolower($uw->label()));
    $title = 'client_' . $uw_label . '_uid_' . $uw->getIdentifier() . '_nid_' . $nw->getIdentifier();
    // $query = new EntityFieldQuery();
    // $query->entityCondition('entity_type', 'feedback')
    //   ->entityCondition('bundle', 'feedback')
    //   ->propertyCondition('title', $title, '=');
    // $result = $query->execute();
    $ew = entity_create('feedback', array('type' => 'feedback'));
    $ew->title = $title;
    $ew->created = strtotime('now');
    $ew->field_rating[LANGUAGE_NONE][0]['value'] = 0;
    // $ew->field_feedback[LANGUAGE_NONE][0]['value'] = $fs['msg_' . $nw->author->getIdentifier()];
    $ew->field_feedb_nid[LANGUAGE_NONE][0]['nid'] = $nw->getIdentifier();
    $ew->field_feedb_user[LANGUAGE_NONE][0]['uid'] = $uw->getIdentifier();
    $ew->field_client_selected[LANGUAGE_NONE][0]['value'] = 0;
    $ew->field_feedb_type[LANGUAGE_NONE][0]['value'] = 'client';
    $ew->save();
  }
  else {
    $ew = entity_metadata_wrapper('feedback', $form_state['requested']);
  }

  if(sizeof($nw->field_hb_users_eck->value()) > 0){
    $flag = 0;
    foreach ($nw->field_hb_users_eck->getIterator() as $k => $u) {

      // Remove old user from the list. - REMOVING.
      if($u->field_feedb_user->getIdentifier() == $user->uid){
        $nw->field_hb_users_eck[$k] = NULL;
        $flag = 1;

        entity_delete('feedback', $ew->getIdentifier());
        break;
      }
    }
    // Append a new user eck to the list. - ADDING.
    if($flag == 0){
      $nw->field_hb_users_eck->offsetSet(sizeof($nw->field_hb_users_eck->value()), $ew->id);
      rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value(), $subject);
      $removed = 0;
    }

  // Set the initial user eck to the list. - ADDING.
  } else {
    $nw->field_hb_users_eck->offsetSet(0, $ew->id);
    rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value(), $subject);
    $removed = 0;
  }

  $nw->save();

  if ($nw->field_hb_type->value() != 'personal') {
    if($removed == 1){
      drupal_set_message(t('Hey !name, your job request has now been removed - we\'ve let the job owner know! Check out the <strong>!link</strong> for more hair and beauty options.', array('!name' => $uw->field_first_name->value(), '!link' => l(t('job listings'), 'job-search'))), 'info', FALSE);
    } else {
      drupal_set_message(t('Hey !name, good news - your request has been sent! Keep an eye on your <strong>!link</strong> for updates - you will be contacted soon.', array('!name' => $uw->field_first_name->value(), '!link' => l(t('job requests'), 'job-requests'))), 'status', FALSE);
    }
  }
  else {
    if($removed == 1){
      drupal_set_message(t('Hey !name, your job offer has now been removed - we\'ve let the last minute model know! Check out the <strong>job board</strong> for more last minute models.', array('!name' => $uw->field_first_name->value())), 'info', FALSE);
    } else {
      drupal_set_message(t('Hey !name, your message has been sent! Keep an eye on your <strong>job requests</strong> for updates - you will be contacted soon.', array('!name' => $uw->field_first_name->value())), 'info', FALSE);
    }
  }
}
