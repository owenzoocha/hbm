<div class="hybridauth-widget-wrapper"><?php
  print theme('item_list',
    array(
      'items' => $providers,
      // 'title' => $element['#title'],
      'type' => 'ul',
      'attributes' => array('class' => array('hybridauth-widget')),
    )
  );
?>
  <h3><?php print $element['#title']; ?></h3>
</div>
