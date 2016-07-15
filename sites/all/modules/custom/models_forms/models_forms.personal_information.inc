<?php
/**
 * @file models.personal_information.inc
 *
 * @author: Owen Williams http://drupal.org/user/??
 *
 */

function models_forms_personal_info() {
  global $user;
  $user = user_load($user->uid);

  $uw = entity_metadata_wrapper('user', $user->uid);
  module_load_include('inc', 'user', 'user.pages');
  // form_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  if ($uw->field_my_tcs->value()) {
    $user_form['field_my_tcs']['und']['#prefix'] = '<span class="sr-only">';
    $user_form['field_my_tcs']['und']['#suffx'] = '</span>';
  }

  $wysiwyg_js['wysiwyg']['configs']['tinymce']['formatfiltered_html'] = array(
    'menubar' => FALSE,
    'statusbar' => FALSE,
  );

  drupal_add_js($wysiwyg_js, 'setting');

  $user_form['#attached']['js'] = array(
    'http://maps.googleapis.com/maps/api/js?libraries=places&key=AIzaSyCLxwLPavRyWseQhhaiBVPvONNb1Korie0' => array(
      'type' => 'external',
    ),
    libraries_get_path('geocomplete') . '/' . 'jquery.geocomplete.min.js',
    drupal_get_path('module', 'models_forms') . '/js/models_forms_google_complete.js',
  );

  $user_form['#theme'] = array('overwrite_user_login');

  $user_form['geocomplete'] = array(
    '#type' => 'textfield',
    // '#title' => 'Enter an address',
    '#description' => t('If your address is unrecognised, try the manual option below.'),
    '#attributes' => array(
      'id' => array('geocomplete'),
    ),
    '#suffix' => '<div class="map_canvas"></div><!--<p><a href="#" class="geocomplete-manual">' . t('+ add manual location') . '</a></p>-->',
  );

  $user_form['picture']['picture_upload']['#description'] = t('Your profile picture');
  unset($user_form['account']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  // unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']['picture_delete']);
  unset($user_form['field_hb_type']);
  // unset($user_form['field_hb_ht']);
  // unset($user_form['field_hb_bt']);
  unset($user_form['field_hb_pics']);
  unset($user_form['field_my_total_feedback']);
  unset($user_form['field_my_overall_rating']);
  unset($user_form['field_my_watchlist']);
  unset($user_form['field_my_latlon']);
  unset($user_form['field_flags_strikes']);
  unset($user_form['field_flags_running_posts']);
  return drupal_render($user_form);

}

function models_forms_update_address(&$form, $form_state) {
  global $user;
  $uw = entity_metadata_wrapper('user', $user->uid);
  // dpm($uw->value());
  if ($uw->field_my_address->value()) {
    // dpm($uw->field_my_address->value());
    $add = '';
    $add .= isset($uw->field_my_address->value()['thoroughfare']) ? $uw->field_my_address->value()['thoroughfare'] . ' ' : FALSE;
    $add .= isset($uw->field_my_address->value()['premise']) ? $uw->field_my_address->value()['premise'] . ', ' : FALSE;
    $add .= isset($uw->field_my_address->value()['locality']) ? $uw->field_my_address->value()['locality'] . ', ' : FALSE;
    $add .= isset($uw->field_my_address->value()['dependent_locality']) ? $uw->field_my_address->value()['dependent_locality'] . ', ' : FALSE;
    $add .= isset($uw->field_my_address->value()['administrative_locality']) ? $uw->field_my_address->value()['administrative_locality'] . ', ' : FALSE;
    $add .= isset($uw->field_my_address->value()['postal_code']) ? $uw->field_my_address->value()['postal_code'] : FALSE;
  }

  $add = str_replace(' , ', ', ', $add);
  $add = str_replace(',,', ',', $add);

  if (!empty($add)) {
    $point = geocoder('google', $add, array('https' => TRUE));
    $geo_array = array(
      'geo_type' => 'point',
      'lat' => $point->coords[1],
      'lon' => $point->coords[0],
    );

    $uw->field_my_latlon->set($geo_array);
    $uw->save();
  }
}

// function models_forms_user_presave(&$edit, $account, $category) {
//   dpm('saving user..');
//   dpm($edit);
//   dpm($account);
// }

function models_forms_email_settings() {
  global $user;

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  unset($user_form['account']);
  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  // unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  // unset($user_form['field_hb_ht']);
  // unset($user_form['field_hb_bt']);
  unset($user_form['field_hb_pics']);
  unset($user_form['field_my_total_feedback']);
  unset($user_form['field_my_overall_rating']);
  unset($user_form['field_my_watchlist']);
  unset($user_form['field_my_latlon']);
  unset($user_form['field_my_college']);
  unset($user_form['field_my_company']);
  unset($user_form['field_flags_strikes']);
  unset($user_form['field_flags_running_posts']);
  unset($user_form['field_hb_cover_pic']);
  // $user_form['privatemsg']['pm_enable']['#access'] = FALSE;
  // dpm($user_form);
  // unset($user_form['privatemsg']['pm_email_only_user']);
  // $user_form['privatemsg']['pm_enable']['#value'] = TRUE;
  // $user_form['privatemsg']['pm_enable']['#default_value'] = TRUE;
  // $user_form['privatemsg']['pm_enable']['#checked'] = TRUE;
  return drupal_render($user_form);
}

