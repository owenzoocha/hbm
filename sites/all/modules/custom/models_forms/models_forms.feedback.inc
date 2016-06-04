<?php

/**
 * @file feedback.
 */

/**
 * Implements hook_form().
 * Provides functionality to create feedback against job users.
 */
function models_forms_feedback_form($form, &$form_state) {
  global $user;
  $nw = entity_metadata_wrapper('node', arg(1));
  $form_state['nid'] = arg(1);
  $usrs = FALSE;
  $owner_fb = FALSE;

  foreach ($nw->field_hb_users_eck as $k => $ew) {
    if ($ew->field_feedb_user->getIdentifier() == $user->uid ){
      $owner_fb = TRUE;
      break;
    }
  }

  dpm($owner_fb, '$owner_fb');

  $desc = !$owner_fb ? t('Provide a star rating from 0 - 5 and leave some feedback.') : t('Provide a star rating from 0 - 5 and leave some feedback for the job owner.');
  $form['form_description'] = array(
    '#markup' => '<p>' . $desc . '</p>',
  );

  if (!$owner_fb) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'feedback')
      ->entityCondition('bundle', 'feedback')
      ->propertyCondition('title', '_nid_' . $nw->getIdentifier(), 'CONTAINS');
    $result = $query->execute();
    $fbk_size = !empty($result) ? sizeof($result['feedback']) : 0;
    if(!empty($result)){
      $form_state['eck_result'] = $result;
    }
    $fbk = $fbk_size ? TRUE : FALSE;

    foreach ($nw->field_hb_users_eck->getIterator() as $k => $u) {
      $ew = false;
      if($fbk) {

        $uw_label = str_replace(' ', '_', strtolower($u->field_feedb_user->label()));

        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'feedback')
          ->entityCondition('bundle', 'feedback')
          ->propertyCondition('title', 'assignee_' . $uw_label . '_uid_' . $u->field_feedb_user->getIdentifier() . '_nid_' . $nw->getIdentifier() . '_rating', '=');
        $result = $query->execute();

        if (!empty($result)){
          $ew = entity_metadata_wrapper('feedback', reset($result['feedback'])->id);
        }

      }

      $mypic = $u->field_feedb_user->value()->picture;
      if($mypic){
        $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => $u->field_feedb_user->value()->picture->uri, 'attributes' => array('class' => array('img-circle')))).'</div>';
      } else {
        $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => 'public://pictures/picture-default.png', 'attributes' => array('class' => array('img-circle')))).'</div>';
      }

      $stars = $u->field_feedb_user->field_my_overall_rating->value() ? $u->field_feedb_user->field_my_overall_rating->value() : 0;
      $form['userpic' . $u->getIdentifier()] = array(
        '#markup' => '<div class="col-sm-2 lhs">' . $pic . '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div><div class="uname">' . l($u->field_feedb_user->label(), 'user/' . $u->field_feedb_user->getIdentifier()) . '</div></div>',
        '#prefix' => '<div class="row feedb-separator">',
      );

      if ( $ew ) {
        $rating_amt = 'data-rating="' . $ew->field_rating->value() . '"';
      }
      else {
        $rating_amt = FALSE;
      }

      $form['raty_' . $u->field_feedb_user->getIdentifier()] = array(
        '#markup' => '<div class="raty-feedback" ' . $rating_amt . ' data-uid="' . $u->field_feedb_user->getIdentifier() . '" data-cancel="1"></div>',
        '#prefix' => '<div class="col-sm-10 rhs">',
      );

      if (!empty($ew)) {
        $form['rating_' . $u->field_feedb_user->getIdentifier()] = array(
          '#type' => 'hidden',
          '#value' => $ew->field_rating->value(),
          // '#required' => TRUE,
          '#attributes' => array('id' => array('star-uid-' . $u->field_feedb_user->getIdentifier())),
        );
      }
      else {
        $form['rating_' . $u->field_feedb_user->getIdentifier()] = array(
          '#type' => 'hidden',
          // '#required' => TRUE,
          '#attributes' => array('id' => array('star-uid-' . $u->field_feedb_user->getIdentifier())),
        );
      }

      $form['msg_' . $u->field_feedb_user->getIdentifier()] = array(
        '#type' => 'textarea',
        '#default_value' => !empty($ew) ? $ew->field_feedback->value() : FALSE,
        '#disabled' => !empty($ew) ? true : FALSE,
        // '#title' => t('Feedback'),
        '#maxlength' => 230,
        '#maxlength_js' => empty($ew) ? TRUE : FALSE,
        '#rows' => 3,
        '#suffix' => '</div></div>',
      );
    }
  }
  else {

  // $query = new EntityFieldQuery();
  // $query->entityCondition('entity_type', 'feedback')
  //   ->entityCondition('bundle', 'feedback')
  //   ->propertyCondition('title', '_nid_'.$nw->getIdentifier(), 'CONTAINS');
  // $result = $query->execute();
  // $fbk_size = !empty($result) ? sizeof($result['feedback']) : 0;
  // if(!empty($result)){
  //   $form_state['eck_result'] = $result;
  // }
  //
    $fbk = $fbk_size ? TRUE : FALSE;
    $form_state['owner_fb'] = TRUE;
    $ew = FALSE;

    $mypic = $nw->author->value()->picture;
    if($mypic){
      $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => $nw->author->value()->picture->uri, 'attributes' => array('class' => array('img-circle')))).'</div>';
    } else {
      $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => 'public://pictures/picture-default.png', 'attributes' => array('class' => array('img-circle')))).'</div>';
    }
    $stars = $nw->author->field_my_overall_rating->value() ? $nw->author->field_my_overall_rating->value() : 0;
    $form['userpic' . $nw->author->getIdentifier()] = array(
      '#markup' => '<div class="col-sm-2 lhs">' . $pic . '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div><div class="uname">' . l($nw->author->label(), 'user/' . $nw->author->getIdentifier()) . '</div></div>',
      '#prefix' => '<div class="row feedb-separator">',
    );

    if ( $ew ) {
      $rating_amt = 'data-rating="' . $ew->field_rating->value() . '"';
    }
    else {
      $rating_amt = FALSE;
    }

    $form['raty_' . $nw->author->getIdentifier()] = array(
      '#markup' => '<div class="raty-feedback" ' . $rating_amt . ' data-uid="' . $nw->author->getIdentifier() . '" data-cancel="1"></div>',
      '#prefix' => '<div class="col-sm-10 rhs">',
    );

    if (!empty($ew)) {
      $form['rating_' . $nw->author->getIdentifier()] = array(
        '#type' => 'hidden',
        '#value' => $ew->field_rating->value(),
        // '#required' => TRUE,
        '#attributes' => array('id' => array('star-uid-' . $nw->author->getIdentifier())),
      );
    }
    else {
      $form['rating_' . $nw->author->getIdentifier()] = array(
        '#type' => 'hidden',
        // '#required' => TRUE,
        '#attributes' => array('id' => array('star-uid-' . $nw->author->getIdentifier())),
      );
    }

    $form['msg_' . $nw->author->getIdentifier()] = array(
      '#type' => 'textarea',
      '#default_value' => !empty($ew) ? $ew->field_feedback->value() : FALSE,
      '#disabled' => !empty($ew) ? true : FALSE,
      // '#title' => t('Feedback'),
      '#maxlength' => 230,
      '#maxlength_js' => empty($ew) ? TRUE : FALSE,
      '#rows' => 3,
      '#suffix' => '</div></div>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
    '#disabled' => sizeof($nw->field_hb_users_eck->value()) <= $fbk_size ? true : false,
    '#attributes' => array(
      'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
      'data-loading-text' => array("Save.."),
      'data-complete-text' => array('Saved!'),
    ),
  );
  return $form;
}

