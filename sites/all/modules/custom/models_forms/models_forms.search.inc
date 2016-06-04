<?php
//
function models_forms_search_form($form, &$form_state){
  $params = drupal_get_query_parameters();
  // dpm($params);
  $s = !empty($params) && isset($params['search']) && $params['search'] != '' ? $params['search'] : t('Search + press enter');
  $form['search'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => array($s),
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#attributes' => array(
      'class' => array('btn btn-ops'),
    ),
  );
  return $form;
}

function models_forms_search_form_submit($form, &$form_state){
  $s = $form_state['values']['search'];
  drupal_goto('task-search', array('query' => array('search' => $s)), 302);
}
