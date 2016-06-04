<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (isset($unpub_msg)): print $unpub_msg; endif; ?>
  <?php if ($show_slick) : ?>
  <div class="job-lhs job-content">
    <?php
      $slick_block = block_load('models_imgs', 'job_slider');
      $block = _block_get_renderable_array(_block_render_blocks(array($slick_block)));
      print drupal_render($block);
    ?>
  </div>
  <?php endif; ?>

  <div class="job-rhs job-content">
    <div class="job-info">
      <h2 class="block-title">About</h2>
      <?php
        print render($content['body']);
      ?>
    </div>
</div>
  <?php if (isset($job_request_form)): print $job_request_form; endif;?>
  <?php if (isset($job_publish_form)): print $job_publish_form; endif;?>
  <?php if (isset($job_cancel_form)): print $job_cancel_form; endif;?>
  <?php if (isset($job_pause_form)): print $job_pause_form; endif;?>
</article>
