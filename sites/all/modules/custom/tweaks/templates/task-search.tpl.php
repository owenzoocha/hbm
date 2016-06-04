<?php if($show_filters): ?>
<div class="task-filter-icon pull-left my-menu">
  <a href="#" class="my-menu-link">
    <span><i class="fa fa-plus"></i> Filters</span>
  </a>
  <?php print $active_menu; ?>
</div>
<?php endif; ?>
<div class="search-surround pull-left">
  <div class="task-search-icon pull-left">
    <span><i class="fa fa-2x fa-search"></i></span>
  </div>
  <div class="task-search pull-left">
    <?php print $search_box; ?>
  </div>
</div>
