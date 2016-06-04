<?php

/**
 * @file models_imgs.jobs.inc.
 */

/**
 * Provides functionality to handle dropzone js on job pages.
 */
function models_imgs_user_page() {
  // $ew = entity_metadata_wrapper('pics', 13);
  // dpm($ew->value());
  return theme('dropzone_for_job');
}

