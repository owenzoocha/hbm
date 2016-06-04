(function ($) {

  var models_imgs = {
    init: function(context) {
      $('.job-slicks').slick({
        dots: true,
        infinite: true,
        speed: 500,
        // slidesToShow: 2,
        // slidesToScroll: 2,
        cssEase: 'linear',
        customPaging : function(slider, i) {
          // console.log( $(slider.$slides[i]).html() );
          var thumb = $(slider.$slides[i]).attr('src');
          return  $(slider.$slides[i]).html();
        },
      });
    },
  }

  Drupal.behaviors.models_imgs = {
    attach: function(context) {
      $('body', context).once(function () {
        models_imgs.init();
      });
    }
  };

})(jQuery);
