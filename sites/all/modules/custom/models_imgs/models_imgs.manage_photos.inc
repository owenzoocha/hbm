<?php
/**
 * @file models_imgs.manage_photos.inc
 * Accepts an id of a job, to add to users watchlist.
 *
 * @author: Owen Williams http://drupal.org/user/??
 *
 */

function models_imgs_manage_photos() {
  global $user;

  if (isset($_POST['pic'])) {
    $pics = drupal_json_decode($_POST['pic']);
    $ew = entity_metadata_wrapper('pics', $pics['id']);
    $nw = is_numeric($pics['nid']) ? entity_metadata_wrapper('node', $pics['nid']) : entity_metadata_wrapper('user', $user->uid);

    if ($pics['option'] == 'update') {
      // $ew->field_pics_promote->set(1);

      foreach ($nw->field_hb_pics->getIterator() as $key => $eck) {
        if ($eck->getIdentifier() == $pics['id']) {
          $eck->field_pics_promote->set(1);
        }
        else {
          $eck->field_pics_promote->set(0);
        }
        $eck->save();
      }

      // $query = new EntityFieldQuery();
      // $query->entityCondition('entity_type', 'events')
      // ->entityCondition('bundle', 'personal')
      // ->propertyCondition('title', '%'.$lookup.'%', 'LIKE');
      // $result = $query->execute();

      // $ew->save();
    }
    else {
      if ($pics['option'] == 'delete') {
        entity_delete('pics', $pics['id']);
      }
    }
    $nid = $pics['nid'];
    cache_clear_all("promoimg:$nid", 'cache_models', FALSE);
    print_r('done');
  }

  // return '';

}
