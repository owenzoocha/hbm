<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="rate-author">
    <?php print $pic; ?>
    <?php print $author; ?>
    <?php // print $author_rating; ?>
  </div>
  <div class="rate-feedback">
    <?php print $type; ?>
    <?php print $stars; ?>
    <?php print render($content['field_feedback']); ?>
    <?php print $job; ?>
  </div>
</div>
