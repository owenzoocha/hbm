<?php
/**
 * @file
 * Tweaks rules file.
 *
 */
function tweaks_rules_action_info() {
  $actions['tweaks_create_geofield'] = array(
    'label' => t('HBM - create geofield on save.'),
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Node'),
      ),
    ),
    'group' => t('HBM'),
    'callbacks' => array(
      'execute' => 'tweaks_create_geofield',
    ),
  );

  return $actions;
}

function tweaks_create_geofield($node) {
dpm($node);
  $original_add = '';
  if (isset($node->original->field_hb_location[LANGUAGE_NONE])) {
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['thoroughfare']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['thoroughfare'] . ' ' : FALSE;
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['premise']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['premise'] . ', ' : FALSE;
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['locality']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['locality'] . ', ' : FALSE;
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['dependent_locality']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['dependent_locality'] . ', ' : FALSE;
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['administrative_locality']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['administrative_locality'] . ', ' : FALSE;
    $original_add .= isset($node->original->field_hb_location[LANGUAGE_NONE][0]['postal_code']) ? $node->original->field_hb_location[LANGUAGE_NONE][0]['postal_code'] : FALSE;
    $original_add = str_replace(' , ', ', ', $original_add);
    $original_add = str_replace(',,', ',', $original_add);
  }

  $nw = entity_metadata_wrapper('node', $node->nid);
  if (isset($node->field_hb_location[LANGUAGE_NONE])) {
    $add = '';
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['thoroughfare']) ? $node->field_hb_location[LANGUAGE_NONE][0]['thoroughfare'] . ' ' : FALSE;
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['premise']) ? $node->field_hb_location[LANGUAGE_NONE][0]['premise'] . ', ' : FALSE;
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['locality']) ? $node->field_hb_location[LANGUAGE_NONE][0]['locality'] . ', ' : FALSE;
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['dependent_locality']) ? $node->field_hb_location[LANGUAGE_NONE][0]['dependent_locality'] . ', ' : FALSE;
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['administrative_locality']) ? $node->field_hb_location[LANGUAGE_NONE][0]['administrative_locality'] . ', ' : FALSE;
    $add .= isset($node->field_hb_location[LANGUAGE_NONE][0]['postal_code']) ? $node->field_hb_location[LANGUAGE_NONE][0]['postal_code'] : FALSE;
    $add = str_replace(' , ', ', ', $add);
    $add = str_replace(',,', ',', $add);
  }

  dpm($add);
  dpm($original_add);
  dpm(md5($add));
  dpm(md5($original_add));

  if ( md5($add) !=  md5($original_add)) {
    $point = geocoder('google', $add, array('https' => TRUE));
    $geo_array = array(
      'geom' => 'POINT ('. $point->coords[0] . ' ' . $point->coords[1] .')',
      'geo_type' => 'point',
      // 'lat' => $point->coords[1],
      // 'lon' => $point->coords[0],
      // 'left' => $point->coords[0],
      // 'top' => $point->coords[1],
      // 'right' => $point->coords[0],
      // 'bottom' => $point->coords[1],
      // // 'geohash' => ,
    );

//     geom (String, 29 characters ) POINT (144.957248 -37.820716)
// geo_type (String, 5 characters ) point
// lat (String, 16 characters ) -37.820716000000
// lon (String, 16 characters ) 144.957248000000
// left (String, 16 characters ) 144.957248000000
// top (String, 16 characters ) -37.820716000000
// right (String, 16 characters ) 144.957248000000
// bottom (String, 16 characters ) -37.820716000000
// geohash (String, 12 characters ) r1r0fdfwkew1
    $node->field_hb_geofield[LANGUAGE_NONE][0] = $geo_array;
    // variable_set('geo_update:' . $nw->getIdentifier(), 1);
    dpm($geo_array, 'geo field?..');
    node_save($node);
  }
  else {
    dpm('no need to do anything!');
  }
}
