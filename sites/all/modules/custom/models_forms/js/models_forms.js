(function ($) {

  var hbmf = {
    nanobar : false,

    init: function(context) {
      var options = {
        bg: '#172A3A',
        id: 'mynano'
      };
      hbmf.nanobar = new Nanobar( options );
      hbmf.formSubmit();

      $( document ).ajaxStop(function() {
        var amt = $('.set-date').length;
        if (amt > 0) {
          $('.set-date input').combodate({
            smartDays: true,
            firstItem: 'name',
            minYear: moment().format('YYYY'),
            maxYear: moment().add(1, 'Year').format('YYYY')
          });
        }
      });

      $('.set-date input').combodate({
        smartDays: true,
        firstItem: 'name',
        minYear: moment().format('YYYY'),
        maxYear: moment().add(1, 'Year').format('YYYY')
      });

      // $('#hb-costing').priceFormat({
      //     prefix: '$',
      //     thousandsSeparator: ''
      // });

      $('#personal-add-date a').on('click', function(){
        $('#date-wrapper-ajax').show();
        $('#personal-add-date').hide();
        return false;
      });

      // var dateInput = $("#edit-date");
      // dateInput.parent().css("position", "relative");

      // var dd = moment("31/05/2016 09:00", "DD/MM/YYYY HH:mm");
      // var dd2 = "31/05/2016 09:00";
      // dateInput.datetimepicker({
      //   format: 'DD/MM/YYYY HH:mm',
      //   defaultDate: dd,
      //   minDate: moment(),
      //   maxDate: moment().add(1, 'year'),
      // });
      // dateInput.data("DateTimePicker").defaultDate("31/05/2016 09:00")

      if (!Drupal.settings.form_type) {
        hbmf.formSelectType();
        hbmf.formSelectHairType();
        hbmf.formSelectBeautyType();
        hbmf.formExtraInfo();
        hbmf.clickScrolls();
        hbmf.formAddressInfo();

        $('#edit-location-country').attr('disabled', 'disabled');
        // $("#edit-location-administrative-area, #edit-location-country").chosen();

        if (!$('.has-error').length) {
          $('#hbf-field_hb_ht, #hbf-field_hb_bt, .hide-hair, .hide-beauty, #step-address-continue, #after-location, #step-extra, #step-extra-btn').hide();
        } else {
          $('.hide-hair, .hide-beauty').hide();
          var jobType = $('#edit-hbf-field-hb-type option:selected').val();
          if (jobType == 'hair') {
            $('.hide-hair').show();
          }
          if (jobType == 'beauty') {
            $('.hide-beauty').show();
          }
        }
      } else {
        $('.hbm-choose-type, #step-extra-btn').hide();
        $('#models-forms-create-form #edit-wrapper').show();
        hbmf.showTypeSelected(Drupal.settings.form_type, true);
      }

      // $('.btn').on('click', function () {
      //   var $btn = $(this).button('loading');
      //   setTimeout(function(){
      //     $btn.button('reset');
      //   }, 500);
      // })
    },

    showTypeSelected : function(type, edit) {
      if (typeof(edit)==='undefined') edit = false;
      $('.hide-beauty, .hide-hair').hide();
      $('.form-item-field-hb-gender').show();
      hbmf.nanobar.go(100);
      $('#hbf_field_hb_type').val(type);
      if (type == 'hair') {
        var s = edit ? 'Edit your hair job below.' : 'Hi there! You are posting a hair job - please fill in the form below to continue..';
        $('#form-intro').removeClass('type-b type-p').addClass('type-h').html(s);
        $('#personal-add-date').hide();
        $('#date-wrapper-ajax').show();

        hbmf.formSelectHairTypeOnEdit();
        hbmf.formSelectHairType();

        setTimeout(function(){
          $('#hbf-field_hb_ht').fadeIn();
        }, 500);
      }
      if (type == 'beauty') {
        var s = edit ? 'Edit your beauty job below.' : 'Hey! You are posting a beauty job - please fill in the form below to continue..';
        $('#form-intro').removeClass('type-h type-p').addClass('type-b').html(s);
        $('#personal-add-date').hide();
        $('#date-wrapper-ajax').show();
        hbmf.formSelectBeautyTypeOnEdit();
        hbmf.formSelectBeautyType();

        setTimeout(function(){
          $('#hbf-field_hb_bt').fadeIn();
        }, 500);
      }
      if (type == 'personal') {
        var s = edit ? 'Edit your personal job below.' : 'Let\'s get started! You are posting about a personal job, fill in the form below to become a last minute model..';

        // // Labels..
        // 'Hair treatments I will model..'
        // 'Beauty treatments I will model..'
        // 'Give us some information about what you\'re willing to model...'
        // 2. Description (What are you looking for)
        // 3. Cost and Dates (How much you're willing to pay / when are you free?)
        if (!edit) {
          $('#personal-add-date').show();
          $('#date-wrapper-ajax').hide();
        }
        $('#form-intro').removeClass('type-b type-h').addClass('type-p').html(s);
        $('.form-item-field-hb-gender').show();
        setTimeout(function(){
          $('#hbf-field_hb_ht, #hbf-field_hb_bt').fadeIn();
        }, 500);
      }
    },

    formSelectType : function() {

      $('.hbm-choose-type .choice-box .choice-type').on('click', function(){
        $('.hbm-choose-type .choice-box .choice-type').addClass('inactive');
        $(this).removeClass('inactive').addClass('active');
        $('#models-forms-create-form #edit-wrapper').show();
        $('#edit-hbf-field-hb-type').val($(this).data('hb_type'));
        hbmf.showTypeSelected($(this).data('hb_type'));
      });

      $('#edit-hbf-field-hb-type').change(function() {
        hbmf.showTypeSelected($(this).find('option:selected').val());
        // if ( $(this).find('option:selected').val() == 'hair' ) {
        //   setTimeout(function(){
        //     $('#hbf-field_hb_ht').fadeIn();
        //   }, 500);
        // }
        // if ( $(this).find('option:selected').val() == 'beauty' ) {
        //   setTimeout(function(){
        //     $('#hbf-field_hb_bt').fadeIn();
        //   }, 500);
        // }
        if ( !$(this).find('option:selected').val() ) {
          $('#hbf-field_hb_ht, #hbf-field_hb_bt').hide();
        }
      });

    },

    formSelectHairType : function() {
      $('#edit-hbf-field-hb-ht').change(function() {
        hbmf.nanobar.go(100);

        if (!Drupal.settings.form_type) {
          setTimeout(function(){
            $('#step-extra-btn').fadeIn();
          }, 1000);
        }

        $.each($(this).find('option:selected'), function(i, v){
          if ($(this).val() == 'Colour') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_ht_colour').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Cut') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_ht_cut').fadeIn();
            }, 500);
          }
        });
      });
    },


    formSelectHairTypeOnEdit : function() {
      $.each($('#edit-hbf-field-hb-ht').find('option:selected'), function(i, v){
        if ($(this).val() == 'Colour') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_ht_colour').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Cut') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_ht_cut').fadeIn();
          }, 500);
        }
      });
    },

    formSelectBeautyType : function() {
      $('#edit-hbf-field-hb-bt').change(function() {
        hbmf.nanobar.go(100);

        // console.log();
        if (!Drupal.settings.form_type) {
          setTimeout(function(){
            $('#step-extra-btn').fadeIn();
          }, 500);
        }

        $.each($(this).find('option:selected'), function(i, v){
          if ($(this).val() == 'Make Up') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_makeup').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Eyelashes') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_eyelashes').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Eyebrows') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_eyebrows').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Nails') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_nails').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Hair Removal') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_waxing').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Facial') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_facials').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Massage') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_massage').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Tanning') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_tanning').fadeIn();
            }, 500);
          }
        });
      });
    },

    formSelectBeautyTypeOnEdit : function() {
      $.each($('#edit-hbf-field-hb-bt').find('option:selected'), function(i, v){
        if ($(this).val() == 'Make Up') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_makeup').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Eyelashes') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_eyelashes').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Eyebrows') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_eyebrows').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Nails') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_nails').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Hair Removal') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_waxing').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Facial') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_facials').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Massage') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_massage').fadeIn();
          }, 500);
        }
        if ($(this).val() == 'Tanning') {
          $('.hide-me').hide();
          setTimeout(function(){
            $('#hbf-field_hb_bt_tanning').fadeIn();
          }, 500);
        }
      });
    },

    clickScrolls : function(){
      $('#edit-title').on('click', function(){
        var top = $('#edit-wrapper').offset().top;
        $('html, body').animate({ scrollTop: top }, 500);
      });

      $('.hbm-choose-type .choice-box .choice-type').on('click', function(){
        var top = $('#block-system-main').offset().top;
        $('html, body').animate({ scrollTop: top - 20 }, 500);
      });
    },

    formExtraInfo : function(){
      $('#step-extra-btn').on('click', function(){
        hbmf.nanobar.go(100);
        setTimeout(function(){
          $('#step-extra').slideDown();
          var top = $('#step-extra-btn').offset().top;
          $('html, body').animate({ scrollTop: top }, 400);
        }, 200);
      });
    },

    formAddressInfo : function(){
      setInterval(function() {
        if ($('input#edit-location-thoroughfare').val() != '') {
          $('#after-location').fadeIn();
          // console.log('yee');
        }
        else {
          $('#after-location').fadeOut();
          // console.log('noo');
        }
      }, 100);
    },

    formSubmit : function(){
      $('#models-forms-create-form').submit(function(){
        hbmf.nanobar.go(30);
        setTimeout(function(){
          hbmf.nanobar.go(100);
          // setTimeout(function(){
          //   hbmf.nanobar.go(100);
          // }, 200);
        }, 1000);
      });
    }
  }

  Drupal.behaviors.hbmf = {
    attach: function(context) {
      $('body', context).once(function () {
        hbmf.init();
      });
    }
  };

})(jQuery);
