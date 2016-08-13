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
      <div class="hero left animated fadeInUp">
        <h1>Welcome to</br>Hair and Beauty Models</h1>
        <h2>Training as a hair dresser or beautician? Looking for last minute models? Or just looking for a cheap cut!</h2>
        <p><strong style="font-size: 27px;">Coming Soon!</strong> Sign up to receive the latest news</p>
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
    <h3 class="text-center hd-pink">Why #HBM?</h3>
    <div class="col-md-3">
      <div class="info-img">
        <img src="/sites/all/themes/models/images/whyhbm.jpg" class="img-responsive" title="Why HBM info image"/>
      </div>
      <div class="info-surround">
        <h2>Why Hair and Beauty Models?</h2>
        <p>Hair and Beauty Models <strong>#HBM</strong> is here to help hair dressers and beauticians, trainees or professionals connect with reliable last minute models for assessments, client work or offers. Interested in joining? <a href="/user/register" class="a-link">Sign up</a> now! It's <strong>free!</strong></p>
      </div>
    </div>
    <div class="col-md-3">
      <div class="info-img">
        <img src="/sites/all/themes/models/images/but.jpg" class="img-responsive" title="But I'm not a .. info image"/>
      </div>
      <div class="info-surround">
        <h2>But I'm not a hair dresser or beautician?</h2>
        <p>We've got you covered! <a href="/user/register" class="a-link">Sign up</a> as a Last Minute Model, search the available jobs and request a treatment. Nothing you fancy, but looking for a job? Post a <strong>last minute model</strong> job and let the professionals come to you!</p>
      </div>
    </div>
    <div class="col-md-3">
      <div class="info-img">
        <img src="/sites/all/themes/models/images/noshow.jpg" class="img-responsive" title="No more no shows! info image"/>
      </div>
      <div class="info-surround">
        <h2>No more no shows!</h2>
        <p>At HBM we understand your frustration when a client doesn't show up.  With HBM you can <strong>leave feedback</strong> and <strong>give a 5 star rating</strong> against the client and owner, to enable more informed selections on future jobs.</p>
      </div>
    </div>
    <div class="col-md-3">
      <div class="info-img">
        <img src="/sites/all/themes/models/images/what.jpg" class="img-responsive" title="what about my business. info image"/>
      </div>
      <div class="info-surround">
        <h2>What about my business?</h2>
        <p>It's <strong>free</strong> to sign up - so create your profile and link to your website for more traffic. Have a special offer coming up? Post a quick job and get your business out there!</p>
      </div>
    </div>
  </div>

    <div id="what-we-offer" class="clearfix container">
      <h3 class="text-center hd-pink">What we offer..</h3>
      <div class="row">
      <div class="col-md-4">
        <div class="what-block">
          <h3>Create up to 5 HBM active jobs</h3>
         <!--  <div class="search-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/search-example.png" alt="Search for jobs" title="Search for jobs"/>
          </div> -->
        </div>
      </div>
      <div class="col-md-4">
        <div class="what-block">
          <h3>Use our search to find clients and jobs</h3>
          <!-- <div class="manage-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/manage-clients-example.png" alt="Manage clients" title="Manage clients"/>
          </div> -->
        </div>
      </div>
      <div class="col-md-4">
        <div class="what-block">
          <h3>Manage your clients and job offers</h3>
          <!-- <div class="manage-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/feedback-example.png" alt="Leave feedback and ratings" title="Leave feedback and ratings"/>
          </div> -->
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-md-4">
        <div class="what-block">
          <h3>Create a profile and link to your business</h3>
         <!--  <div class="search-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/search-example.png" alt="Search for jobs" title="Search for jobs"/>
          </div> -->
        </div>
      </div>
      <div class="col-md-4">
        <div class="what-block">
          <h3>Feeling inspired? Write a blog post for us too</h3>
          <!-- <div class="manage-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/manage-clients-example.png" alt="Manage clients" title="Manage clients"/>
          </div> -->
        </div>
      </div>
      <div class="col-md-4">
        <div class="what-block">
          <h3>More coming soon...</h3>
          <!-- <div class="manage-img">
            <img class="img-responsive" src="/sites/all/themes/models/images/feedback-example.png" alt="Leave feedback and ratings" title="Leave feedback and ratings"/>
          </div> -->
        </div>
      </div>
    </div>
  </div>

  <div id="look-and-feel" class="clearfix">
    <div class="lhs pull-left">
      <div class="what-block">
        <h3 class="text-center hd-pink">Mobile Friendly</h3>
        <p>Hair and Beauty Models has been optimised for mobile to allow you to access your jobs, requests and offers in the most efficient way. What are you waiting for? Check it out on mobile <a href="/user/register" class="a-link">Sign up</a> now!</p>
      </div>
    </div>
    <div class="rhs pull-right">
      <div class="what-block">
        <div class="mobile">
          <img src="/sites/all/themes/models/images/mobile-view.png" class="img-responsive"/>
        </div>
      </div>
    </div>
  </div>

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

