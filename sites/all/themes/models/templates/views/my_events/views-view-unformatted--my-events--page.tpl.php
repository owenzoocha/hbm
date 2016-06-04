<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<div class="views-row views-row-first col-md-3 col-sm-4">
  <div class="views-field views-field-rendered-entity">
    <span class="field-content">
      <?php
        $node_add = '<div id="node-add" class="node node-event node-promoted node-teaser contextual-links-region clearfix" about="event/create" typeof="sioc:Item foaf:Document">
            <span property="dc:title" content="Add event" class="rdf-meta element-hidden"></span><span property="sioc:num_replies" content="0" datatype="xsd:integer" class="rdf-meta element-hidden"></span>
            <div class="content">
              <h2 class="sr-only">Add event</h2>
              <span><i class="fa fa-3x fa-plus"></i></span>
            </div>
          </div>';
        print l($node_add, 'event/create', array('html' => TRUE, 'attributes' => array('class' => array('node-add-create'))));
      ?>
    </span>
  </div>
</div>

<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
