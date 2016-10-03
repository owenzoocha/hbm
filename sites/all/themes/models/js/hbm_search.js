(function ($) {

  var hbm_search = {
    lat: false,
    lng: false,

    init: function (context) {
      // hbm_search.masonryLayout();
      hbm_search.facetsDropDown();
      hbm_search.submitHack();
      hbm_search.getLocation();
      hbm_search.setDistance();
      // hbm_search.moreInformation();
    },

    // Location stuff....
    moreInformation: function () {
      $('.quick-view').on('click', function () {
        var nid = $(this).data('nid');
        console.log(nid);
        $('#node-' + nid).closest('.views-field-rendered-entity').toggleClass('active');
        console.log($('#node-' + nid).closest('.views-field-rendered-entity'));
        if ($('#node-' + nid).closest('.views-field-rendered-entity').hasClass('active')) {
          $(this).find('.fa').removeClass('fa-caret-down').addClass('fa-times');
        }
        else {
          $(this).find('.fa').removeClass('fa-times').addClass('fa-caret-down');
        }
        return false;
      });
    },

    // Location stuff....
    setDistance: function () {
      // $('.views-field-field-hb-geofield-latlon').hide();
      $('.views-row').each(function (i, v) {
        $this = $(this);
        var dist = $this.find('.views-field-field-hb-geofield-latlon .field-content').html();
        if (dist) {
          $this.find('.hb-location').append(' <span class="hb-dist">(' + Math.round(parseFloat(dist) * 100) / 100 + ' km away)</span>');
        }
        else {
          return;
        }
      });
    },

    // Location stuff....
    resizeNav: function () {
      $('.page-search .col-sm-3').css({
        height: $(window).height() - $('.page-search .col-sm-3').offset().top - 40,
      });
    },

    // submit hack stuff....
    submitHack: function () {
      // $('#views-exposed-form-s-page').submit(function(){
      //   $('#edit-field-hb-geofield-latlon').val( $('#edit-field-hb-geofield-latlon-1').val() );
      // });
    },

    // h2 clicks to expose more.....
    facetsDropDown: function () {
      $('.block-facetapi h2, #block-views-exp-job-search-page h2').on('click', function () {
        if (!$(this).closest('.block-dd').hasClass('active')) {
          $(this).closest('.block-dd').addClass('active');
          // $('.col-sm-3').scrollTop( 300 );
        }
        else {
          $(this).closest('.block-dd').removeClass('active');
        }
      });
    },

    // Masonry....
    masonryLayout: function () {
      // $('.region-content').append('<div class="loader"></div>');
      $('.view-job-search .view-content').imagesLoaded(function () {

        var $grid = $('.view-job-search .view-content').masonry({
          // disable initial layout.
          initLayout: false,
          itemSelector: '.views-field-rendered-entity',
          percentPosition: true,
          transitionDuration: 300
        });

        // bind event.
        $grid.masonry('on', 'layoutComplete', function () {
          $('.region-content .loader').remove();
          $('.views-row').each(function (i, v) {
            $this = $(this);
            var dist = $this.find('.views-field-field-hb-geofield-latlon .field-content').html();
            if (dist) {
              $this.find('.hb-location').append(' <span class="hb-dist">(' + Math.round(parseFloat(dist) * 100) / 100 + ' km away)</span>');
            }
            else {
              return;
            }
          });
        });

        // trigger initial layout.
        $grid.masonry();
      });
    },

    // Location stuff....
    getLocation: function () {
      if (navigator.geolocation) {
        // navigator.geolocation.getCurrentPosition(hbm_search.locationSuccess);
      }
    },

    locationSuccess: function (position) {
      hbm_search.lat = position.coords.latitude;
      hbm_search.lng = position.coords.longitude;

      // $('#edit-field-hb-geofield-latlon').val(hbm_search.lat + ' ' + hbm_search.lng);
      // console.log(hbm_search.lat + ' ' + hbm_search.lng);
    }
  }

  Drupal.behaviors.hbm_search = {
    attach: function (context) {
      $('body', context).once(function () {
        hbm_search.init();
      });
    }
  };

})(jQuery);
