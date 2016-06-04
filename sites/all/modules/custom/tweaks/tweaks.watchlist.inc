<?php
/**
 * @file tweaks.watchlist.inc
 * Accepts an id of a job, to add to users watchlist.
 *
 * @author: Owen Williams http://drupal.org/user/??
 *
 */

function tweaks_watchlist_updater() {
  global $user;
  // $manual = '{"option":"delete","id":120}';
  if (isset($_POST['watchlist'])) {
    $uid = $user->uid;
    $uw = entity_metadata_wrapper('user', $user->uid);
    $watchlist = drupal_json_decode($_POST['watchlist']);

    if ($watchlist['option'] == 'add') {
      if( !$uw->field_my_watchlist->value()) {
        $uw->field_my_watchlist->offsetSet(0, $watchlist['id']);
      }
      else {
        $uw->field_my_watchlist->offsetSet( sizeof($uw->field_my_watchlist->value()), $watchlist['id']);
      }
    }
    else {
      if ($watchlist['option'] == 'delete') {
        $my_wl = tweaks_get_watchlist($uw);
        $uw->field_my_watchlist->set(NULL);
        $i = 0;
        unset($my_wl[$watchlist['id']]);
        if (sizeof($my_wl)) {
          foreach ($my_wl as $key => $nid) {
            $uw->field_my_watchlist->offsetSet($i, $nid);
            $i++;
          }
        }
      }
    }

    // Do some caching stuff here?!
    cache_clear_all("watchlist:$uid", 'cache_models', FALSE);
    $uw->save();
    print_r('done');
  }

  if (isset($manual)) {
    $uw = entity_metadata_wrapper('user', $user->uid);
    $watchlist = drupal_json_decode($manual);
    if ($watchlist['option'] == 'add') {
      if( !$uw->field_my_watchlist->value()) {
        $uw->field_my_watchlist->offsetSet(0, $watchlist['id']);
      }
      else {
        $uw->field_my_watchlist->offsetSet( sizeof($uw->field_my_watchlist->value()), $watchlist['id']);
      }
    }
    else {
      if ($watchlist['option'] == 'delete') {
        $my_wl = tweaks_get_watchlist($uw);
        $uw->field_my_watchlist->set(NULL);
        $i = 0;
        unset($my_wl[$watchlist['id']]);
        if (sizeof($my_wl)) {
          foreach ($my_wl as $key => $nid) {
            $uw->field_my_watchlist->offsetSet($i, $nid);
            $i++;
          }
        }
      }
    }
    // Do some caching stuff here?!
    $uw->save();
  }

  // return '';

}
