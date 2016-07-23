<?php
/**
 * @file
 * Provides form functionality to contact the admin.
 */

/**
 * Implements hook_form().
 * Provides functionality to contact admin.
 */
function models_forms_contactus_form($form, &$form_state){
  global $user;

  if ($user->uid != 0) {
    $uw = entity_metadata_wrapper('user', $user);
    $name = $uw->label();
    $email = $uw->mail->value();
  }

  $form_state['currentpath'] = current_path();

  $desc = t('Have an issue? Need some help? Looking to advertise? Our team are on hand to answer your questions.  Please fill in the details below.');
  $form['form_description'] = array(
    '#markup' => '<p>' . $desc . '</p>',
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($name) ? $name : FALSE,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#default_value' => isset($email) ? $email : FALSE,
  );

  $options = array('- please select -', 'An issue with my account', 'I want to report a bug', 'Advertising on HBM', 'General enquiry', 'I would like to report a user');
  sort($options);

  $form['ops'] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc($options),
    '#title' => t('What\'s it regarding?'),
  );

  $form['msg'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#description' => t('Send us your message, we will get back to you ASAP!'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('send'),
    '#attributes' => array(
      'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
      'data-loading-text' => array("Sending request.."),
      'data-complete-text' => array('Sent!'),
    ),
  );
  return $form;
}

function models_forms_contactus_form_submit($form, &$form_state){
  global $user;
  // $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $uw = entity_metadata_wrapper('user', $user->uid);
  $msg = isset($form_state['values']['msg']) ? $form_state['values']['msg'] : false;
  // SEND a message email...
  drupal_set_message(t('Thanks for your message - we will get back to you soon!'), 'info', FALSE);

  $params = array(
    'msg' => $form_state['values']['msg'] ? $form_state['values']['msg'] : 'n/a',
    'name' => $form_state['values']['name'] ? $form_state['values']['name'] : 'n/a',
    'option' => $form_state['values']['ops'] ? $form_state['values']['ops'] : 'n/a',
    'email' => $form_state['values']['email'] ? $form_state['values']['email'] : 'n/a',
  );
  $key = 'models_forms_contactus_mail';
  $to = 'owenwilliams1@gmail.com';
  $mail = drupal_mail('models_forms', $key, $to, language_default(), $params);

  drupal_goto($form_state['currentpath']);
}
