<?php print render($form['hbm_type']); ?>
<!-- <div class="row"> -->
<fieldset class="panel panel-default form-wrapper">

  <legend class="panel-heading">
    <span class="panel-title fieldset-legend">Post a Job</span>
  </legend>

  <div class="panel-body">


    <div class="col-sm-12">
      <h2>1. Job Information</h2>
    </div>

    <div class="col-sm-2">
      <label class="control-label" for="edit-title">Job title <span class="form-required" title="This field is required.">*</span></label>
    </div>
    <div class="col-sm-10">
      <?php print render($form['wrapper']['title']); ?>
    </div>

    <div class="col-sm-2">
      <label class="control-label" for="edit-field-hb-gender">Who's it for? </label>
    </div>
    <div class="col-sm-4">
      <?php print render($form['wrapper']['field_hb_gender']); ?>
    </div>
    <div class="col-sm-2">
      <label class="control-label" for="edit-hbf-field-hb-ht">Select hair treatment type </label>
    </div>
    <div class="col-sm-4">
      <?php print render($form['wrapper']['hbf_field_hb_ht']); ?>
    </div>

  </div>

</fieldset>
<!-- </div> -->



<?php print drupal_render_children($form) ?>
