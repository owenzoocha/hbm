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
            <?php // print $search_menu; ?>
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
<main id="main" role="main">
  <div id="hero">
    <div class="hero-content container">
      <div class="hero left">
        <h1>Welcome to</br>Hair and Beauty Models</h1>
        <h2>Training as a hair dresser or beautician? Looking for last minute models? Or just looking for a cheap cut!</h2>
        <p><strong>Coming Soon!</strong> Sign up to receive the latest news</p>
      </div>
      <div class="hero right">
        <?php
          $slick_block = block_load('webform', 'client-block-166');
          $block = _block_get_renderable_array(_block_render_blocks(array($slick_block)));
          print drupal_render($block);
        ?>
      </div>
    </div>
  </div>

  <div id="what-is-it" class="container">
    <div class="col-md-4">
      <div class="what-block">
        <h3>Search hair & beauty jobs or last minute models</h3>
       <!--  <div class="search-img">
          <img class="img-responsive" src="/sites/all/themes/models/images/search-example.png" alt="Search for jobs" title="Search for jobs"/>
        </div> -->
      </div>
    </div>
    <div class="col-md-4">
      <div class="what-block">
        <h3>Manage your clients, improve your profile</h3>
        <!-- <div class="manage-img">
          <img class="img-responsive" src="/sites/all/themes/models/images/manage-clients-example.png" alt="Manage clients" title="Manage clients"/>
        </div> -->
      </div>
    </div>
    <div class="col-md-4">
      <div class="what-block">
        <h3>Leave, receive feedback and give ratings!</h3>
        <!-- <div class="manage-img">
          <img class="img-responsive" src="/sites/all/themes/models/images/feedback-example.png" alt="Leave feedback and ratings" title="Leave feedback and ratings"/>
        </div> -->
      </div>
    </div>
  </div>

<!--   <div id="landing-page-2" class="container">
    <div class="col-md-6">
      <div class="what-block">
        <h3>Search for Hair and Beauty jobs - or last minute models</h3>
      </div>
    </div>
    <div class="col-md-6">
      <div class="what-block">
        <h3>Manage your clients, receive feedback and improve your profile!</h3>
      </div>
    </div>
  </div> -->

</main>

<div class="main-container <?php print $container_class; ?>">
   <div class="row">
    <section<?php print $content_column_class; ?>>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php print $messages; ?>
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
  <div class="footer-surround">
    <?php if (!isset($no_footer)): ?>
      <footer class="footer container-fluid">
        <?php print render($page['footer']); ?>
      </footer>
    <?php endif; ?>
    <footer class="footer-cr container-fluid">
      <span class="cr"><?php print '&copy; ' . t(':date hairandbeautymodels.com all rights reserved.', array(':date' => date('Y', strtotime('now')))); ?></span>
    </footer>
  </div>
<?php endif; ?>

