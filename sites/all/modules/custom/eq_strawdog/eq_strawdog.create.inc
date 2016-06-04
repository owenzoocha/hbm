<?php

/**
 * @file
 * Provides functionality to create the strawdog (agenda) builder.
 */


/**
 * Return the theme function to generate strawdog builder.
 */
function eq_strawdog_create($nid) {
  // dpm($nid);
  return theme('strawdog_create');
}


/**
 * Implements of hook_theme().
 */
function eq_strawdog_theme() {
  return array (
    'strawdog_create' => array(
      'template' => 'templates/strawdog-create',
    ),
  );
}

/**
 * Template preprocess for Event Nav.
 */
function template_preprocess_strawdog_create(&$vars) {
  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.12.0/moment.min.js', 'external');

  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.contextMenu.min.js', 'external');
  drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.contextMenu.min.css', 'external');
  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.ui.position.min.js', 'external');

  drupal_add_js(libraries_get_path('bootstrap-timepicker') . '/js/bootstrap-timepicker.js');

  drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/bootstrap-touchspin/3.1.1/jquery.bootstrap-touchspin.min.css', 'external');
  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/bootstrap-touchspin/3.1.1/jquery.bootstrap-touchspin.min.js', 'external');

  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.contextMenu.min.js', 'external');
  drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.contextMenu.min.css', 'external');
  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/jquery-contextmenu/2.1.1/jquery.ui.position.min.js', 'external');

  drupal_add_js(libraries_get_path('dragula') . '/dist/dragula.min.js');
  drupal_add_css(libraries_get_path('dragula') . '/dist/dragula.min.css');
  drupal_add_js(drupal_get_path('module', 'eq_strawdog') . '/js/eq_strawdog.js');

  $strawdog_time_form = drupal_get_form('strawdog_time_form');
  $modal_options_time = array(
    'attributes' => array('id' => 'strawdog-time', 'class' => array('event-custom-popup-modal')),
    'heading' => t('Set Time'),
    'body' => drupal_render($strawdog_time_form),
  );

  $strawdog_splitter_form = drupal_get_form('strawdog_splitter_form');
  $modal_options_splitter = array(
    'attributes' => array('id' => 'strawdog-splitter', 'class' => array('event-custom-popup-modal')),
    'heading' => t('Split Mod'),
    'body' => drupal_render($strawdog_splitter_form),
  );
  $vars['time_popup'] = theme('bootstrap_modal', $modal_options_time);
  $vars['splitter_popup'] = theme('bootstrap_modal', $modal_options_splitter);
}

/**
 * Implements hook_form().
 * Provides functionality to set times for each mod.
 */
function strawdog_time_form($form, &$form_state) {
  $form['time_markup'] = array(
    '#markup' => '<div class="form-group">
      <label class="control-label" for="edit-time">Start time: </label>
      <div class="input-group date" id="start-time">
        <input type="text" class="form-control" />
        <span class="input-group-addon">
          <span class="fa fa-clock-o"></span>
        </span>
      </div>
    </div>',
  );
  $form['duration_markup'] = array(
    '#markup' => '<div class="form-group">
      <label class="control-label" for="edit-duration">Duration: </label>
      <div class="input-group date" id="duration-time">
        <input type="text" class="form-control" />
      </div>
    </div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("Save.."),
      'data-complete-text' => array('Saved!'),
    ),
  );
  return $form;
}
/**
 * Implements hook_form().
 * Provides functionality to split element on strawdog builder.
 */
function strawdog_splitter_form($form, &$form_state) {
  $ops = array(
    2 => 2,
    3 => 3,
    4 => 4,
    5 => 5,
    6 => 6,
    7 => 7,
    8 => 8,
    9 => 9,
    10 => 10,
  );
  $form['split'] = array(
    '#type' => 'select',
    '#chosen' => true,
    '#default' => 2,
    '#title' => t('Total to split:'),
    '#options' => $ops,
    '#multiple' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Split'),
    '#attributes' => array(
      'class' => array('btn-success'),
      'data-loading-text' => array("Save.."),
      'data-complete-text' => array('Saved!'),
    ),
  );
  return $form;
}

