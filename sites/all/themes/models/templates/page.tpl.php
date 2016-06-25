<?php print $social; ?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <div class="container-fluid">
    <div class="navbar-header">
      <?php if ($logo): ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
        <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>

      <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($home_nav) || !empty($page['navigation'])): ?>
        <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
          <span class="sr-only"><?php print t('Toggle navigation'); ?></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
        </button>
      <?php endif; ?>
    </div>

    <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($home_nav) || !empty($page['navigation'])): ?>
      <div class="navbar-collapse collapse">
        <nav role="navigation">
          <?php if (!empty($primary_nav)): ?>
            <?php print render($primary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($secondary_nav)): ?>
            <?php // print render($secondary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($search_menu)): ?>
            <?php print $search_menu; ?>
          <?php endif; ?>
          <?php if (!empty($custom_nav)): ?>
            <?php print $custom_nav; ?>
          <?php endif; ?>
          <?php if (!empty($home_nav)): ?>
            <?php print $home_nav; ?>
          <?php endif; ?>
          <?php if (!empty($page['navigation'])): ?>
            <?php print render($page['navigation']); ?>
          <?php endif; ?>
        </nav>
      </div>
    <?php endif; ?>
  </div>
</header>

<div id="hb-header" class="container-fluid <?php if (empty($my_nav)): print 'no-my-nav '; endif; ?><?php print $title_search_class; ?>">

  <?php if (!empty($my_nav) || isset($show_bg)): ?>
  <div id="page-header-bg" data-0="transform: translateY(-100px);" data-300="transform: translateY(0);"></div>
  <?php endif; ?>

  <div class="container">
    <div class="<?php if (!empty($hb_header_class)): print $hb_header_class; endif;?>">
      <h1 class="page-header"><?php print $title; ?></h1>
      <?php
        if (!empty($job_details)) {
          print $job_details;
        }
      ?>
    </div>
    <?php print render($title_suffix); ?>
    <?php // if (!empty($breadcrumb)): print $breadcrumb; endif;?>
    <?php
      if (!empty($author_pic)) {
        print '<div class="pull-right header-author-pic">'. $author_pic . $author_rating . $author_feedback_amount . '</div>';
      }
      if (!empty($filter_blocks)) {
        print '<div class="pull-right">' . $filter_blocks . '</div>';
      }
    ?>
    <a id="main-content"></a>
  </div>
</div>

<?php if (!empty($my_nav)): ?>
<div class="my-nav">
  <div class="container">
    <nav role="navigation">
      <?php print $my_nav; ?>
    </nav>
  </div>
</div>
<?php endif; ?>

<div class="main-container <?php print $container_class; ?>">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->

  <div class="row">

    <?php if (!empty($page['sidebar_second'])): ?>
      <aside class="col-sm-push-9 col-sm-3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

    <?php if (!empty($page['sidebar_first'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    <section<?php print $content_column_class; ?>>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php if (!empty($page['search_top'])): ?>
        <?php print render($page['search_top']); ?>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php  if (isset($client_request_confirm_form)) : print $client_request_confirm_form; endif; ?>
    </section>
  </div>
</div>

<?php if (!empty($page['footer'])): ?>
  <?php if (!isset($no_footer)): ?>
    <div class="footer-surround">
      <footer class="footer container-fluid">
        <?php print render($page['footer']); ?>
      </footer>
    <footer class="footer-cr container-fluid">
      <span class="cr"><?php print '&copy; ' . t(':date hairandbeautymodels.com all rights reserved.', array(':date' => date('Y', strtotime('now')))); ?></span>
    </footer>
  </div>
  <?php endif; ?>
<?php endif; ?>
