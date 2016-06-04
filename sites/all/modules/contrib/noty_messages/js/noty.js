var notyMessages = notyMessages || {};

(function($) {
  Drupal.behaviors.notyMessagesRenderMessages = {
    attach: function(context, settings) {
      // Don't deal with config here.
      for (var type in settings.notyMessagesNoties){
        // Pre construct the settings for noty.
        notyMessages.renderType(type, settings.notyMessagesNoties[type], settings.notyMessages);
      }
    }
  },
  notyMessages.renderType = function(typeName, typeData, config) {
    for (message in typeData){
      // Set the text.
      console.log('render');
      noty({
    	  layout: config.notyLayout[typeName],
          theme: config.notyTheme[typeName] + 'Theme', 
          type: config.notyType[typeName],
          timeout: parseInt(config.notyTimeout[typeName], 10), 
          modal: config.notyModal[typeName],
          text: typeData[message],
      });
    }
  };
})(jQuery);
