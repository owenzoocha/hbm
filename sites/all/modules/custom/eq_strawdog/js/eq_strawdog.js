(function ($) {

  var eq_strawdog = {
    el : '',
    dropped : 0,
    pause : 0,
    overRide : 0,
    currentRow : 1,

    init: function() {
      eq_strawdog.setClock();
      eq_strawdog.setClockFunctions();
      eq_strawdog.build();
      eq_strawdog.contextMenus();
    },

    contextMenus : function() {
      $.contextMenu({
        selector: '.key-blocks',
        callback: function(key, options) {
          eq_strawdog.blockClick(key, options);
        },
        items: {
          "edit": {name: "Edit", icon: "edit"},
          "split": {name: "Split", icon: "cut"},
         // copy: {name: "Copy", icon: "copy"},
          // "paste": {name: "Paste", icon: "paste"},
          "delete": {name: "Delete", icon: "delete"},
          "sep1": "---------",
          "quit": {name: "Quit", icon: function(){
            return 'context-menu-icon context-menu-icon-quit';
          }}
        }
      });

      $.contextMenu({
        selector: '.sd-padded, .sd-number',
        callback: function(key, options) {
          eq_strawdog.rowClick(key, options);
        },
        items: {
          "edit": {name: "Edit", icon: "edit"},
         // copy: {name: "Copy", icon: "copy"},
          // "paste": {name: "Paste", icon: "paste"},
          "delete": {name: "Delete", icon: "delete"},
          "sep1": "---------",
          "quit": {name: "Quit", icon: function(){
            return 'context-menu-icon context-menu-icon-quit';
          }}
        }
      });
    },
    updateClockDetails : function(id) {
      var timeBlock = $('#sd-row-' + (id - 1)).prev('.sd-padded');
      $('#start-time').prev('label').html('Start time: <strong>' + timeBlock.find('.finish').html() + '</strong>');
      $('#start-time').hide();
    },

    setClockFunctions : function() {
      $('#start-time input').timepicker({
        template: false,
        showInputs: false,
        minuteStep: 5,
        defaultTime: '09:00',
      });

      $("#duration-time input").TouchSpin({
        verticalbuttons: true,
        verticalupclass: 'glyphicon glyphicon-plus',
        verticaldownclass: 'glyphicon glyphicon-minus',
        step: 5,
        postfix: "minutes",
        max: 540,
        min: 0,
      });
    },

    setClock : function() {
      $('#strawdog-time').modal('show');

      // Show the commence time form and edit..
      $('#strawdog-add-time').on('click', function(){
        $('#strawdog-time').modal('show');
        return false;
      });

      // The main mods form - time etc..
      $('#strawdog-time-form').submit(function(){

        var currentRow = eq_strawdog.currentRow;
        var timeBlock = $('#sd-row-'+currentRow).prev('.sd-padded');
        var startTime;

        if (currentRow == 1) {
          startTime = moment($('#start-time input').val(), "HH:mm");
          $('#sd-row-'+currentRow).data('start', startTime.format("hh:mm A"));
          timeBlock.find('.start').html(startTime.format("hh:mm A"));
        } else {
          startTime = moment( $('#sd-row-'+ (currentRow - 1) ).data('finish'), "hh:mm A" );
        }

        var duration1 = startTime.add($('#duration-time input').val(), 'm');
        timeBlock.find('.finish').html(duration1.format("hh:mm A"));
        $('#sd-row-'+currentRow).data('finish', duration1.format("hh:mm A"));

        $('#duration-time input').val('');

        $('#strawdog-time').modal('hide');
        return false;
      });

    },

    build : function() {
      var container;

      // Process functions.
      eq_strawdog.splitUpForm();

      var drake = dragula({
        copy: function (el, source) {
          // console.log(source);
          return source === document.getElementById('strawdog-key')
        },
        accepts: function (el, target) {
          return target !== document.getElementById('strawdog-key')
        },
        removeOnSpill: true,
      });

      drake.on('drop', function (el, source) {
        eq_strawdog.setWidth(source);
        eq_strawdog.dropped = 1;
        eq_strawdog.overRide = 0;
        eq_strawdog.pause = 0;
      });
      drake.on('remove', function (el, source) {
        eq_strawdog.setWidth(source);
      });

      drake.on('over', function (el, container, source) {
        // console.log('over');
        eq_strawdog.dropped = 0;
        if($(container).attr('id') != 'strawdog-key') {
          eq_strawdog.over = $(container).attr('id');

          if( eq_strawdog.overRide == 0 ){
            if( $(container).attr('id') == $(source).attr('id')) {
              eq_strawdog.pause = 1;
            }
          }
          eq_strawdog.setTransitWidth(el, container, source);
        }
      });
      drake.on('out', function (el, container, source) {
        if(eq_strawdog.dropped != 1) {

          // console.log('out');
          eq_strawdog.overRide = 1;
          eq_strawdog.pause = 0;

          eq_strawdog.out = $(container).attr('id');
          if($(container).attr('id') != 'strawdog-key') {
            eq_strawdog.resetTransitWidth(el, container);
          }
        }
      });

      drake.containers.push(document.querySelector('#strawdog-key'), document.querySelector('#sd-row-1'), document.querySelector('#sd-2'));

      $('#strawdog-add-row').on('click', function(){
        $('#strawdog-time').modal('show');
        var id = parseInt( $('.sd-container').length + 1);
        eq_strawdog.updateClockDetails(id);
        eq_strawdog.currentRow = id;

        $('#strawdog-dropzone').append('<div class="sd-wrapper"><div class="sd-number sd-common"><span>' + id + '</span></div><div class="sd-padded sd-common"><span class="start"></span><span class="finish"></span></div><div id="sd-row-' + id + '" class="sd-container sd-common"></div></div></div>');
        drake.containers.push(document.querySelector('#sd-row-' + id));
        return false;
      });
      $('#strawdog-add-break').on('click', function(){
        var breakAmt = $('.sd-break').length;
        $('#strawdog-dropzone').append('<div id="sd-break-' + parseInt(breakAmt + 1) + '" class="sd-break"><span>BREAK</span></div>');
        return false;
      });

      $(document).on('click', '.sd-container .key-blocks', function(){
        console.log('CLICKED EVENT!!');
        return false;
      });

    },
    blockClick : function(id, ops) {
      console.log('menu clicked!')

      $el = $(ops['$trigger']);
      if(id == 'delete'){
        eq_strawdog.setWidth($el);
      }
      if(id == 'split'){
        eq_strawdog.splitUp($el);
      }
    },

    // Set width of oxes when the transit dynamically enters a container.
    setTransitWidth : function(el, destination, source) {
      var container = $(destination);
      var boxes = container.find('.key-blocks:not(.gu-transit)');
      var boxes2 = container.children();
      var currentLength;

      // If there's no current boxes in the destination, transit box is 85 %.
      if(boxes.length == 0) {
        // currentLength = $('.region-content').width(); // before padded added!
        currentLength = $('.sd-wrapper:eq(0)').width() - $('.sd-number').width() - $('.sd-padded').width() - 3; // after padded added!

        $(el).css({
          width: currentLength + 'px',
        });
      } else {
        // If there is boxes, calculate the width and update.
        if(eq_strawdog.pause == 1) {
          // console.log('do nothing.. ');
          return;
        } else {
          currentLength = ($('.sd-wrapper:eq(0)').width() - $('.sd-number').width() - $('.sd-padded').width() - 3 ) / (boxes.length + 1);

          console.log(currentLength);

        }
        container.find('.key-blocks').css({
          width: currentLength + 'px',
        });
        $(el).css({
          width: currentLength + 'px',
        });
      }
    },

    // Reset width of oxes when the transit dynamically enters a container.
    resetTransitWidth : function(el, destination) {
      var container = $(destination);
      var boxes = container.find('.key-blocks:not(.gu-transit)');
      var currentLength;
      // If there's no current boxes in the destination, transit box is 85%.
      if(boxes.length > 0) {
        // If there is boxes, calculate the width and update.
        currentLength = 85 / (boxes.length);
        container.find('.key-blocks').css({
          width: currentLength + '%',
        });
      } else {
        console.log('im not doing anything!???');
      }
    },

    // Set width of all boxes when the transit is DROPPED (or split).
    setWidth : function(source) {
      if(source instanceof jQuery) {
        var container = source.parent();
        source.remove();
        var boxes = container.children();
      } else {
        var container = $(source);
        var boxes = container.children();
      }
      var w = 85/boxes.length;
      // if (boxes.length > 2) {
      //   container.addClass('key-blocks-multiple')
      // } else {
      //   container.removeClass('key-blocks-multiple')
      // }
      $.each(boxes, function(i, v){
        $(this).css({
          width: w+'%',
        });
      });
    },
    splitUp : function(el, source) {
      $('#strawdog-splitter').modal('show');
      eq_strawdog.el = el;
    },
    splitUpForm : function() {
      $('#strawdog-splitter-form').submit(function(){
        var container = eq_strawdog.el.parent();
        var amt = $('#edit-split');
        for(i = 0; i < amt.val(); i++) {
          eq_strawdog['el'].clone().appendTo(container);
        }
        eq_strawdog.setWidth(eq_strawdog['el']);
        $('#strawdog-splitter').modal('hide');
        return false;
      });
    },

  }

  Drupal.behaviors.eq_strawdog = {
    attach: function(context) {
      $('body', context).once(function () {
        eq_strawdog.init();
      });
    }
  };

})(jQuery);
