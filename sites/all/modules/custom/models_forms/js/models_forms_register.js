(function ($) {

  var hbmfreg = {

    init: function(context) {
      hbmfreg.setType();
    },

    setType : function() {
      $('#edit-field-i-am-a-und').change(function() {
        $('.field-name-field-my-college, .field-name-field-my-company').hide();
        if ( $(this).find('option:selected').val() == 'study' ) {
          $('.field-name-field-my-college').show();
        } else if ($(this).find('option:selected').val() == 'employed') {
          $('.field-name-field-my-company').show();
        }
      });
    }
  }

  Drupal.behaviors.hbmfreg = {
    attach: function(context) {
      $('body', context).once(function () {
        hbmfreg.init();
      });
    }
  };

})(jQuery);
