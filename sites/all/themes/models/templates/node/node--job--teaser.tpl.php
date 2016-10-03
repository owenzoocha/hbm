<div class="views-row-surrounder">
  <?php if (isset($job_status)): ?>
    <div class="status <?php print 'status-' . str_replace(' ', '-', strtolower($job_status)); ?>">
      <?php print $job_status; ?>
    </div>
  <?php endif; ?>
  <?php print $the_image; ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print render($title_prefix); ?>
    <?php if (!$page): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php print $the_type; ?>
    <div class="content"<?php print $content_attributes; ?>>
      <?php
        print $author_pic;
        print $posted_by;
//        print $stars;
        print $location;
        print $created;
        print $starting;
        print $costs;
        print $more_info;
        if (isset($requestees)): print $requestees; endif;
      ?>
    </div>
  </div>

  <div class="more-info">
    <p><?php print $description; ?></p>
    <p><?php print $more_info_list; ?></p>
    <p><?php print $view_link; ?></p>
  </div>

</div>
