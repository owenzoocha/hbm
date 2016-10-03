/**
 * Created by owenwilliams on 15/08/2016.
 */
(function ($) {

  var models_searcher = {

    init: function (context) {

      var $input = $('#search-lookup');
      var data = JSON.parse(Drupal.settings.geos);
      $input.typeahead(
        {
          source: data,
          fitToElement: true,
          autoSelect: false
        });

      $input.change(function () {
        var current = $input.typeahead("getActive");
        if (current) {
          // Some item from your model is active!
          if (current.name.toLowerCase() == $input.val().toLowerCase()) {
            models_searcher.searcher(current);
            // This means the exact match is found. Use toLowerCase() if you want case insensitive match.
          }
          else {
            // This means it is only a partial match, you can either add a new item
            // or take the active if you don't want new items
          }
        }
        else {
          // Nothing is active so it is a new value (or maybe empty value)
        }
      });

      $('#models-searcher-form').submit(function () {
        var geo = $input.typeahead("getActive");
        if (geo) {
          models_searcher.searcher(geo);
        }
        return false;
      });

    },

    searcher: function (geo) {
      var srch = 'http://models.dev/search?field_hb_geofield_latlon_op=10&field_hb_geofield_latlon=' + geo['suburb'] + '&search=&field_hb_geofield_latlon_lat=' + geo['latitude'] + '&field_hb_geofield_latlon_lng=' + geo['longitude'] + '&sort=field_hb_geofield%3Alatlon&order=asc';
      window.location.href = srch;
    }

  }

  Drupal.behaviors.models_searcher = {
    attach: function (context) {
      $('body', context).once(function () {
        models_searcher.init();
      });
    }
  };

})(jQuery);
