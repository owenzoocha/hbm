(function ($) {

  var eq_nav = {
    init: function(context) {
      eq_nav.collapseNav();

      $(window).resize(function(e) {
        if(e.target === window) {
          return eq_nav.resizeNav();
        }
      });

      eq_nav.resizeNav();

    },
    resizeNav : function() {
      $('.eq-nav-body').css({
        height: $(window).height() - $('.eq-nav-body').offset().top - 40,
      });
    },
    collapseNav : function() {
      $('.event-nav-collapse').on('click', function(){
        if ($('body').hasClass('show-event-menu-static')) {
          $('body').removeClass('hide-event-menu show-event-menu-static');
          $('.eq-nav-footer span').removeClass('fa-long-arrow-right').addClass('fa-long-arrow-left');
        } else {
          $('body').addClass('hide-event-menu show-event-menu-static');
          $('.eq-nav-footer span').addClass('fa-long-arrow-right').removeClass('fa-long-arrow-left');
        }
      });
      $('.col-sm-3 .region').mouseover(function(){
        if ( $('body').hasClass('hide-event-menu') ) {
          console.log('has hide menu');
          $('body').removeClass('hide-event-menu');
        }
      });
      $('.col-sm-3 .region').mouseleave(function(){
        if ( $('body').hasClass('show-event-menu-static') ) {
          $('body').addClass('hide-event-menu');
        }
      });
    }
  }

  Drupal.behaviors.eq_nav = {
    attach: function(context) {
      $('body', context).once(function () {
        eq_nav.init();
      });
    }
  };

})(jQuery);
