<div class="views-row-surrounder">
  <?php print $image_and_type; ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print render($title_prefix); ?>
    <?php if (!$page): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <div class="content"<?php print $content_attributes; ?>>
      <?php
        print $author_pic;
        print $posted_by;
        print $stars;
        if (isset($requestees)): print $requestees; endif;
      ?>
    </div>
  </div>
  <div class="summary">
    <?php print $location; ?>
    <?php print $created; ?>
    <?php print $starting; ?>
  </div>
  <?php if (isset($job_status)): ?>
    <div class="status <?php print 'status-' . str_replace(' ', '-', strtolower($job_status)); ?>">
      <?php print $job_status; ?>
    </div>
  <?php endif; ?>

</div>
