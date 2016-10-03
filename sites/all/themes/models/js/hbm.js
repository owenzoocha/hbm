(function ($) {

  var hbm = {
    lat : false,
    lng : false,

    init: function(context) {
      if ($('.page-search').length) {
        // hbm.scrollAnimations();
        // var h2 = $('.main-container').outerHeight(true) + $('#hb-header').outerHeight(true);
        // $('.page-search .col-sm-3 .well').height(h2);
      } else {
        // hbm.scrollAnimationsMenu();
      }
      hbm.searchHighlight();
      // hbm.skrollr();
      hbm.hbRaty();
      hbm.loginFormHacks();
      hbm.hbmMenu();
      hbm.watchlist();
      hbm.reorder();
      hbm.selectClient();
      hbm.expandFilters();
      hbm.mobileChecks();
      hbm.fadeOutAlertsOnHome();
      hbm.hacks();
      hbm.moreInformation();

      $('table').addClass('table-bordered');
      $('.page-messages .btn-xs').removeClass('btn-xs');

      $('.nav-2 a').on('click', function(){
        // return false;
      });

      if ($('.about-cut').length) {
        $('.about-cut .readmore').on('click', function(){
          $(this).closest('.extend-this').find('.about-cut').addClass('hidden');
          $(this).closest('.extend-this').find('.about-normal').removeClass('hidden');
          return false;
        })
      }

      if ($('#dz-submit').length) {
        var dest = Drupal.settings.photo_nid ? '?nid=' + Drupal.settings.photo_nid : '?uid=loggedin';
        Dropzone.autoDiscover = false;
        var myDropzone = new Dropzone("#dz", {
          url: '/file-dz-upload' + dest,
          dictDefaultMessage: "Drop your photos here to upload (or click to search)",
          dictFallbackMessage: "Your browser doesn't support drag n' drop uploads - please upgrade to the latest version of your browser! Or contact us for help :)",
          paramName: "files", // The name that will be used to transfer the file
          maxFilesize: 2, // MB
          maxFiles: 5,
          uploadMultiple: true,
          parallelUploads: 5,
          acceptedFiles: 'image/*',
          init: function() {
            this.on("addedfile", function(file) {
              // console.log("Added filesss.");
            });
           this.on("complete", function (file) {
              if (this.getUploadingFiles().length === 0 && this.getQueuedFiles().length === 0) {
                location.reload();
              }
            });
          },
          addRemoveLinks : true,
          autoProcessQueue : false,
        });

        $('#dz-submit').on('click', function(){
          myDropzone.processQueue();
          return false;
        });
      }

      setTimeout(function(){
        $('.st_fblike').fadeIn();
      }, 4000);

      if (document.location.hostname == 'models.dev') {
        $('img').error(function(){
          // $(this).attr('src', "http://cumbrianrun.co.uk/wp-content/uploads/2014/02/default-placeholder.png");
        })
      }

      // if (Drupal.settings.noty) {
      //   $.each(Drupal.settings.noty, function(i, v){
      //     var n = noty({
      //       layout: v['pos'] ? v['pos'] : 'bottomLeft',
      //       text: v['msg'],
      //       theme : 'relax',
      //       // template: '<div class="noty_message"><span class="noty_text"></span><div class="noty_close"></div></div>',
      //       type : v['type'],
      //       timeout : v['timer'] ? v['timer'] : 5000,
      //       maxVisible: 5,
      //       button: true,
      //       closeWith: ['button', 'click'],
      //       animation: {
      //         open: 'animated fadeInUp', // Animate.css class names
      //         close: 'animated fadeOutDown', // Animate.css class names
      //         easing: 'swing', // unavailable - no need
      //         speed: 500 // opening & closing animation speed
      //       }
      //     });
      //   });
      // }
    },

    // Location stuff....
    moreInformation: function () {
      $('.quick-view').on('click', function () {
        var nid = $(this).data('nid');
        $('#node-' + nid).closest('.views-field-rendered-entity').toggleClass('active');
        if ($('#node-' + nid).closest('.views-field-rendered-entity').hasClass('active')) {
          $(this).find('.fa').removeClass('fa-caret-down').addClass('fa-times');
        }
        else {
          $(this).find('.fa').removeClass('fa-times').addClass('fa-caret-down');
        }
        return false;
      });
    },

    hacks : function(){
      if ($('.view-header .btn-group a').length) {
        url = window.location.href;
        var url = url.substr(url.indexOf('/my-jobs'), url.length);
        console.log(url);
        $('.view-header .btn-group a').removeClass('active');
        $('.view-header .btn-group a').each(function(i, v){
          if (url == '/my-jobs') {
            $(this).addClass('active');
            return false;
          }
          var thisUrl = $(this).attr('href');
          if (url == thisUrl) {
            $(this).addClass('active');
            return false;
          }
        });
        $('.view-header .btn-group').css('visibility', 'visible');
      }
    },

    mobileChecks : function(){
      if (!!navigator.platform && /iPad|iPhone|iPod/.test(navigator.platform)) {
        $('select').addClass('ios-select'); // provide a class for iOS select box
      }
    },

    fadeOutAlertsOnHome : function(){
      if ($('body.front .alert-success').length ){
        setTimeout(function(){
          $('body.front .alert-success').addClass('alert-cya');
          setTimeout(function(){
            $('body.front .alert-success').remove();
          }, 2000);
        }, 8000);
      };
    },

    expandFilters : function(){
      $('#block-block-7 button').on('click', function(){
        $('body').toggleClass('show-filters');
        $('body, html').toggleClass('no-scroll');
      });
    },

    selectClient : function(){
      if ($('.page-job-clients').length) {
        $('.page-job-clients .option a').on('click', function(){
          if ($(this).closest('.views-row').find('.views-field-nothing-2 a').data('feedback') != 1) {
            if ($(this).closest('.views-row').hasClass('active')) {
              $(this).closest('.views-row').removeClass('active');
              $(this).html('Client Select');
            } else {
              $(this).closest('.views-row').addClass('active');
              $(this).html('<i class="fa fa-times"></i> Selected');
            }
            hbm.confirmClient();
          }
          return false;
        });
      }
      if ($('.page-job-clients .views-field-nothing-2 a[data-selected="1"]').length) {
        $.each($('.page-job-clients .views-field-nothing-2 a[data-selected="1"]'), function(i, v) {
          $(this).closest('.views-row').addClass('active');
          if ($(this).closest('.views-row').find('.views-field-nothing-2 a').data('feedback') != 1) {
            $(this).closest('.views-row').find('.option a').html('<i class="fa fa-times"></i> Selected');
          } else {
            $(this).closest('.views-row').find('.option a').html('<i class="fa fa-check"></i> Feedback Given');
          }
        });
        hbm.confirmClient();
      }
    },

    confirmClient : function(){
      if ($('.page-job-clients .views-row.active').length) {
        $('#selected-clients, #selected-clients-popup').html('');
        $('#clients_hidden').val('');
        $('#block-block-6 button').attr('disabled', false);
        var eids = '';
        $.each($('.page-job-clients .views-row.active'), function(i, v) {
          $('#selected-clients, #selected-clients-popup').append('<li>' + $(this).find('.views-field-name .field-content').html() + '</li>')
          eids += $(this).find('.views-field-nothing-2 a').data('eid') + ',';
        });
        $('#clients_hidden').val(eids);
      } else {
        $('#block-block-6 button').attr('disabled', true);
        $('#selected-clients, #selected-clients-popup').html('');
        $('#clients_hidden').val('');
      }
    },

    skrollr : function(){
      if ($(window).width() > 440) {

        var owen = document.getElementById('owen');

        // init controller
        // var controller = new ScrollMagic.Controller();

        // Create Animation for 0.5s
        var myTimeline = new TimelineMax({
          // repeat: 0
        });

        // myTimeline
        //   .to('#page-header-bg', 1, {y: -100, ease: Linear.easeNone});

        // build scenes
        // var scene = new ScrollMagic.Scene({triggerElement: "#page-header-bg", offset: 40})
        //   .setTween(myTimeline)
        //   .addIndicators()
        //   .addTo(controller);
      }
    },

    reorder : function(){
      if ( $('#block-views-eck-pics-block-1').length || $('#block-views-eck-pics-user-block').length) {
        $('.views-row-first').addClass('active');
        $('.img-responsive').on('click', function(){
          $('.views-row.active').removeClass('active');
          $(this).closest('.views-row').addClass('active');
          var ops = {'option': 'update', 'id': $(this).closest('.views-row').find('.fa-close').data('eid'), 'nid': $(this).closest('.views-row').find('.fa-close').data('nid') ? $(this).closest('.views-row').find('.fa-close').data('nid') : 'user'}
          $.ajax({
            url : '/pic-updates',
            type : 'POST',
            data : {'pic' : JSON.stringify(ops)},
            success : function(data) {
              location.reload();
            },
          });

          return false;
        });

        $('.views-field-nothing .fa').on('click', function(){
          $(this).closest('.views-row').hide().addClass('removed');

          var ops = {'option': 'delete', 'id': $(this).closest('.views-row').find('.fa-close').data('eid') }
          $.ajax({
            url : '/pic-updates',
            type : 'POST',
            data : {'pic' : JSON.stringify(ops)},
            success : function(data) {
              console.log(data);
            },
          });

          return false;
        });
      }
    },

    // Location stuff....
    searchHighlight : function() {
      $('#edit-search').on('focusin', function(){
        $(this).closest('.search-surround').addClass('search-surround-focus');
      });
      $('#edit-search').on('focusout', function(){
        $(this).closest('.search-surround').removeClass('search-surround-focus');
      });
    },

    hbRaty : function() {
      $('.raty-readonly').raty({
        starOff   : 'fa fa-fw fa-star star-dark-grey', // this is awesome.
        hints : ['Easy!', 'It\'s OK', 'It\'ll be fine!', 'Pretty tricky!', 'HARD!'],
        readOnly: function() {
          return true;
        },
        score: function() {
          return $(this).attr('data-rating');
        }
      });
      if ($('.raty-feedback').length) {
        $('.raty-feedback').raty({
          starOff   : 'fa fa-fw fa-star star-dark-grey', // this is awesome.
          hints : ['Easy!', 'It\'s OK', 'It\'ll be fine!', 'Pretty tricky!', 'HARD!'],
          cancel: true,
          click: function(score, evt) {
            var id = $(this).closest('.raty-feedback').data('uid');
            $('#star-uid-' + id).val(score);
          },
          readOnly: function() {
            if( $(this).attr('data-rating') ) {
              return true;
            }
          },
          score: function() {
            if( $(this).attr('data-rating') ) {
              return $(this).attr('data-rating');
            }
          }
        });
      }
    },

    scrollAnimations : function() {
      // init controller
      if ($(window).width() > 440) {
        if (!$('body.front').length) {

          var controller = new ScrollMagic.Controller();
          var topH = $('#navbar').offset().top;
          // Build scenes.
          new ScrollMagic.Scene({offset: topH})
          // new ScrollMagic.Scene({triggerElement: "#navbar-top-top", offset: 50})
            // .on('leave', function(){
            //   console.log('left!');
            // })
            .setClassToggle("body", "nav-animate") // add class toggle
            // .setPin(".col-sm-3")
            // .addIndicators() // add indicators (requires plugin)
            .addTo(controller);
        }
      }
    },

    scrollAnimationsMenu : function() {
      // init controller
      if ($(window).width() > 440) {
        if (!$('body.front').length) {
          var controller = new ScrollMagic.Controller();
          var topH = $('#navbar').offset().top;
          // Build scenes.
          new ScrollMagic.Scene({offset: topH})
          // new ScrollMagic.Scene({triggerElement: "#navbar-top-top", offset: 50})
            // .on('leave', function(){
            //   console.log('left!');
            // })
            .setClassToggle("body", "nav-animate") // add class toggle
            // .addIndicators() // add indicators (requires plugin)
            .addTo(controller);
        }
      }
    },

    loginFormHacks : function() {
      if ( $('.not-logged-in').length ) {
        $('.not-logged-in .form-item .col-md-4').removeClass('col-md-4');
      }
    },

    hbmMenu : function() {
      $('.a-dd > a').mouseover(function() {
        if (!$(this).parent().hasClass('show-dd')) {
          $(this).parent().addClass('active show-dd');
        }
      });
      $('.my-menu-dd, .a-dd').mouseleave(function() {
        $('.a-dd').removeClass('active show-dd');
      });

      // $('.burger-menu button').on('click', function() {
      //   if(!$('#navbar').hasClass('show-mobile')){
      //     window.scrollTo(0, 0);
      //     $('#navbar').addClass('show-mobile');
      //     $('.main-container').addClass('show-mobile-body');
      //   } else {
      //     $('#navbar').removeClass('show-mobile');
      //     $('.main-container').removeClass('show-mobile-body');
      //   }
      // });
    },

    watchlist : function() {
      if ($('.hb-like').length) {
        $('.hb-like').on('click', function(){
          var watchlist = {'option': $(this).hasClass('hb-like-active') ? 'delete' : 'add', 'id': $(this).data('jid') }
          $this = $(this);
          if ($this.hasClass('hb-like-active')) {
            $this.removeClass('hb-like-active');
          } else {
            $this.addClass('hb-like-active');
          }
          $.ajax({
            url : '/watchlist-updater',
            type : 'POST',
            data : {'watchlist' : JSON.stringify(watchlist)},
            success : function(data) {
              console.log(data);
            },
          });
          return false;
        });
      }
    }
  }

  Drupal.behaviors.hbm = {
    attach: function(context) {
      $('body', context).once(function () {
        hbm.init();
      });
    }
  };

})(jQuery);
