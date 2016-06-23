(function ($) {

  var models_nav = {
    init: function(context) {
      $('#block-views-user-profile-jobs-block .view-content, #block-views-user-profile-jobs-block-1 .view-content, #block-views-user-profile-jobs-block-2 .view-content, .slick-me-up .view-content').slick({
        dots: true,
        infinite: true,
        speed: 500,
        slidesToShow: 4,
        slidesToScroll: 4,
         responsive: [
          {
            breakpoint: 1024,
            settings: {
              slidesToShow: 4,
              slidesToScroll: 4,
              infinite: true,
              dots: true
            }
          },
          {
            breakpoint: 992,
            settings: {
              slidesToShow: 3,
              slidesToScroll: 3
            }
          },
          {
            breakpoint: 500,
            settings: {
              slidesToShow: 2,
              slidesToScroll: 2
            }
          },
          {
            breakpoint: 330,
            settings: {
              slidesToShow: 1,
              slidesToScroll: 1
            }
          }
          // You can unslick at a given breakpoint now by adding:
          // settings: "unslick"
          // instead of a settings object
        ]
      });

      if ($('.views-field-field-geofield-distance').length) {
        $('.views-row').each(function(i, v){
          $this = $(this);
          var dist = $this.find('.views-field-field-geofield-distance .field-content').html();
          if (dist) {
            $this.find('.hb-location').append( '</br><span class="hb-dist">(' + Math.round(parseFloat(dist) * 100) / 100 + ' km from you)</span>');
          } else {
            return;
          }
        });
      }
    }
  }

  Drupal.behaviors.models_nav = {
    attach: function(context) {
      $('body', context).once(function () {
        models_nav.init();
      });
    }
  };

})(jQuery);
