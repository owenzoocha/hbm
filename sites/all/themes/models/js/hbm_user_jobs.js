(function ($) {

  var hbm_user_jobs = {

    init: function(context) {
      hbm_user_jobs.masonryLayout();
      // hbm_user_jobs.setStars();
    },

    // Masonry....
    masonryLayout : function() {
      // $('.region-content').append('<div class="loader"></div>');
      $('.page-my-jobs .view-content, .page-previous-jobs .view-content, .page-job-requests .view-content, .page-watchlist .view-content').imagesLoaded( function() {

        var $grid = $('.page-my-jobs .view-content, .page-previous-jobs .view-content, .page-job-requests .view-content, .page-watchlist .view-content').masonry({
          // disable initial layout.
          initLayout: false,
          itemSelector: '.views-field-rendered-entity',
          percentPosition: true,
          transitionDuration: 100,
        });

        // bind event.
        $grid.masonry( 'on', 'layoutComplete', function() {
          $('.region-content .loader').remove();
        });

        // trigger initial layout.
        $grid.masonry();

      });
    },

    // Stars stuff....
    setStars : function() {
      $('.hb-rating').raty({ score: 3, readOnly: true });
    },

  }

  Drupal.behaviors.hbm_user_jobs = {
    attach: function(context) {
      $('body', context).once(function () {
        hbm_user_jobs.init();
      });
    }
  };

})(jQuery);
