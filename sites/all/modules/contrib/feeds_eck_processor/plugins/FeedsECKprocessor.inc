<?php

class FeedsECKprocessor extends FeedsProcessor {

  /**
   * Define entity type.
   */
  public function entityType() {
    return $this->config['entity_type'];
  }
  
  protected function entityInfo() {
    $info = parent::entityInfo();
    $entities = eck_entity_info();
    $info['label plural'] = isset($entities[$this->entityType()]['label']) ?
        $entities[$this->entityType()]['label'] : NULL;
    return $info;
  }

  protected function newEntity(FeedsSource $source) {
    $properties = eck_entity_property_info();
    $properties = $properties[$this->entityType()]['properties'];
    
    $entity = new stdClass();
    $entity->type = $this->bundle();
    if (!empty($properties['created'])) {
      $entity->created = REQUEST_TIME;
    }
    if (!empty($properties['changed'])) {
      $entity->changed = REQUEST_TIME;
    }
    if (!empty($properties['language'])) {
      $entity->language = LANGUAGE_NONE;
    }
    if (!empty($properties['uid'])) {
      $entity->uid = $this->config['author'];
    }
    return $entity;
  }

  protected function entityLoad(FeedsSource $source, $id) {
    $entity = parent::entityLoad($source, $id);
    return $entity;
  }

  protected function entitySaveAccess($entity) {
  }
  
  protected function entityValidate($entity) {
  }

  public function entitySave($entity) {
    entity_save($this->entityType(), $entity);
  }
  
  protected function entityDeleteMultiple($ids) {
    entity_delete_multiple($this->entityType(), $ids);
  }
  
  public function expire(FeedsSource $source, $time = NULL) {
    return;
  }
  
  public function expiryTime() {
    return 0;
  }
  
  public function configDefaults() {
    return array(
      'entity_type' => NULL,
      'bundle' => NULL,
      'expire' => FEEDS_EXPIRE_NEVER,
      'author' => 0,
      'authorize' => TRUE,
    ) + parent::configDefaults();
  }

  public function configForm(&$form_state) {
    $entities = eck_entity_info();
    if (empty($entities)) {
      return array(
        '#type' => 'markup',
        '#markup' => t('First, create the entity using ECK module '),
      );
    }

    $entity_type = isset($form_state['values']['entity_type']) ? $form_state['values']['entity_type'] : $this->config['entity_type'];
    //get first entity type if value not initialised
    if (empty($entity_type)) {
      $types = array_keys($entities);
      $entity_type = $types[0];
    }

    //update $form_state values for ajax reload form elements work properly
    $bundle = isset($form_state['values']['bundle'])
              ? $form_state['values']['entity_type']
              : $this->bundle();

    $expire = isset($form_state['values']['expire'])
              ? $form_state['values']['expire']
              : $this->config['expire'];

    $author = isset($form_state['values']['author'])
              ? $form_state['values']['author']
              : $this->config['author'];

    $authorize = isset($form_state['values']['authorize'])
              ? $form_state['values']['authorize'] 
              : $this->config['authorize'];

    $update_existing = isset($form_state['values']['update_existing']) 
                       ? $form_state['values']['update_existing'] 
                       : $this->config['update_existing'];

    $properties = eck_entity_property_info();
    $properties = $properties[$entity_type]['properties'];
    $entity_label = $entities[$entity_type]['label'];

    $form = parent::configForm($form_state);
    unset($form['bundle'], $form['update_existing']);

    $weight = 7;
    foreach ($form as &$element) {
      $element['#weight'] = $weight++;
    }

    $options = array();
    foreach ($entities as $id => $entity) {
      $options[$id] = $entity['label'];
    }
    $form['entity_type'] = array(
      '#type' => 'select',
      '#title' => t('Select entity type'),
      '#options' => $options,
      '#default_value' => $entity_type,
      '#weight' => 0,
      '#ajax' => array(
        'callback' => 'feeds_eck_processor_ajax_callback',
        'wrapper' => 'form-ajaxed-controls',
        'method' => 'replace',
        'effect' => 'fade',
      )
    );

    $form['container'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => 'form-ajaxed-controls',
        '#weight' => 1,
      ),
    );

    $options = array();
    foreach ($entities[$entity_type]['bundles'] as $id => $bndl) {
      $options[$id] = $bndl['label'];
    }
    $form['container']['bundle'] = array(
      '#type' => 'select',
      '#title' => t('Select bundle'),
      '#options' => $options,
      '#default_value' => in_array($bundle, array_keys($options)) ? $bundle : NULL,
      '#weight' => 2,
    );

