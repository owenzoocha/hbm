<?php

/**
 * @file
 * Provides form functionality to create events.
 */

/**
 * Implements hook_form().
 * Provides functionality to create an event.
 */
function models_forms_create_form($form, &$form_state) {
  global $user;

  if (arg(2) == 'edit') {
    if (is_numeric(arg(1))) {
      $nw = entity_metadata_wrapper('node', arg(1));
      if ($nw->value()) {
        drupal_set_title('Edit' . ' ' . $nw->label());
        drupal_set_title($nw->label() . ' - Update');

        $title = $nw->label();
        $notes = $nw->body->value() ? $nw->body->value()['value'] : FALSE;
        $form_state['hb_type'] = $nw->field_hb_type->value() ? $nw->field_hb_type->value() : FALSE;
        $hb_cost = $nw->field_hb_price_text->value() ? $nw->field_hb_price_text->value() : FALSE;

        $form_state['job_update'] = $nw->getIdentifier();
        drupal_add_js(array('form_type' => $form_state['hb_type']), 'setting');

        if ($nw->field_hb_gender->value()) {
          $field_hb_gender = array();
          foreach ($nw->field_hb_gender->getIterator() as $k => $v) {
            $field_hb_gender[] = $v->value();
          }
        }
        if ($nw->field_hb_ht->value()) {
          $field_hb_ht = array();
          foreach ($nw->field_hb_ht->getIterator() as $k => $v) {
            $field_hb_ht[] = $v->value();
          }
        }
        if ($nw->field_hb_ht_colour->value()) {
          $field_hb_ht_colour = array();
          foreach ($nw->field_hb_ht_colour->getIterator() as $k => $v) {
            $field_hb_ht_colour[] = $v->value();
          }
        }
        if ($nw->field_hb_ht_cut->value()) {
          $field_hb_ht_cut = array();
          foreach ($nw->field_hb_ht_cut->getIterator() as $k => $v) {
            $field_hb_ht_cut[] = $v->value();
          }
        }
        if ($nw->field_hb_bt->value()) {
          $field_hb_bt = array();
          foreach ($nw->field_hb_bt->getIterator() as $k => $v) {
            $field_hb_bt[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_makeup->value()) {
          $field_hb_bt_makeup = array();
          foreach ($nw->field_hb_bt_makeup->getIterator() as $k => $v) {
            $field_hb_bt_makeup[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_eyelashes->value()) {
          $field_hb_bt = array();
          foreach ($nw->field_hb_bt->getIterator() as $k => $v) {
            $field_hb_bt_eyelashes[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_eyebrows->value()) {
          $field_hb_bt_eyebrows = array();
          foreach ($nw->field_hb_bt_eyebrows->getIterator() as $k => $v) {
            $field_hb_bt_eyebrows[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_nails->value()) {
          $field_hb_bt_nails = array();
          foreach ($nw->field_hb_bt_nails->getIterator() as $k => $v) {
            $field_hb_bt_nails[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_waxing->value()) {
          $field_hb_bt_waxing = array();
          foreach ($nw->field_hb_bt_waxing->getIterator() as $k => $v) {
            $field_hb_bt_waxing[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_makeup->value()) {
          $field_hb_bt_makeup = array();
          foreach ($nw->field_hb_bt_makeup->getIterator() as $k => $v) {
            $field_hb_bt_makeup[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_facials->value()) {
          $field_hb_bt_facials = array();
          foreach ($nw->field_hb_bt_facials->getIterator() as $k => $v) {
            $field_hb_bt_facials[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_massage->value()) {
          $field_hb_bt_massage = array();
          foreach ($nw->field_hb_bt_massage->getIterator() as $k => $v) {
            $field_hb_bt_massage[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_tanning->value()) {
          $field_hb_bt_tanning = array();
          foreach ($nw->field_hb_bt_tanning->getIterator() as $k => $v) {
            $field_hb_bt_tanning[] = $v->value();
          }
        }

        $date_array = array();
        if ($nw->field_hb_time->value()) {
          foreach ($nw->field_hb_time->getIterator() as $k => $v) {
            $date_array[] = format_date($v->value(), 'custom', 'Y-m-d H:i:s');
          }
        }

        $hb_link = $nw->field_hb_link->value() ? $nw->field_hb_link->value()['url'] : FALSE;
        $hb_company = $nw->field_hb_company->value() ? $nw->field_hb_company->value() : FALSE;

        $dependent_locality = $nw->field_hb_location->value()['dependent_locality'] ? $nw->field_hb_location->value()['dependent_locality'] : FALSE;
        $thoroughfare = $nw->field_hb_location->value()['thoroughfare'] ? $nw->field_hb_location->value()['thoroughfare'] : FALSE;
        $premise = $nw->field_hb_location->value()['premise'] ? $nw->field_hb_location->value()['premise'] : FALSE;
        $locality = $nw->field_hb_location->value()['locality'] ? $nw->field_hb_location->value()['locality'] : FALSE;
        $administrative_area = $nw->field_hb_location->value()['administrative_area'] ? $nw->field_hb_location->value()['administrative_area'] : FALSE;
        $postal_code = $nw->field_hb_location->value()['postal_code'] ? $nw->field_hb_location->value()['postal_code'] : FALSE;
        $country = $nw->field_hb_location->value()['country'] ? $nw->field_hb_location->value()['country'] : 'AU';
      }
    }
  }

  // $form['#attached']['js'] = array(
  //   'https://cdnjs.cloudflare.com/ajax/libs/nanobar/0.2.1/nanobar.min.js' => array(
  //     'type' => 'external',
  //   ),
  //   'https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/js/bootstrap-datetimepicker.min.js' => array(
  //     'type' => 'external',
  //   ),
  //   drupal_get_path('module', 'models_forms') . '/js/models_forms.js',
  // );

  // $form['#attached']['css'] = array(
  //   'https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/css/bootstrap-datetimepicker.min.css' => array(
  //     'type' => 'external',
  //   ),
  // );

  $form['#attached']['js'] = array(
    'https://cdnjs.cloudflare.com/ajax/libs/nanobar/0.2.1/nanobar.min.js' => array(
      'type' => 'external',
    ),
    'http://maps.googleapis.com/maps/api/js?libraries=places&key=AIzaSyCLxwLPavRyWseQhhaiBVPvONNb1Korie0' => array(
      'type' => 'external',
    ),
    libraries_get_path('geocomplete') . '/' . 'jquery.geocomplete.min.js',
    drupal_get_path('module', 'models_forms') . '/js/models_forms_google_complete.js',
    libraries_get_path('combodate') . '/' .  'combodate.js',
    libraries_get_path('price_format') . '/' .  'jquery.price_format.2.0.min.js',
    drupal_get_path('module', 'models_forms') . '/js/models_forms.js',
  );


  $select_type  = '<div class="hbm-choose-type row">';
  $select_type .= '<div class="col-xs-4 choice-box">';
  $select_type .= '<div class="choice-type hair" data-hb_type="hair"><div class="hb-type hb-type-hair">Hair</div><span>I want to post a hair related job..</span></div>';
  $select_type .= '</div>';
  $select_type .= '<div class="col-xs-4 choice-box">';
  $select_type .= '<div class="choice-type beauty" data-hb_type="beauty"><div class="hb-type">Beauty</div><span>I want to post a beauty related job..</span></div>';
  $select_type .= '</div>';
  $select_type .= '<div class="col-xs-4 choice-box">';
  $select_type .= '<div class="choice-type personal" data-hb_type="personal"><div class="hb-type hb-type-personal">Personal</div><span>Make me a last minute model..</span></div>';
  $select_type .= '</div>';
  $select_type .= '</div>';

  $form['hbm_type'] = array(
    '#markup' => $select_type,
  );

  // $form['#theme'] = array('overwrite_create_job');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => isset($title) ? t('Edit Job') : t('Post a Job'),
  );

  $form['wrapper']['heading1'] = array(
    '#markup' => '<h2><span>1.</span> Job Information</h2>',
  );

  $form['wrapper']['intro'] = array(
    '#markup' => '<p id="form-intro"></p>',
  );

  $form['wrapper']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Job title'),
    '#description' => t('Give us a quick overview in 60 characters e.g:'),
    '#default_value' => isset($title) ? $title : FALSE,
    // '#required' => TRUE,
    '#maxlength' => 60,
    '#maxlength_js' => TRUE,
    '#suffix' => '<ul class="help-points"><li><em>Models needed for [hair treatment] on [date]</em></li><li>Free [beauty treatment] this weekend!</li><li>Last minute model looking for [hair/beauty treatment]</li></ul>',
  );

  $type = field_info_field('field_hb_gender');
  $options = list_allowed_values($type);
  $form['wrapper']['field_hb_gender'] = array(
    '#type' => 'select',
    '#title' => t('Who\'s it for?'),
    '#description' => t('You can select multiple gender.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_gender) ? $field_hb_gender : FALSE,
    // '#disabled' => isset($hb_type) ? TRUE : FALSE,
    // '#required' => TRUE,
  );

  // $type = field_info_field('field_hb_type');
  // $options = list_allowed_values($type);
  // $form['wrapper']['hbf_field_hb_type'] = array(
  //   '#type' => 'select',
  //   '#title' => t('What kind of Job is it?'),
  //   '#options' => $options,
  //   // '#chosen' => TRUE,
  //   '#default_value' => isset($hb_type) ? $hb_type : FALSE,
  //   '#disabled' => isset($hb_type) ? TRUE : FALSE,
  //   '#required' => TRUE,
  // );

  $form['wrapper']['hbf_field_hb_type'] = array(
    '#type' => 'hidden',
    // '#required' => TRUE,
    '#attributes' => array('id' => array('hbf_field_hb_type')),
  );

  // HAIR --------------------------------------------------
  // If HAIR was selected - commence the following:
  $type = field_info_field('field_hb_ht');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht'] = array(
    '#type' => 'select',
    '#title' => t('Select hair treatment type'),
    '#description' => t('You can select multiple hair treatment types.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_ht) ? $field_hb_ht : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht" class=" hide-hair">',
    '#suffix' => '</div>',
  );

  // If HAIR - COLOUR was selected - commence the following:
  $type = field_info_field('field_hb_ht_colour');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht_colour'] = array(
    '#type' => 'select',
    '#title' => t('Hair colour type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_ht_colour) ? $field_hb_ht_colour : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht_colour" class="hide-me hide-hair">',
    '#suffix' => '</div>',
  );

  // If HAIR - CUT was selected - commence the following:
  $type = field_info_field('field_hb_ht_cut');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht_cut'] = array(
    '#type' => 'select',
    '#title' => t('Hair cut type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_ht_cut) ? $field_hb_ht_cut : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht_cut" class="hide-me hide-hair">',
    '#suffix' => '</div>',
  );

  // BEAUTY --------------------------------------------------
  // If BEAUTY was selected - commence the following:
  $type = field_info_field('field_hb_bt');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt'] = array(
    '#type' => 'select',
    '#title' => t('Select beauty treatment type'),
    '#description' => t('You can select multiple beauty treatment types.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_bt) ? $field_hb_bt : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt" class="hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - MAKEUP was selected - commence the following:
  $type = field_info_field('field_hb_bt_makeup');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_makeup'] = array(
    '#type' => 'select',
    '#title' => t('Makeup type'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_bt_makeup) ? $field_hb_bt_makeup : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_makeup" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - EYELASHES was selected - commence the following:
  $type = field_info_field('field_hb_bt_eyelashes');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_eyelashes'] = array(
    '#type' => 'select',
    '#title' => t('Eyelashes type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_eyelashes) ? $field_hb_bt_eyelashes : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_eyelashes" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - EYEBROWS was selected - commence the following:
  $type = field_info_field('field_hb_bt_eyebrows');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_eyebrows'] = array(
    '#type' => 'select',
    '#title' => t('Eyebrows type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_eyebrows) ? $field_hb_bt_eyebrows : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_eyebrows" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - NAILS was selected - commence the following:
  $type = field_info_field('field_hb_bt_nails');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_nails'] = array(
    '#type' => 'select',
    '#title' => t('Nails type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_nails) ? $field_hb_bt_nails : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_nails" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - WAXING was selected - commence the following:
  $type = field_info_field('field_hb_bt_waxing');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_waxing'] = array(
    '#type' => 'select',
    '#title' => t('Hair Removal type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_waxing) ? $field_hb_bt_waxing : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_waxing" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - FACIALS was selected - commence the following:
  $type = field_info_field('field_hb_bt_facials');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_facials'] = array(
    '#type' => 'select',
    '#title' => t('Facials type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_facials) ? $field_hb_bt_facials : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_facials" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - MASSAGE was selected - commence the following:
  $type = field_info_field('field_hb_bt_massage');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_massage'] = array(
    '#type' => 'select',
    '#title' => t('Massage type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_massage) ? $field_hb_bt_massage : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_massage" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - TANNING was selected - commence the following:
  $type = field_info_field('field_hb_bt_tanning');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_tanning'] = array(
    '#type' => 'select',
    '#title' => t('Tanning type'),
    '#multiple' => TRUE,
    '#options' => $options,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_tanning) ? $field_hb_bt_tanning : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_tanning" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // STEP 2 ---------------
  $form['wrapper']['extra_info_btn'] = array(
    '#markup' => '<div id="step-extra-btn" class="text-center"><btn class="btn btn-sm btn-success">Continue</button></div>',
  );

  $form['wrapper']['step2_start'] = array(
    '#markup' => '<div id="step-extra">',
  );

  $form['wrapper']['heading2'] = array(
    '#markup' => '<h2><span>2.</span> Description</h2>',
  );

  $wysiwyg_js['wysiwyg']['configs']['tinymce']['formatfiltered_html'] = array(
    'menubar' => FALSE,
    'statusbar' => FALSE,
  );

  drupal_add_js($wysiwyg_js, 'setting');

  $form['wrapper']['notes'] = array(
    '#type' => 'text_format',
    '#title' => t('Tell us about your job, be as specific as you can'),
    // '#maxlength' => 600,
    // '#maxlength_js' => TRUE,
    '#default_value' => isset($notes) ? $notes : FALSE,
    '#format' => 'filtered_html'
    // '#description' => t('Tell us about your job, be as specific as you can.'),
  );


  if (!isset($form_state['job_update'])) {
    $form['wrapper']['field_hb_pics'] = array(
      '#type' => 'managed_file',
      '#default_value' => isset($file) ? $file : FALSE,
      '#title' => t('Image'),
      '#description' => t('You can upload more on the next page - jpg jpeg png / 2MB max'),
      '#upload_validators' => array(
        'file_validate_extensions' => array('jpg jpeg png'),
        'file_validate_size' => array(2000000),
      ),
      '#upload_location' => 'public://',
    );
  }

  // $form['wrapper']['contact_number'] = array(
  //   '#type' => 'textfield',
  //   '#title' => t('Contact Number'),
  //   '#default_value' => isset($hb_company) ? $hb_company : '',
  //   '#description' => t('Add a contact number if required'),
  // );

  $form['wrapper']['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Web link'),
    '#default_value' => isset($hb_link) ? $hb_link : '',
    '#attributes' => array('placeholder' => 'www.example.com'),
    '#description' => t('Add a web link for further information'),
  );

  $form['wrapper']['company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company/Studio/College name'),
    '#default_value' => isset($hb_company) ? $hb_company : '',
    '#description' => t('Where\'s it taking place? Hair Dressers? Beauticians?'),
  );

  $form['wrapper']['geocomplete'] = array(
    '#type' => 'textfield',
    // '#title' => 'Enter an address',
    '#description' => t('If your address is unrecognised, try the manual option below.'),
    '#attributes' => array(
      'id' => array('geocomplete'),
    ),
    '#prefix' => '<label class="control-label" for="geocomplete">' . t('Location lookup') . '</label>',
    '#suffix' => '<div class="map_canvas"></div><!--<p><a href="#" class="geocomplete-manual">' . t('+ add manual location') . '</a></p>-->',
  );

  // https://www.drupal.org/node/970048
  $form['wrapper']['location'] = array (
    '#type' => 'addressfield',
    '#title' => t('Location'),
    // '#description' => t('Location of the job.'),
    '#required' => FALSE,
    '#chosen' => TRUE,
    '#default_widget' => 'addressfield_standard',
    '#default_formatter' => 'addressfield_default',
    '#default_value' => array (
      'dependent_locality ' => isset($dependent_locality) ? $dependent_locality : FALSE,
      'thoroughfare' =>  isset($thoroughfare) ? $thoroughfare : FALSE,
      'premise' => isset($premise) ? $premise : FALSE,
      'locality' => isset($locality) ? $locality : FALSE,
      'administrative_area' => isset($administrative_area) ? $administrative_area : FALSE,
      'postal_code' => isset($postal_code) ? $postal_code : FALSE,
      'country' => 'AU',
    ),
    '#available_countries' => array('AU'),
  );

  $form['wrapper']['step2_end'] = array('#markup' => '</div>');

  $form['wrapper']['step3_start'] = array('#markup' => '<div id="after-location">');

  // $form['wrapper']['step3_start_btn'] = array(
  //   '#markup' => '<div id="step-address-continue" class="text-center"><btn class="btn btn-sm btn-success">Continue</button></div>',
  // );

  $form['wrapper']['heading3'] = array(
    '#markup' => '<h2><span>3.</span> Cost and Dates</h2>',
  );

  $form['wrapper']['cost'] = array(
    '#type' => 'textfield',
    '#title' => t('($) Costing'),
    '#default_value' => isset($hb_cost) ? $hb_cost : '',
    '#description' => t('How much will the job cost? Is it free or at discount? If personal, how much are you willing to pay?'),
    '#attributes' => array(
      'id' => array('hb-costing'),
    ),
    '#maxlength' => 150,
    '#maxlength_js' => TRUE,
  );

  $form['wrapper']['personal_add_date'] = array(
    '#markup' => '<div id="personal-add-date" class="form-item"><a class="btn btn-success" href="#">Add a date</a><div class="help-block">Last Minute Model? Add your availability dates or leave this blank</div></div>',
  );

  $form['wrapper']['date_wrapper'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="date-wrapper-ajax" class="form-group">',
    '#suffix' => '</div>',
  );

  if (isset($form_state['job_update'])) {
    if (!isset($form_state['date_count'])) {
      $form_state['date_count'] = sizeof($date_array);
    }

    $form['wrapper']['date_wrapper']['date_label'] = array(
      '#markup' => '<label>' . t('Appointments') . '</label>',
    );
    $previous_appointment = $form_state['date_count'] - 2 ;
  }
  else {
    $form_state['date_count'] = !isset($form_state['date_count']) ? 1 : $form_state['date_count'];
    $previous_appointment = FALSE;
  }

  for ($i = 0; $i < $form_state['date_count']; $i++) {
    if ($previous_appointment) {
      if (!empty($date_array[$i])) {
        $date_value = date('d-m-Y H:i', strtotime($date_array[$i]));
      }
      else {
        if ($i == $previous_appointment) {
          $date_value = date('d-m-Y H:i', strtotime($form_state['values']['date_' . $previous_appointment]));
        }
      }
    }
    else {
      $date_value = date('d-m-Y 09:00', strtotime('now'));
    }

    $form['wrapper']['date_wrapper']['date_' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('!amount. Date / Time', array('!amount' => $i + 1)),
      '#description' => $i+1 == $form_state['date_count'] ? t('Tell us the date and time for the job - leave blank if not needed.') : FALSE,
      '#attributes' => array(
        'id' => array('hb-datetime-' . $i),
        'data-template' => array('DD / MMM / YYYY     HH : mm'),
        'data-value' => array($date_value),
      ),
      '#prefix' => '<div class="row set-date"><div class="col-sm-12">',
      '#suffix' => '</div></div>',
    );
  }

  $form['wrapper']['date_wrapper']['add_more'] = array(
    '#type' => 'submit',
    '#value' => 'add',
    '#name' => 'add',
    '#submit' => array('add_a_date'),
    '#ajax' => array(
      'callback' => 'models_forms_create_form_ajax',
      'wrapper' => 'date-wrapper-ajax',
      'method' => 'replace',
      // 'effect' => 'fade',
    ),
    '#attributes' => array(
      'class' => array('btn-xs'),
    ),
    '#prefix' => '<div class="row"><div class="col-sm-12">',
  );

  $form['wrapper']['date_wrapper']['remove_more'] = array(
    '#type' => 'submit',
    '#value' => t('remove'),
    '#name' => 'remove',
    '#submit' => array('remove_a_date'),
    '#ajax' => array(
      'callback' => 'models_forms_create_form_ajax',
      'wrapper' => 'date-wrapper-ajax',
      'method' => 'replace',
      // 'effect' => 'fade',
    ),
    '#attributes' => array(
      'class' => array('btn-danger btn-xs'),
    ),
    '#suffix' => '</div></div>',
  );

  $h4 = !empty($form_state['hb_type']) ? t('Update Your Job') : t('Post Your Job');
  $form['wrapper']['heading4'] = array(
    '#markup' => '<h2><span>4.</span> ' . $h4 . '</h2><p>'. t('You can perform further updates on the next page and when you\'re ready, hit publish to get your page live!') . '</p>',
  );
  $form['wrapper']['submit_btn'] = array(
    '#type' => 'submit',
    '#name' => 'submit_job',
    '#value' => !empty($form_state['hb_type']) ? t('Update Job') : t('Post Job') ,
    // '#disabled' => sizeof($nw->field_t_users->value()) <= $fbk_size ? TRUE : FALSE,
    '#attributes' => array(
      // 'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
      'class' => array('btn-success btn-block'),
      // 'data-loading-text' => isset($form_state['hb_type']) ? array("Updating..") : array("Posting.."),
      'data-complete-text' => array('Saved!'),
    ),
    '#prefix' => '<div id="step-submit">',
    '#suffix' => '</div>',
  );

  $form['wrapper']['step3_end'] = array('#markup' => '</div>');
  return $form;
}

// Ajax call to upload more brief attachments
function add_a_date($form, &$form_state) {
  $form_state['date_count']++;
  $form_state['rebuild'] = TRUE;
  $form_state['ajaxify'] = TRUE;
}

function remove_a_date($form, &$form_state) {
  if ($form_state['date_count'] > 1) {
    $form_state['date_count']--;
    $form_state['rebuild'] = TRUE;
  }
}

function models_forms_create_form_ajax($form, $form_state) {
  return $form['wrapper']['date_wrapper'];
}


/**
 * Custom submit function for models_forms_create_form_submit.
 */
function models_forms_create_form_submit(&$form, &$form_state){
  global $user;

  // dpm($form_state, 'fs');

  $fs = $form_state['values'];

  if (!isset($form_state['job_update'])) {
    $node = new stdClass();
    $node->type = "job";
    $node->create = strtotime('now');
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->status = 0;
  } else {
    $node = node_load($form_state['job_update']);
    $node->updated = strtotime('now');
    unset($node->field_hb_gender[LANGUAGE_NONE]);
    unset($node->field_hb_ht[LANGUAGE_NONE]);
    unset($node->field_hb_ht_colour[LANGUAGE_NONE]);
    unset($node->field_hb_ht_cut[LANGUAGE_NONE]);
    unset($node->field_hb_bt[LANGUAGE_NONE]);
    unset($node->field_hb_bt_makeup[LANGUAGE_NONE]);
    unset($node->field_hb_bt_eyelashes[LANGUAGE_NONE]);
    unset($node->field_hb_bt_eyebrows[LANGUAGE_NONE]);
    unset($node->field_hb_bt_nails[LANGUAGE_NONE]);
    unset($node->field_hb_bt_waxing[LANGUAGE_NONE]);
    unset($node->field_hb_bt_facials[LANGUAGE_NONE]);
    unset($node->field_hb_bt_massage[LANGUAGE_NONE]);
    unset($node->field_hb_bt_tanning[LANGUAGE_NONE]);
  }

  $node->title = $fs['title'];

  $type = $fs['hbf_field_hb_type'];
  if (!empty($type)) {
    $node->field_hb_type[LANGUAGE_NONE][0]['value'] = $type;

    if(!empty($fs['field_hb_gender'])){
      foreach ($fs['field_hb_gender'] as $k => $v) {
        $node->field_hb_gender[LANGUAGE_NONE][]['value'] = $v;
      }
    }

    if ($type == 'hair' || $type == 'personal') {
      if(!empty($fs['hbf_field_hb_ht'])){
        foreach ($fs['hbf_field_hb_ht'] as $k => $v) {
          $node->field_hb_ht[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_ht_colour'])){
        foreach ($fs['hbf_field_hb_ht_colour'] as $k => $v) {
          $node->field_hb_ht_colour[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_ht_cut'])){
        foreach ($fs['hbf_field_hb_ht_cut'] as $k => $v) {
          $node->field_hb_ht_cut[LANGUAGE_NONE][]['value'] = $v;
        }
      }
    }

    if ($type == 'beauty' || $type == 'personal') {
      if(!empty($fs['hbf_field_hb_bt'])){
        foreach ($fs['hbf_field_hb_bt'] as $k => $v) {
          $node->field_hb_bt[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_makeup'])){
        foreach ($fs['hbf_field_hb_bt_makeup'] as $k => $v) {
          $node->field_hb_bt_makeup[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_eyelashes'])){
        foreach ($fs['hbf_field_hb_bt_eyelashes'] as $k => $v) {
          $node->field_hb_bt_eyelashes[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_eyebrows'])){
        foreach ($fs['hbf_field_hb_bt_eyebrows'] as $k => $v) {
          $node->field_hb_bt_eyebrows[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_nails'])){
        foreach ($fs['hbf_field_hb_bt_nails'] as $k => $v) {
          $node->field_hb_bt_nails[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_waxing'])){
        foreach ($fs['hbf_field_hb_bt_waxing'] as $k => $v) {
          $node->field_hb_bt_waxing[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_facials'])){
        foreach ($fs['hbf_field_hb_bt_facials'] as $k => $v) {
          $node->field_hb_bt_facials[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_massage'])){
        foreach ($fs['hbf_field_hb_bt_massage'] as $k => $v) {
          $node->field_hb_bt_massage[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_tanning'])){
        foreach ($fs['hbf_field_hb_bt_tanning'] as $k => $v) {
          $node->field_hb_bt_tanning[LANGUAGE_NONE][]['value'] = $v;
        }
      }
    }
  }

  // Body.
  if(!empty($fs['notes'])){
    $node->body[LANGUAGE_NONE][0]['value'] = $fs['notes']['value'];
    $node->body[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  }

  if(!empty($fs['link'])){
    $url = $fs['link'];
    if (!preg_match("~^(?:f|ht)tps?://~i", $url)) {
        $url = "http://" . $fs['link'];
    }
    if (filter_var($url, FILTER_VALIDATE_URL)) {
      $node->field_hb_link[LANGUAGE_NONE][0]['url'] = $url;
    }
    else {
      $node->field_hb_link[LANGUAGE_NONE][0]['url'] = '';
    }
  }

  if (!empty($fs['company'])){
    $node->field_hb_company[LANGUAGE_NONE][]['value'] = $fs['company'];
  }

  $node->field_hb_price_text[LANGUAGE_NONE][0]['value'] = $fs['cost'];

//  if ( !empty($fs['cost']) && ltrim($fs['cost'], '$') != 0.00 ){
//    $node->field_hb_price[LANGUAGE_NONE][0]['value'] = ltrim($fs['cost'], '$');
//    $node->field_hb_price_type[LANGUAGE_NONE][0]['value'] = 'fixed';
//  }
//  else {
//    $node->field_hb_price[LANGUAGE_NONE][0]['value'] = 0.00;
//    $node->field_hb_price_type[LANGUAGE_NONE][0]['value'] = 'free';
//  }

  // Date.
  unset($node->field_hb_time);
  $date_i = 0;
  foreach ($fs as $key => $date_value) {
    if (preg_match('/^date_/', $key)) {

      if ( strtotime($date_value) > strtotime('now') ) {
        if ( date('Y', strtotime($date_value)) != '1970' ) {
          $date = format_date(strtotime( str_replace('/', '-', $date_value)), 'custom', 'Y-m-d H:i:s', 'UTC');
          $node->field_hb_time[LANGUAGE_NONE][$date_i]['value'] = $date;
          $date_i++;
        }
        else {
          unset($node->field_hb_time);
        }
      }
    }
  }

  $node->field_hb_location[LANGUAGE_NONE][0]['thoroughfare'] = $fs['location']['thoroughfare'] ? $fs['location']['thoroughfare'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['premise'] = $fs['location']['premise'] ? $fs['location']['premise'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['dependent_locality'] = $fs['location']['dependent_locality'] ? $fs['location']['dependent_locality'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['locality'] = $fs['location']['locality'] ? $fs['location']['locality'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['administrative_area'] = $fs['location']['administrative_area'] ? $fs['location']['administrative_area'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['postal_code'] = $fs['location']['postal_code'] ? $fs['location']['postal_code'] : FALSE;
  $node->field_hb_location[LANGUAGE_NONE][0]['country'] = $fs['location']['country'] ? $fs['location']['country'] : FALSE;

  node_save($node);

  // if (!isset($form_state['job_update'])) {
  //   drupal_set_message(t('Your Job: ' . $fs['title'] . ' has been posted '), 'info', FALSE);
  // }
  // else {
  //   drupal_set_message(t('Your Job: ' . $fs['title'] . ' has been updated '), 'success', FALSE);
  // }
  // dpm($form_state);
  //
  $nw = entity_metadata_wrapper('node', $node->nid);
  if (!empty($fs['field_hb_pics'])) {
    // $nw = entity_metadata_wrapper('node', $node->nid);
    $ew = entity_create('pics', array('type' => 'pics'));
    $title = 'pics_0_' . $nw->getIdentifier() . '_' . $nw->label();
    $ew->title = $title;
    $ew->created = strtotime('now');
    $ew->changed = strtotime('now');

    $file = file_load($fs['field_hb_pics']);
    $ew->field_pics_img[LANGUAGE_NONE][0] = (array) $file;
    $ew->save();

    $nw->field_hb_pics[] = $ew->id;
    $nw->save();
  }

  // Check if there's a last day - if so, schedule the complete flag.
  if ($nw->field_hb_time->value()) {
    $date_n = sizeof($nw->field_hb_time->value()) - 1;
    $last_day = $nw->field_hb_time->value()[$date_n];
    rules_invoke_component('rules_set_schedule_schedule_the_complete_job', $last_day, $nw->value());
  }

  drupal_goto('node/' . $node->nid);
}
