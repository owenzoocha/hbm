<div class="row">
  <h2>Your Information</h2>
  <div class="col-sm-2">
    <label class="control-label" for="edit-field-my-name-und-0-value">Full Name: </label>
  </div>
  <div class="col-sm-10">
    <?php print render($form['field_my_name']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-2">
    <label class="control-label" for="edit-field-my-bio-und-0-value">About Me: </label>
  </div>
  <div class="col-sm-10">
    <?php print render($form['field_my_bio']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-2">
    <label class="control-label" for="edit-field-gender-und">Gender: </label>
  </div>
  <div class="col-sm-4">
    <?php print render($form['field_gender']); ?>
  </div>
    <div class="col-sm-2">
    <label class="control-label" for="edit-field-phone-und-0-value">Phone: </label>
  </div>
  <div class="col-sm-4">
    <?php print render($form['field_phone']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-2">
    <label class="control-label" for="edit-field-my-college-und-0-value">College: </label>
  </div>
  <div class="col-sm-4">
    <?php print render($form['field_my_college']); ?>
  </div>
    <div class="col-sm-2">
    <label class="control-label" for="edit-field-my-company-und-0-value">Company: </label>
  </div>
  <div class="col-sm-4">
    <?php print render($form['field_my_company']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-2">
    <label class="control-label" for="edit-field-my-web-und-0-url">Web: </label>
  </div>
    <div class="col-sm-8">
    <?php print render($form['field_my_web']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-12">
    <h2>Photos</h2>
    <?php print render($form['picture']); ?>
  </div>
  <div class="col-sm-12">
    <?php print render($form['field_hb_cover_pic']); ?>
  </div>
</div>
<div class="row">
  <div class="col-sm-12">
    <h2>Address</h2>
    <?php print render($form['geocomplete']); ?>
    <?php print render($form['field_my_address']); ?>
  </div>
</div>



<?php print drupal_render_children($form) ?>
