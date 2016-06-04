(function($) {
  Drupal.behaviors.noty_messages = {
    attach: function(context) {
      // Button click.
      $('.test-noty-messages').click(function(event){
        event.preventDefault();
        event.stopPropagation();
        // Get name.
        var name = $(this).attr('name');
        // Get current actives
        if (name == 'global' || $('#edit-settings-global-is-noty-' + name).is(':checked')){
          // Change settings.
          var notySettings = Drupal.settings.notyMessages;
          notySettings.notyType[name] = $('#edit-settings-' + name + '-type :selected').val();
          notySettings.notyLayout[name] = $('#edit-settings-' + name + '-layout :selected').val();
          notySettings.notyTimeout[name] = $('#edit-settings-' + name + '-timeout').val();
          notySettings.notyModal[name] = $('#edit-settings-' + name + '-modal').is(':checked');
          notySettings.notyTheme[name] = $('#edit-settings-global-theme :selected').val();
          testMessages = new Array(
            Drupal.t('This is a @name message', {'@name': name}),
            Drupal.t('And this is another one!')
          );
          new notyMessages.renderType(name, testMessages, notySettings);
        }
        else{
          alert(Drupal.t('This is not a noty message'));
        }
        return false;
      });
    }
  };
})(jQuery);
