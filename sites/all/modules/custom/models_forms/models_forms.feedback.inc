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
  $uw = entity_metadata_wrapper('user', $user->uid);
  $form_state['nid'] = arg(1);
  $usrs = FALSE;
  $owner_fb = FALSE;

  // Check if this is a user submitting feedback on the job owner...
  $title = '%_aid_' . $nw->author->getIdentifier() . '_uid_' . $uw->getIdentifier()  . '_nid_' . $nw->getIdentifier() . '%';
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'feedback')
    ->entityCondition('bundle', 'feedback')
    ->propertyCondition('title', $title, 'like');
  $result = $query->execute();
  if (sizeof($result)) {
    $owner_fb = TRUE;
    $aid = reset($result['feedback'])->id;
    $form_state['aid'] = $aid;
    $aw = entity_metadata_wrapper('feedback', $aid);
    $fb_completed = $aw->field_feedb_received->value() ? TRUE : FALSE;
  }

  // $aid = reset($result['feedback'])->id;
  // $form_state['aid'] = $aid;

  if (!$owner_fb) {
    $desc = t('Provide a star rating from 0 - 5 and leave some feedback.');
    $fb_completed = $nw->field_hb_feedb_size->value() == $nw->field_hb_client_size->value() ? TRUE : FALSE;
    if ($fb_completed) {
      $desc = t('The feedback for this job is now complete!');
    }
  }
  else {
    $desc = t('Provide a star rating from 0 - 5 and leave some feedback for the </strong>job owner</strong>.');
    if ($fb_completed) {
      $desc = t('Your feedback for the job owner is now complete! Click <strong>!here</strong> to view the job.', array('!here' => l(t('here'), 'node/' . $nw->getIdentifier())) );
    }
  }

  $form['form_description'] = array(
    '#markup' => '<p>' . $desc . '</p>',
  );

  // If the person giving the feedback is the job owner..
  if (!$owner_fb) {

    $fb_completed = $nw->field_hb_feedb_size->value() == $nw->field_hb_client_size->value() ? TRUE : FALSE;

    foreach ($nw->field_hb_users_eck->getIterator() as $k => $u) {
      $ew = false;
      if ($u->field_client_selected->value()) {

        $mypic = $u->field_feedb_user->value()->picture;
        if($mypic){
          $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => $u->field_feedb_user->value()->picture->uri, 'attributes' => array('class' => array('img-circle')))).'</div>';
        } else {
          $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => 'public://pictures/picture-default.png', 'attributes' => array('class' => array('img-circle')))).'</div>';
        }

        $stars = $u->field_feedb_user->field_my_overall_rating->value() ? $u->field_feedb_user->field_my_overall_rating->value() : 0;
        $form['userpic' . $u->getIdentifier()] = array(
          '#markup' => '<div class="col-sm-2 lhs">' . $pic . '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>
          <div class="feedback-overall">' . l($u->field_feedb_user->field_my_total_feedback->value() . ' ' . t('feedback'), 'user/' . $u->field_feedb_user->getIdentifier() . '/feedback') . '</div>
          <div class="uname">' . l($u->field_feedb_user->label(), 'user/' . $u->field_feedb_user->getIdentifier()) . '</div></div>',
          '#prefix' => '<div class="row feedb-separator">',
        );

        if ( $u->field_rating->value() ) {
          $rating_amt = 'data-rating="' . $u->field_rating->value() . '"';
        }
        else {
          $rating_amt = FALSE;
        }

        $form['raty_' . $u->field_feedb_user->getIdentifier()] = array(
          '#markup' => '<div class="raty-feedback" ' . $rating_amt . ' data-uid="' . $u->field_feedb_user->getIdentifier() . '" data-cancel="1"></div>',
          '#prefix' => '<div class="col-sm-10 rhs">',
        );

        if ($u->field_rating->value()) {
          $form['rating_' . $u->field_feedb_user->getIdentifier()] = array(
            '#type' => 'hidden',
            '#value' => $u->field_rating->value(),
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
          '#default_value' => $u->field_feedback->value() ? $u->field_feedback->value() : FALSE,
          '#disabled' => $u->field_feedback->value() ? TRUE : FALSE,
          // '#title' => t('Feedback'),
          '#maxlength' => 230,
          '#maxlength_js' => !$u->field_feedback->value() ? TRUE : FALSE,
          '#rows' => 3,
          '#suffix' => '</div></div>',
        );
      }
    }
  }
  // If the person giving the feedback is one of - or the individual client..
  else {
    $form_state['owner_fb'] = TRUE;

    $mypic = $nw->author->value()->picture;
    if($mypic){
      $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => $nw->author->value()->picture->uri, 'attributes' => array('class' => array('img-circle')))).'</div>';
    } else {
      $pic = '<div class="my-image img-circle">' . theme('image_style', array('style_name' => 'profile', 'path' => 'public://pictures/picture-default.png', 'attributes' => array('class' => array('img-circle')))).'</div>';
    }

    $stars = $nw->author->field_my_overall_rating->value() ? $nw->author->field_my_overall_rating->value() : 0;
    $form['userpic' . $nw->author->getIdentifier()] = array(
      '#markup' => '<div class="col-sm-2 lhs">' . $pic . '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div><div class="feedback-overall">' . l($nw->author->field_my_total_feedback->value() . ' ' . t('feedback'), 'user/' . $nw->author->getIdentifier() . '/feedback') . '</div><div class="uname">' . l($nw->author->label(), 'user/' . $nw->author->getIdentifier()) . '</div></div>',
      '#prefix' => '<div class="row feedb-separator">',
    );

    if ( $aw->field_rating->value() ) {
      $rating_amt = 'data-rating="' . $aw->field_rating->value() . '"';
    }
    else {
      $rating_amt = FALSE;
    }

    $form['raty_' . $nw->author->getIdentifier()] = array(
      '#markup' => '<div class="raty-feedback" ' . $rating_amt . ' data-uid="' . $nw->author->getIdentifier() . '" data-cancel="1"></div>',
      '#prefix' => '<div class="col-sm-10 rhs">',
    );

    if ($aw->field_rating->value()) {
      $form['rating_' . $nw->author->getIdentifier()] = array(
        '#type' => 'hidden',
        '#value' => $aw->field_rating->value(),
        '#attributes' => array('id' => array('star-uid-' . $nw->author->getIdentifier())),
      );
    }
    else {
      $form['rating_' . $nw->author->getIdentifier()] = array(
        '#type' => 'hidden',
        '#attributes' => array('id' => array('star-uid-' . $nw->author->getIdentifier())),
      );
    }

    $form['msg_' . $nw->author->getIdentifier()] = array(
      '#type' => 'textarea',
      '#default_value' => $aw->field_feedback->value() ? $aw->field_feedback->value() : FALSE,
      '#disabled' => $aw->field_feedback->value() ? true : FALSE,
      // '#title' => t('Feedback'),
      '#maxlength' => 230,
      '#maxlength_js' => !$aw->field_feedback->value() ? TRUE : FALSE,
      '#rows' => 3,
      '#suffix' => '</div></div>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('save'),
    '#disabled' => $fb_completed ? TRUE : FALSE,
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

  if (!isset($form_state['owner_fb'])) {

    $feedback_completed_size = 0;
    foreach ($nw->field_hb_users_eck->getIterator() as $key => $u) {
      if ($u->field_client_selected->value()) {
        if($fs['msg_' . $u->field_feedb_user->getIdentifier()]){

          // Save the user ECK data.
          // ------- ECK --------
          $u->field_feedback->set($fs['msg_' . $u->field_feedb_user->getIdentifier()]);
          $u->field_rating->set($fs['rating_' . $u->field_feedb_user->getIdentifier()]);
          $u->field_feedb_received->set(1);

          // ------- USER --------
          if ($u->field_feedb_user->field_my_total_feedback->value()) {
            $fb_amt = $u->field_feedb_user->field_my_total_feedback->value() + 1;
            $u->field_feedb_user->field_my_total_feedback->set($fb_amt);
          }
          else {
            $u->field_feedb_user->field_my_total_feedback->set(1);
            $fb_amt = 1;
          }

          // Save the entity eck before running the next sql query.
          $u->save();

          if ($u->field_feedb_user->field_my_overall_rating->value()) {

          $sql = db_query('select fb.id AS id, SUM(r.field_rating_value) AS score
            FROM eck_feedback fb
            LEFT JOIN field_data_field_rating r ON r.entity_id = fb.id
            LEFT JOIN field_data_field_client_selected s ON s.entity_id = fb.id
            LEFT JOIN field_data_field_feedb_user u ON u.entity_id = fb.id
            LEFT JOIN field_data_field_feedb_received g ON g.entity_id = fb.id
            WHERE u.field_feedb_user_uid = :uid AND s.field_client_selected_value = 1 AND g.field_feedb_received_value = 1', array('uid' => $u->field_feedb_user->getIdentifier()));

            $sql_res = $sql->fetchAll();
            $total_stars = $sql_res[0]->score;
            $overall_rating = $total_stars / $fb_amt;

            $overall_rating = number_format($overall_rating, 2);
            $u->field_feedb_user->field_my_overall_rating->set($overall_rating);
          }
          else {
            $u->field_feedb_user->field_my_overall_rating->set($fs['rating_' . $u->field_feedb_user->getIdentifier()]);
          }
          // Save the user profile data.
          $u->field_feedb_user->save();
          $feedback_completed_size++;
        }
      }
    }
    // Set the completed feedback amount.
    $nw->field_hb_feedb_size->set($feedback_completed_size);
    $nw->save();
  }

  // if ($feedback == sizeof($nw->field_hb_users->value())) {
  //   $nw->field_hb_feedback_complete->set(1);
  //   $nw->save();
  //   drupal_set_message(t('Hey !name, your feedback is now complete! Keep an eye on your profile for your attendees feedback.', array('!name' => $nw->author->field_first_name->value())), 'info', FALSE);
  // }
  // else {
  //   drupal_set_message(t('Hey !name, it looks like you may have missed someone! Please make sure all feedback is complete.', array('!name' => $nw->author->field_first_name->value())), 'warning', FALSE);
  // }

  else {

    if($fs['msg_' . $nw->author->getIdentifier()]){

      // dpm($fs);
      // dpm($form_state);

      $aw = entity_metadata_wrapper('feedback', $form_state['aid']);
      // dpm($aw->value());


      // Save the Job Owner ECK data.
      // ------- ECK --------
      $aw->field_feedback->set($fs['msg_' . $nw->author->getIdentifier()]);
      $aw->field_rating->set($fs['rating_' . $nw->author->getIdentifier()]);
      $aw->field_feedb_received->set(1);

      // ------- USER --------
      if ($aw->field_feedb_user->field_my_total_feedback->value()) {
        $fb_amt = $aw->field_feedb_user->field_my_total_feedback->value() + 1;
        $aw->field_feedb_user->field_my_total_feedback->set($fb_amt);
      }
      else {
        $aw->field_feedb_user->field_my_total_feedback->set(1);
        $fb_amt = 1;
      }

      // Save the entity eck before running the next sql query.
      $aw->save();

      if ($aw->field_feedb_user->field_my_overall_rating->value()) {

        $sql = db_query('select fb.id AS id, SUM(r.field_rating_value) AS score
          FROM eck_feedback fb
          LEFT JOIN field_data_field_rating r ON r.entity_id = fb.id
          LEFT JOIN field_data_field_client_selected s ON s.entity_id = fb.id
          LEFT JOIN field_data_field_feedb_user u ON u.entity_id = fb.id
          LEFT JOIN field_data_field_feedb_received g ON g.entity_id = fb.id
          WHERE u.field_feedb_user_uid = :uid AND s.field_client_selected_value = 1 AND g.field_feedb_received_value = 1', array('uid' => $nw->author->getIdentifier()));

        $sql_res = $sql->fetchAll();
        $total_stars = $sql_res[0]->score;
        $overall_rating = $total_stars / $fb_amt;

        $overall_rating = number_format($overall_rating, 2);
        $aw->field_feedb_user->field_my_overall_rating->set($overall_rating);
      }
      else {
        $aw->field_feedb_user->field_my_overall_rating->set($fs['rating_' . $nw->author->getIdentifier()]);
      }
      // Save the user profile data.
      $aw->field_feedb_user->save();

      drupal_set_message(t('Hey !name, your feedback for the job owner is now complete! Keep an eye on your profile for your feedback from this job.', array('!name' => $nw->author->field_first_name->value())), 'info', FALSE);

    }
  }
}
