<?php

/**
 * @file models_imgs.uploader.inc.
 */

/**
 * Provides functionality to handle dropzone js uploads.
 */
function models_imgs_upload_page() {
  global $user;
  if (!empty($_GET['nid'])) {
    if (!empty($_FILES)) {

      $nw = entity_metadata_wrapper('node', $_GET['nid']);
      if ($nw->field_hb_pics->value()) {
        $i = sizeof($nw->field_hb_pics->value());
      }
      else {
        $i = 0;
      }

      foreach ($_FILES['files']['name'] as $key => $file) {
        $uri = 'public://job_imgs/' . $nw->getIdentifier();
        file_prepare_directory($uri, FILE_CREATE_DIRECTORY);
        $path = drupal_realpath($uri);

        $src = $_FILES['files']['tmp_name'][$key];
        $file_name = $nw->getIdentifier()  . '_' . strtotime('now') . '_' . transliteration_clean_filename($file);
        $destination = $path . '/' . $file_name;

        $ew = entity_create('pics', array('type' => 'pics'));
        $title = 'pics_' . $i . '_' . $nw->getIdentifier() . '_' . $nw->label();
        $ew->title = $title;
        $ew->created = strtotime('now');
        $ew->changed = strtotime('now');

        move_uploaded_file($src, $destination);

        // if ($nw->field_hb_imgs->value()) {
        //   // do something..
        // }
        // else {
          $fs = filesize($destination);
          $file = array(
            'uid' => $user->uid,
            'uri' => $uri . '/' . $file_name,
            'filemime' => file_get_mimetype($destination),
            'status' => 1,
            'filesize' => $fs,
            'filename' => $file_name,
            'display' => 1,
          );
        // }
        // dpm($file, 'fileez');

        $file = file_save((object) $file);
        $ew->field_pics_img[LANGUAGE_NONE][0] = (array) $file;
        $ew->save();
        $i++;
        $nw->field_hb_pics[] = $ew->id;
      }
      $nw->save();
    }
  }
  if (!empty($_GET['uid'])) {
    if (!empty($_FILES)) {
      $uw = entity_metadata_wrapper('user', $user->uid);

      if ($uw->field_hb_pics->value()) {
        $i = sizeof($uw->field_hb_pics->value());
      }
      else {
        $i = 0;
      }

      foreach ($_FILES['files']['name'] as $key => $file) {
        $uri = 'public://user_imgs/' . $uw->getIdentifier();
        file_prepare_directory($uri, FILE_CREATE_DIRECTORY);
        $path = drupal_realpath($uri);

        $src = $_FILES['files']['tmp_name'][$key];
        $file_name = $uw->getIdentifier()  . '_' . strtotime('now') . '_' . transliteration_clean_filename($file);
        $destination = $path . '/' . $file_name;

        $ew = entity_create('pics', array('type' => 'pics'));
        $title = 'user_pics_' . $i . '_' . $uw->getIdentifier() . '_' . $uw->label();
        $ew->title = $title;
        $ew->created = strtotime('now');
        $ew->changed = strtotime('now');

        move_uploaded_file($src, $destination);

        $fs = filesize($destination);
        $file = array(
          'uid' => $user->uid,
          'uri' => $uri . '/' . $file_name,
          'filemime' => file_get_mimetype($destination),
          'status' => 1,
          'filesize' => $fs,
          'filename' => $file_name,
          'display' => 1,
        );

        $file = file_save((object) $file);
        $ew->field_pics_img[LANGUAGE_NONE][0] = (array) $file;
        $ew->save();
        $i++;
        $uw->field_hb_pics[] = $ew->id;
      }
      $uw->save();
    }
  }
}