function models_forms_interests() {
  global $user;

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  $user_form['interest_types'] = array(
    '#markup' => '<p>' . t('Let us know what you\'re interested in - we can use this to tailor your search results and keep you updated with offers.') . '</p>',
    '#weight' => 1,
  );
  unset($user_form['account']);
  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  // unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  // unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  unset($user_form['field_hb_pics']);
  unset($user_form['field_my_total_feedback']);
  unset($user_form['field_my_overall_rating']);
  unset($user_form['field_my_watchlist']);
  unset($user_form['field_my_latlon']);
  unset($user_form['field_my_college']);
  unset($user_form['field_my_company']);
  unset($user_form['field_flags_strikes']);
  unset($user_form['field_hb_cover_pic']);
  unset($user_form['field_flags_running_posts']);
  // $user_form['field_my_tcs']['und']['#required'] = FALSE;
  // unset($user_form['field_my_tcs']);
  return drupal_render($user_form);
}

function models_forms_account_settings() {
  global $user;

  module_load_include('inc', 'hybridauth', 'hybridauth.pages');
  if(!empty(_hybridauth_identity_load_by_uid($user->uid))) {
    $identity = hybridauth_user_identity($user);
    $identity_table = drupal_render($identity);
  }

  $user = user_load($user->uid);
  module_load_include('inc', 'user', 'user.pages');
  $user_form = drupal_get_form('user_profile_form', $user);

  unset($user_form['field_my_name']);
  unset($user_form['field_first_name']);
  unset($user_form['field_surname']);
  unset($user_form['field_phone']);
  unset($user_form['field_gender']);
  unset($user_form['field_my_web']);
  unset($user_form['field_my_address']);
  // unset($user_form['field_my_bio']);
  unset($user_form['field_my_latlong']);
  // unset($user_form['privatemsg']);
  unset($user_form['timezone']);
  unset($user_form['picture']);
  unset($user_form['field_hb_type']);
  // unset($user_form['field_hb_ht']);
  // unset($user_form['field_hb_bt']);
  unset($user_form['field_hb_pics']);
  unset($user_form['field_my_total_feedback']);
  unset($user_form['field_my_overall_rating']);
  unset($user_form['field_my_watchlist']);
  unset($user_form['field_my_latlon']);
  unset($user_form['field_my_college']);
  unset($user_form['field_my_company']);
  unset($user_form['field_hb_cover_pic']);
  unset($user_form['field_flags_strikes']);
  unset($user_form['field_flags_running_posts']);
  if (isset($identity_table)) {
    return drupal_render($user_form) . $identity_table;
  }
  else {
    return drupal_render($user_form);
  }
}

/**
 * Implements hook_form().
 * Provides functionality to update users personal information.
 */

function models_forms_personal_information_form($form, &$form_state){
  global $user;
  $uw = entity_metadata_wrapper('user', $user);

  $desc = t('blabla');
  $form['form_description'] = array(
    '#markup' => '<p>'.$desc.'</p>',
  );

  // $form['pass_fields'] = array(
  //   '#type' => 'password_confirm',
  //   '#description' => t('Enter the same password in both fields'),
  //   '#size' => 32,
  //   '#required' => TRUE,
  // );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("Sending request.."),
      'data-complete-text' => array('Sent!'),
    ),
  );
  return $form;

}

// function models_forms_personal_information_form_submit($form, &$form_state){
//   global $user;
//   $nw = entity_metadata_wrapper('node', $form_state['nid']);
//   $uw = entity_metadata_wrapper('user', $user->uid);
//   $msg = isset($form_state['values']['msg']) ? $form_state['values']['msg'] : false;
//   $removed = 1;
//   if(sizeof($nw->field_hb_users->value()) > 0){
//     $flag = 0;
//     foreach ($nw->field_hb_users->getIterator() as $k => $u) {
//       if($u->getIdentifier() == $user->uid){
//         $nw->field_hb_users[$k] = NULL;
//         $flag = 1;
//         break;
//       }
//     }
//     if($flag == 0){
//       $nw->field_hb_users->offsetSet(sizeof($nw->field_hb_users->value()), $user->uid);
//       rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value());
//       $removed = 0;
//     }
//   } else {
//     $nw->field_hb_users->offsetSet(0, $user->uid);
//     rules_invoke_component('rules_pm_job_request', $msg, $user, $nw->author->value(), $nw->value());
//     $removed = 0;
//   }

//   $nw->save();

//   if($removed == 1){
//     drupal_set_message(t('Hey !name, your job request has now been removed - we\'ve let the job owner know! Check out the <strong>!link</strong> for more hair and beauty options.', array('!name' => $uw->field_first_name->value()), '!link' => l(t('job listings'), 'job-search')), 'info', FALSE);
//   } else {
//     drupal_set_message(t('Hey !name, good news - your request has been sent! Keep an eye on your <strong>!link</strong> for updates - you will be contacted soon.', array('!name' => $uw->field_first_name->value()), '!link' => l(t('job requests'), 'job-requests')), 'success', FALSE);
//   }
// }