/**
 * Custom submit function for models_forms_create_form_submit.
 */
function models_forms_feedback_form_submit(&$form, &$form_state){
  global $user;
  $fs = $form_state['values'];
  $nw = entity_metadata_wrapper('node', $form_state['nid']);
  $feedback = 0;
  // dpm($fs);
  // dpm($form_state);

  if (!isset($form_state['owner_fb'])) {
    foreach ($nw->field_hb_users_eck->getIterator() as $key => $u) {
      dpm($u->value());
      // if($fs['msg_' . $u->field_feedb_user->getIdentifier()]){
      //   $feedback++;
      //   $title = 'assignee_' . $u->field_feedb_user->label() . '_uid_' . $u->getIdentifier() . '_nid_' . $nw->getIdentifier() . '_rating';
      //   $query = new EntityFieldQuery();
      //   $query->entityCondition('entity_type', 'feedback')
      //     ->entityCondition('bundle', 'feedback')
      //     ->propertyCondition('title', $title, '=');
      //   $result = $query->execute();
      //   if(!$result){
      //     $rw = entity_create('feedback', array('type' => 'feedback'));
      //     $rw->title = $title;
      //     $rw->created = strtotime('now');
      //     $rw->field_rating[LANGUAGE_NONE][0]['value'] = !empty($fs['rating_' . $nw->author->getIdentifier()]) ? $fs['rating_' . $nw->author->getIdentifier()] : 0;
      //     $rw->field_feedback[LANGUAGE_NONE][0]['value'] = $fs['msg_'.$u->getIdentifier()];
      //     $rw->field_feedb_nid[LANGUAGE_NONE][0]['nid'] = $nw->getIdentifier();
      //     $rw->field_feedb_user[LANGUAGE_NONE][0]['uid'] = $u->getIdentifier();
      //     $rw->field_feedb_type[LANGUAGE_NONE][0]['value'] = 'assignee';
      //     $rw->save();
      //   }

      //   $query = new EntityFieldQuery();
      //   $query->entityCondition('entity_type', 'feedback')
      //     ->entityCondition('bundle', 'feedback')
      //     ->propertyCondition('title', $u->label() . '_uid_' . $u->getIdentifier(), 'CONTAINS');
      //   $result = $query->execute();
      //   if(!empty($result)){
      //     if ($u->field_my_total_feedback->value()) {
      //       $fb_amt = $u->field_my_total_feedback->value() + 1;
      //       $u->field_my_total_feedback->set($fb_amt);
      //     }
      //     else {
      //       $u->field_my_total_feedback->set(1);
      //     }

      //     if ($u->field_my_overall_rating->value()) {
      //       $sql = db_query('select fb.id AS id, SUM(r.field_rating_value) AS score
      //         FROM eck_feedback fb
      //         LEFT JOIN field_data_field_rating r ON r.entity_id = fb.id
      //         WHERE fb.title LIKE :title', array('title' => '%assignee_' . $u->label() . '_uid_' . $u->getIdentifier() .'%'));
      //       $sql_res = $sql->fetchAll();
      //       $total_stars = $sql_res[0]->score;
      //       $overall_rating = $total_stars / sizeof($result['feedback']);
      //       $overall_rating = number_format($overall_rating, 2);
      //       $u->field_my_overall_rating->set($overall_rating);
      //     }
      //     else {
      //       $u->field_my_overall_rating->set($fs['rating_'.$u->getIdentifier()]);
      //     }
      //     $u->save();
      //   }
      // }
    }
    // if ($feedback == sizeof($nw->field_hb_users->value())) {
    //   $nw->field_hb_feedback_complete->set(1);
    //   $nw->save();
    //   drupal_set_message(t('Hey !name, your feedback is now complete! Keep an eye on your profile for your attendees feedback.', array('!name' => $nw->author->field_first_name->value())), 'info', FALSE);
    // }
    // else {
    //   drupal_set_message(t('Hey !name, it looks like you may have missed someone! Please make sure all feedback is complete.', array('!name' => $nw->author->field_first_name->value())), 'warning', FALSE);
    // }
  }
  else {

    // if($fs['msg_' . $nw->author->getIdentifier()]){

    //   $nw->field_hb_feedback_complete->set(1);
    //   $nw->save();

    //   $title = 'owner_' . $nw->author->label() . '_uid_' . $nw->author->getIdentifier() . '_nid_' . $nw->getIdentifier() . '_aid_' . $user->uid . '_rating';
    //   $query = new EntityFieldQuery();
    //   $query->entityCondition('entity_type', 'feedback')
    //     ->entityCondition('bundle', 'feedback')
    //     ->propertyCondition('title', $title, '=');
    //   $result = $query->execute();

    //   if(!$result){
    //     $rw = entity_create('feedback', array('type' => 'feedback'));
    //     $rw->title = $title;
    //     $rw->created = strtotime('now');
    //     $rw->field_rating[LANGUAGE_NONE][0]['value'] = !empty($fs['rating_' . $nw->author->getIdentifier()]) ? $fs['rating_' . $nw->author->getIdentifier()] : 0;
    //     $rw->field_feedback[LANGUAGE_NONE][0]['value'] = $fs['msg_' . $nw->author->getIdentifier()];
    //     $rw->field_feedb_nid[LANGUAGE_NONE][0]['nid'] = $nw->getIdentifier();
    //     $rw->field_feedb_user[LANGUAGE_NONE][0]['uid'] = $nw->author->getIdentifier();
    //     $rw->field_feedb_type[LANGUAGE_NONE][0]['value'] = 'owner';
    //     $rw->save();

    //     dpm($rw, '1');

    //   }

    //   $query = new EntityFieldQuery();
    //   $query->entityCondition('entity_type', 'feedback')
    //     ->entityCondition('bundle', 'feedback')
    //     ->propertyCondition('title', $nw->author->label() . '_uid_' . $nw->author->getIdentifier(), 'CONTAINS');
    //   $result = $query->execute();
    //   if(!empty($result)){
    //     if ($nw->author->field_my_total_feedback->value()) {
    //       $fb_amt = $nw->author->field_my_total_feedback->value() + 1;
    //       $nw->author->field_my_total_feedback->set($fb_amt);
    //     }
    //     else {
    //       $nw->author->field_my_total_feedback->set(1);
    //     }

    //     if ($nw->author->field_my_overall_rating->value()) {
    //       $sql = db_query('select fb.id AS id, SUM(r.field_rating_value) AS score
    //         FROM eck_feedback fb
    //         LEFT JOIN field_data_field_rating r ON r.entity_id = fb.id
    //         WHERE fb.title LIKE :title', array('title' => '%' . $nw->author->label() . '_uid_' . $nw->author->getIdentifier() .'%'));
    //       $sql_res = $sql->fetchAll();
    //       dpm($sql_res);
    //       $total_stars = $sql_res[0]->score;
    //       $overall_rating = $total_stars / sizeof($result['feedback']);
    //       $overall_rating = number_format($overall_rating, 2);
    //       $nw->author->field_my_overall_rating->set($overall_rating);
    //     }
    //     else {
    //       $nw->author->field_my_overall_rating->set($fs['rating_' . $nw->author->getIdentifier()]);
    //     }
    //     $nw->author->save();
    //   }

    //   drupal_set_message(t('Hey !name, your feedback for the job owner is now complete! Keep an eye on your profile for your feedback from this job.', array('!name' => $nw->author->field_first_name->value())), 'info', FALSE);

    // }
  }
}
