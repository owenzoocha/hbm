<?php if ($info_long) : ?>
<div class="row">
  <div class="hbm-user-details col-sm-12">
    <div class="hbm-user-details-wrapper">
        <div class="extend-this">
        <?php
          print $name;
          // print $username;
          // print $add;
          // print $company;
          // print $college;
          if ($info) { print $info; } ;
          if ($info_long) { print $info_long; } ;
          // print $web;
        ?>
      </div>
    </div>
  </div>
</div>
<?php endif; ?>
<div class="row">
  <div class="hbm-user-details-slick col-sm-12">
    <div class="hbm-user-details-wrapper">
      <?php
        print $jobs_title;
        $jobs_block = block_load('views', 'user_profile_jobs-block_2');
        $block1 = _block_get_renderable_array(_block_render_blocks(array($jobs_block)));
        print drupal_render($block1);
      ?>
    </div>
  </div>
</div>