    if (!empty($properties['uid'])) {
      $form['container']['authorize'] = array(
        '#type' => 'checkbox',
        '#title' => t('Authorize'),
        '#description' => t('Check that the author has permission to create the entity.'),
        '#default_value' => $authorize,
        '#weight' => 3,
      );
    }

    if (!empty($properties['created'])) {
      $period = drupal_map_assoc(array(FEEDS_EXPIRE_NEVER, 3600, 10800, 21600, 43200, 86400, 259200, 604800, 2592000, 2592000 * 3, 2592000 * 6, 31536000), 'feeds_format_expire');
      $form['container']['expire'] = array(
        '#type' => 'select',
        '#title' => t('Expire enities'),
        '#options' => $period,
        '#description' => t('Select after how much time entities should be deleted. The entities\'s published date will be used for determining the entities\'s age, see Mapping settings.'),
        '#default_value' => $expire,
        '#weight' => 4,
      );
    }
    if (!empty($properties['uid'])) {
      $form['container']['author'] = array(
        '#type' => 'textfield',
        '#title' => t('Author'),
        '#description' => t('Select the author of the entities to be created - leave empty to assign "anonymous".'),
        '#autocomplete_path' => 'user/autocomplete',
        '#default_value' => empty($author) ?  '' : $author,
        '#weight' => 5,
      );
    }
    //overwrite default update_existing form element for dynamically change entity label
    $tokens = array('@entities' => $entity_label);
    $form['container']['update_existing'] = array(
      '#type' => 'radios',
      '#title' => t('Update existing @entities', $tokens),
      '#description' => t('Existing @entities will be determined using mappings that are a "unique target".', $tokens),
      '#options' => array(
        FEEDS_SKIP_EXISTING => t('Do not update existing @entities', $tokens),
        FEEDS_REPLACE_EXISTING => t('Replace existing @entities', $tokens),
        FEEDS_UPDATE_EXISTING => t('Update existing @entities', $tokens),
      ),
      '#default_value' => $update_existing,
      '#weight' => 6,
    );
    return $form;
  }

  public function configFormSubmit(&$values) {
    parent::configFormSubmit($values);
  }

  public function setTargetElement(FeedsSource $source, $target_entity, $target_element, $value) {
    switch ($target_element) {
      case 'created':
        $target_entity->created = feeds_to_unixtime($value, REQUEST_TIME);
        break;
      case 'changed':
        $target_entity->changed = feeds_to_unixtime($value, REQUEST_TIME);
        break;
      default:
        parent::setTargetElement($source, $target_entity, $target_element, $value);
        break;
    }
  }

  public function getMappingTargets() {
    $properties = eck_entity_property_info();
    $properties = $properties[$this->entityType()]['properties'];
    unset($properties['type']);

    $targets = parent::getMappingTargets();

    foreach ($properties as $id => $property) {
      $targets[$id] = array(
        'name' => $property['label'],
        'description' => $property['description'],
      );
    }

    if (!empty($targets['id'])) {
      $targets['id']['optional_unique'] = TRUE;
    }
    if (!empty($targets['title'])) {
      $targets['title']['optional_unique'] = TRUE;
    }

    // Let other modules expose mapping targets.
    self::loadMappers();
    $entity_type = $this->entityType();
    $bundle = $this->bundle();
    drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);

    return $targets;
  }

  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    if ($id = parent::existingEntityId($source, $result)) {
      return $id;
    }

    // Iterate through all unique targets and test whether they do already
    // exist in the database.
    $entities = eck_entity_info();
    $table = $entities[$this->entityType()]['base table'];
    foreach ($this->uniqueTargets($source, $result) as $target => $value) {
      switch ($target) {
        case 'id':
          $id = db_query("SELECT id FROM {" . $table . "} WHERE id = :id", array(':id' => $value))->fetchField();
          break;
        case 'title':
          $id = db_query("SELECT id FROM {" . $table . "} WHERE title = :title AND type = :type", array(':title' => $value, ':type' => $this->bundle()))->fetchField();
          break;
      }
      if ($id) {
        // Return with the first id found.
        return $id;
      }
    }
    return 0;
  }
}

//callback for dynamically update plugin settings form elements
function feeds_eck_processor_ajax_callback($form, $form_state) {
  return $form['container'];
}
