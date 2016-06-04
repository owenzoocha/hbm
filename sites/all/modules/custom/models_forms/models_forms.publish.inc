<?php
/**
 * @file
 * Provides form functionality to publish jobs / PM node author.
 */

/**
 * Implements hook_form().
 * Provides functionality to publish a job.
 */
function models_forms_publish_form($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $uw = entity_metadata_wrapper('user', $user);

  $form_state['nid'] = arg(1);
  foreach ($nw->field_hb_users->getIterator() as $k => $v) {
    if($v->getIdentifier() == $user->uid){
      $requested = true;
      break;
    }
  }

  $desc = t('Let\'s get this job published! Hit <strong>publish now</strong> to continue.  Your job will now be searchable.');

  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('publish now'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("publishing.."),
      'data-complete-text' => array('published!'),
    ),
  );
  return $form;
}

function models_forms_publish_form_submit($form, &$form_state){
  global $user;
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $nw->status->set(1);
  $nw->save();
  drupal_set_message(t($nw->label() . ' is now published, keep an eye on your <strong>job requests</strong> to see who\'s interested.'), 'info', FALSE);
}
