<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

// -37.859354, 144.971573 == 11/349.. blabla

// function models_search_api_solr_search_results_alter(&$results, $query, $response) {
//   dpm($results);
//   dpm($response);
// }

/**
 * Implements hook_preprocess_node().
 */
function models_preprocess_node(&$variables) {
  global $user;
  if ($variables['view_mode'] == 'teaser') {
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__teaser';
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->nid . '__teaser';
  }

  if ($variables['type'] == 'job') {
    $nw = entity_metadata_wrapper('node', $variables['nid']);
    $uw = entity_metadata_wrapper('user', $user->uid);

    if ($variables['view_mode'] == 'teaser') {
      $mypic = $nw->author->value()->picture;
      if ($mypic) {
        $pic = '<div class="my-image img-circle">' . theme('image_style', array(
            'style_name' => 'profile',
            'path' => $nw->author->value()->picture->uri,
            'attributes' => array('class' => array('img-circle'))
          )) . '</div>';
      }
      else {
        $pic = '<div class="my-image img-circle">' . theme('image_style', array(
            'style_name' => 'profile',
            'path' => 'public://pictures/picture-default.png',
            'attributes' => array('class' => array('img-circle'))
          )) . '</div>';
      }
      $variables['author_pic'] = l($pic, 'user/' . $nw->author->getIdentifier(), array(
        'html' => TRUE,
        'attributes' => array('class' => array('author-pic'))
      ));

      $image = FALSE;
      $location = FALSE;
      if ($nw->field_hb_location->value()) {
        if ($nw->field_hb_location->value()['locality']) {
          $location = '<div class="hb-location"><i class="fa fa-map-marker"></i> ' . $nw->field_hb_location->value()['locality'] . '</div>';
        }
        else {
          $location = '<div class="hb-location"><i class="fa fa-map-marker"></i> ' . $nw->field_hb_location->value()['premise'] . '</div>';
        }
      }

      if ($nw->field_hb_time->value()) {
        $sz = sizeof($nw->field_hb_time->value());
        $ts = date('d/m/y H:ia', $nw->field_hb_time->value()[0]);
        $time = $sz . ' ' . format_plural($sz, 'appointment', 'appointments') . ' from ' . $ts;
        $starting = '<div class="hb-starting"><i class="fa fa-clock-o"></i> ' . $time . '</div>';
      }
      else {
        $starting = FALSE;
      }

      if ($nw->field_hb_type->value() != 'personal') {
        if ($nw->field_hb_pics->value()) {
          $promoted_img_uri = models_cache_get_promoimg_cache($nw->getIdentifier());
          $image = l(theme('image_style', array(
            'style_name' => 'profile',
            'path' => $promoted_img_uri
          )), 'node/' . $nw->getIdentifier(), array('html' => TRUE));
        }
        else {
          if ($nw->field_hb_type->value() == 'hair') {
            $image = l('<img class="img-responsive" src="/sites/all/themes/models/images/hair-button.png">', 'node/' . $nw->getIdentifier(), array('html' => TRUE));
          }
          if ($nw->field_hb_type->value() == 'beauty') {
            $image = l('<img class="img-responsive" src="/sites/all/themes/models/images/beauty-button.png">', 'node/' . $nw->getIdentifier(), array('html' => TRUE));
          }
        }
      }
      else {
        if (!$nw->field_hb_pics->value()) {
          $image = l(theme('image_style', array(
            'style_name' => 'profile',
            'path' => $nw->author->value()->picture->uri
          )), 'node/' . $nw->getIdentifier(), array('html' => TRUE));
        }
        else {
          $promoted_img_uri = models_cache_get_promoimg_cache($nw->getIdentifier());
          $image = l(theme('image_style', array(
            'style_name' => 'profile',
            'path' => $promoted_img_uri
          )), 'node/' . $nw->getIdentifier(), array('html' => TRUE));
        }
      }


      $cost_class = FALSE;
      $cost = $nw->field_hb_price_text->value() ? '<div class="hb-cost"><i class="fa fa-dollar"></i> ' . $nw->field_hb_price_text->value() . '</div>' : FALSE;
      $variables['costs'] = $cost;


//      if ($nw->field_hb_type->value() != 'personal') {
//        if ($nw->field_hb_price_text->value()) {
//          $cost = $nw->field_hb_price_text->value();
//        }
//        else {
//          $cost = '19.55';
//        }
//      }

//
//      if ($nw->field_hb_price_type->value()) {
//        switch ($nw->field_hb_price_type->value()) {
//          case 'free':
//            $pt = 'Free';
//            $cost_class = 'cost-free';
//            $cost = FALSE;
//            break;
//          case 'approx':
//            $pt = ' <small>Approx.</small>';
//            break;
//          case 'fixed':
//            $pt = FALSE;
//            break;
//          default:
//            $pt = FALSE;
//            break;
//        }
//      }
//      else {
//        $pt = FALSE;
//      }

      $image_and_type = '<div class="hb-imagery pull-left">';
      $image_and_type .= '<span>' . $image . '</span>';

      $liked = FALSE;
      if (in_array($nw->getIdentifier(), tweaks_get_watchlist($uw))) {
        $liked = 'hb-like-active';
      }


      if ($nw->field_hb_type->value()) {
        $tooltip_h = $tooltip_b = '';
        if ($nw->field_hb_type->value() == 'hair' || $nw->field_hb_type->value() == 'personal') {
          if (sizeof($nw->field_hb_ht->value())) {
            $tooltip_h .= t('Hair &raquo ');
            foreach ($nw->field_hb_ht->getIterator() as $key => $ht) {
              $tooltip_h .= $ht->label() . ', ';
            }
            $tooltip_h = rtrim($tooltip_h, ', ');
          }
        }
        if ($nw->field_hb_type->value() == 'beauty' || $nw->field_hb_type->value() == 'personal') {
          if (sizeof($nw->field_hb_bt->value())) {
            $tooltip_b .= t('Beauty &raquo ');
            foreach ($nw->field_hb_bt->getIterator() as $key => $bt) {
              $tooltip_b .= $bt->label() . ', ';
            }
            $tooltip_b = rtrim($tooltip_b, ', ');
          }
        }
        $tooltip = $tooltip_h . ' ' . $tooltip_b;
        $more_info = '<span class="hb-info" data-toggle="tooltip" data-placement="top" title="' . $tooltip . '"><i class="fa fa-info-circle"></i></span>';
      }
      else {
        $more_info = FALSE;
      }

      $image_and_type .= '<span data-jid="' . $nw->getIdentifier() . '" class="hb-like ' . $liked . ' fa fa-star"></span>';
//      $image_and_type .= $more_info;
      $image_and_type .= '</div>';

      $variables['the_image'] = $image_and_type;
      $variables['more_info'] = l('<i class="fa fa-caret-down"></i> Quick Info', 'search', array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('quick-view'),
          'data-nid' => array($nw->getIdentifier())
        )
      ));
      $variables['view_link'] = l('View Job', 'node/' . $nw->getIdentifier(), array(
        'html' => TRUE,
        'attributes' => array('class' => array('a-link'))
      ));
      $variables['more_info_list'] = $tooltip;

      $alter = array(
        'max_length' => 250,
        'ellipsis' => TRUE,
        'word_boundary' => TRUE,
        'html' => TRUE,
      );
      $variables['description'] = $nw->body->value() ? views_trim_text($alter, drupal_html_to_text($nw->body->value()['value'], array(
        'p',
        'a'
      ))) : FALSE;

//      if ($nw->field_hb_type->value() != 'personal') {
//      }

      $variables['the_type'] = '<span class="hb-type hb-type-' . strtolower($nw->field_hb_type->label()) . '">' . $nw->field_hb_type->label() . '</span>';;
      $variables['location'] = $location;
      $variables['starting'] = $starting;

      $variables['posted_by'] = '<div class="hb-author"><small>Posted by: </small>' . $nw->author->label() . ', <span class="hb-timeago">' . format_date($nw->created->value(), 'timeago', 'Y-m-d H:i:s', 'UTC') . '</span></div>';

      $stars = $nw->author->field_my_overall_rating->value() ? $nw->author->field_my_overall_rating->value() : 0;
      $variables['stars'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>';

      // $variables['created'] = '<span>' . format_date($nw->created->value(), 'timeago', 'Y-m-d H:i:s', 'UTC') . '</span>';
      $variables['created'] = FALSE;

      // if (strpos(current_path(), 'users') !== FALSE && !drupal_is_front_page()) {
      if (strpos(current_path(), 'my-jobs') !== FALSE) {
        if ($nw->author->getIdentifier() == $uw->getIdentifier()) {

          if ($nw->field_hb_cancelled->value()) {
            $variables['job_status'] = t('Cancelled');
          }
          else {
            if ($nw->field_hb_paused->value()) {
              $variables['job_status'] = t('Paused');
            }
            else {
              if ($nw->field_hb_assigned->value()) {
                $variables['job_status'] = $nw->field_hb_feedb_size->value() != $nw->field_hb_client_size->value() ? t('Leave Feedback') : t('Feedback Complete');
              }
              else {
                if ($nw->field_hb_feedback_complete->value()) {
                  $variables['job_status'] = t('Complete');
                }
                else {
                  if ($nw->field_hb_completed->value()) {
                    $variables['job_status'] = t('Complete');
                  }
                  else {
                    if (!$nw->status->value()) {
                      $variables['job_status'] = t('Unpublished');
                    }
                    else {
                      if ($nw->status->value()) {
                        $variables['job_status'] = t('Running');
                      }
                    }
                  }
                }
              }
            }
          }

          // If there are requests OR offers.
          if ($nw->field_hb_users_eck->value()) {

            // feedb size = Feedback size so far.
            // Client Size = CONFIRMED clients to the job.
            if ($nw->field_hb_feedb_size->value() != $nw->field_hb_client_size->value()) {
              // Feedback obvs not complete..
              if (!$nw->field_hb_assigned->value()) {
                // If not assigned, then people are interested..
                $interested_txt = $nw->field_hb_type->value() != 'personal' ? t('interested') : format_plural(sizeof($nw->field_hb_users_eck->value()), t('offer'), t('offers'));
                $variables['requestees'] = '<span class="interested"><i class="material-icons">accessibility</i>' . ' ' . l(sizeof($nw->field_hb_users_eck->value()) . $interested_txt, 'job/' . $nw->getIdentifier() . '/clients') . '</span>';
              }
              else {
                // If assigned, then you need to leave feedback.
                $variables['requestees'] = '<span class="interested"><i class="material-icons">face</i>' . ' ' . l(sizeof($nw->field_hb_client_size->value()) . ' ' . t('feedback required'), 'job/' . $nw->getIdentifier() . '/feedback') . '</span>';
              }
            }
            else {
              if ($nw->field_hb_feedb_size->value()) {
                // if there is feedback size and it = client size - then feedback is complete!
                $variables['requestees'] = '<span class="interested"><i class="material-icons">done</i>' . ' ' . l(' ' . t('feedback complete'), 'job/' . $nw->getIdentifier() . '/feedback') . '</span>';
              }
              else {
                // No feedback given yet.
                // No feedback, hasn't been assigned.. //
                $interested_txt = $nw->field_hb_type->value() != 'personal' ? t('interested') : format_plural(sizeof($nw->field_hb_users_eck->value()), t('offer'), t('offers'));
                $variables['requestees'] = '<span class="interested"><i class="material-icons">accessibility</i>' . ' ' . l(sizeof($nw->field_hb_users_eck->value()) . $interested_txt, 'job/' . $nw->getIdentifier() . '/clients') . '</span>';
              }
            }
          }

        }
      }
    }
    else {


      // Check if there's a last day - if so, schedule the complete flag.
      // if ($nw->field_hb_time->value()) {
      //   $date_n = sizeof($nw->field_hb_time->value()) - 1;
      //   $last_day = $nw->field_hb_time->value()[$date_n];
      //   rules_invoke_component('rules_set_schedule_schedule_the_complete_job', $last_day, $nw->value());
      // }

      $variables['users_available'] = FALSE;
      $variables['show_slick'] = $nw->field_hb_pics->value() ? TRUE : FALSE;

      if (!empty($variables['content']['field_hb_time'])) {
        $variables['content']['field_hb_time_intro'] = $variables['content']['field_hb_time'];
        $variables['content']['field_hb_time_intro']['#title'] = t('Date and Time');
      }

      if (!$nw->field_hb_assigned->value()) {
        if (!$nw->status->value()) {

          if ($nw->field_hb_type->value() != 'personal') {

            // HACKY.
            if ($nw->field_hb_cancelled->value()) {
              $unpub_msg = '<div class="alert alert-block alert-danger messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
              $unpub_msg .= t('This Job has been cancelled - and will be removed soon!');
              $unpub_msg .= '</div>';
            }
            else {
              if (!$nw->field_hb_paused->value()) {
                $unpub_msg = '<div class="alert alert-block alert-info messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
                $unpub_msg .= t('Hey !name, ' . $nw->label() . ' is currently unpublished.  Check out your job below - this is what it will look like to other users.  To publish your job, click <strong>Publish Job</strong> below.', array('!name' => $uw->field_first_name->value()));
                $unpub_msg .= '</div>';
              }
              else {
                $unpub_msg = '<div class="alert alert-block alert-success messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
                $unpub_msg .= t('Hey !name, ' . $nw->label() . ' is currently <strong>paused</strong>. To resume, click <strong>Resume Job</strong> below.', array('!name' => $uw->field_first_name->value()));
                $unpub_msg .= '</div>';
              }
            }
          }
          else {
            if ($nw->field_hb_cancelled->value()) {
              $unpub_msg = '<div class="alert alert-block alert-danger messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
              $unpub_msg .= t('This Job has been cancelled - and will be removed soon.');
              $unpub_msg .= '</div>';
            }
            else {
              if (!$nw->field_hb_paused->value()) {
                $unpub_msg = '<div class="alert alert-block alert-info messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
                $unpub_msg .= t('Hey !name, your job <em>' . $nw->label() . '</em> is currently inactive. To appear on <strong>HBM</strong> and start receiving <strong>Last Minute Model</strong> job offers - click <strong>Publish</strong> below.', array('!name' => $uw->field_first_name->value()));
                $unpub_msg .= '</div>';
              }
              else {
                $unpub_msg = '<div class="alert alert-block alert-success messages info"><a class="close" data-dismiss="alert" href="#">×</a><h4 class="element-invisible">Informative message</h4>';
                $unpub_msg .= t('Hey !name, ' . $nw->label() . ' is currently <strong>paused</strong>. To resume, click <strong>Resume Job</strong> below.', array('!name' => $uw->field_first_name->value()));
                $unpub_msg .= '</div>';
              }
            }
          }

          $variables['unpub_msg'] = $unpub_msg;

          // Publish a job button.
          $publish_form = drupal_get_form('models_forms_publish_form');
          $modal_options = array(
            'attributes' => array(
              'id' => 'job-publish-form-popup',
              'class' => array('job-publish-form-popup-modal')
            ),
            'heading' => t('Publish Job:') . ' ' . $nw->label(),
            'body' => drupal_render($publish_form),
          );
          $variables['job_publish_form'] = theme('bootstrap_modal', $modal_options);

          $job_publish_text = !$nw->field_hb_paused->value() ? t('Publish Job') : t('Resume Job');

          $job_publish = l($job_publish_text, '#', array(
            'attributes' => array(
              'data-toggle' => array('modal'),
              'data-target' => array('#job-publish-form-popup'),
              'class' => array('btn btn-success')
            )
          ));
          $variables['job_publish_button'] = ($nw->author->getIdentifier() != 000) ? '<div class="hb-job-button">' . $job_publish . '</div>' : FALSE;
        }
        else {
          $btn_text = $nw->field_hb_type->value() != 'personal' ? t('Request Job') : t('Offer Service');
          $btn_class = 'btn-info';
          if ($nw->field_hb_users_eck->value()) {
            // if ($uw->getIdentifier() == $nw->author->getIdentifier()) {
            //   $variables['users_available'] = sizeof($nw->field_hb_users->value());
            // }
            foreach ($nw->field_hb_users_eck->getIterator() as $k => $u) {
              if ($u->field_feedb_user->getIdentifier() == $uw->getIdentifier()) {
                $btn_text = $nw->field_hb_type->value() != 'personal' ? t('Remove Request') : t('Remove Offer');
                $btn_class = 'btn-danger';
                break;
              }
            }
          }

          // Request a job button.
          $request_form = drupal_get_form('models_forms_request_form');
          $modal_options = array(
            'attributes' => array(
              'id' => 'job-request-form-popup',
              'class' => array('job-request-form-popup-modal')
            ),
            'heading' => $nw->field_hb_type->value() != 'personal' ? t('Request job:') . ' ' . $nw->label() : t('Get in touch with') . ' ' . $nw->author->field_first_name->value(),
            'body' => drupal_render($request_form),
          );
          $variables['job_request_form'] = theme('bootstrap_modal', $modal_options);

          if ($user->uid != 0) {
            $job_details = l($btn_text, '#', array(
              'attributes' => array(
                'data-toggle' => array('modal'),
                'data-target' => array('#job-request-form-popup'),
                'class' => array('btn ' . $btn_class)
              )
            ));
          }
          else {
            $job_details = l($btn_text, 'user/login', array('attributes' => array('class' => array('btn ' . $btn_class))));
          }
          $variables['job_button'] = ($nw->author->getIdentifier() != 000) ? '<div class="hb-job-button">' . $job_details . '</div>' : FALSE;
          $variables['unpub_msg'] = FALSE;
        }
      }
      else {
        $variables['feedback_button'] = '<div class="hb-job-button">' . l(t('Leave Feedback'), 'job/' . $nw->getIdentifier() . '/feedback', array('attributes' => array('class' => array('btn btn-danger')))) . '</div>';
        $variables['job_button'] = '<p><strong>' . t('Sorry, this job has already been assigned!') . '</strong></p>';
      }
    }
  }
}

/**
 * Implements hook_preprocess_page()
 */
function models_preprocess_page(&$variables) {
  global $user;
  $uw = entity_metadata_wrapper('user', $user);
  if ( strpos(drupal_get_path_alias(), 'users/') !== FALSE
    || (arg(0) == 'user' && is_numeric(arg(1)) && arg(2) == 'feedback')) {
    $variables['this_is_user'] = TRUE;
  }
  else {
    $variables['this_is_user'] = FALSE;
  }

  // Save the first name part.
  if (!$uw->field_first_name->value()) {
    if ($uw->field_my_name->value()) {
      $fname = explode(' ', $uw->field_my_name->value());
      $uw->field_first_name->set($fname[0]);
      $uw->save();
    }
  }

  // Save the whole my name part.
  if ($uw->field_first_name->value()) {
    $update_name = $uw->field_first_name->value();
    if ($uw->field_surname->value()) {
      $update_name .= ' ' . $uw->field_surname->value();
      $uw->field_my_name->set($update_name);
      $uw->save();
    }
  }

  $variables['home_nav'] = $user->uid == 0 ? theme('home_nav') : FALSE;

  if (drupal_is_front_page()) {
    drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/animate.css/3.4.0/animate.min.css', array('type' => 'external'));
    unset($variables['page']['content']);
    $variables['logo'] = drupal_get_path('theme', 'models') . '/' . 'white-logo.png';
    if (isset($_COOKIE['Drupal_visitor_not_verified_logoff'])) {
      if ($_COOKIE['Drupal_visitor_not_verified_logoff'] != 0) {
        // drupal_set_message(t('Oops - it looks like you haven\'t verified your account yet! Please check your email for the verification link - or request a new password'), 'status', FALSE);

        $logged_out_user = user_load($_COOKIE['Drupal_visitor_not_verified_logoff']);
        if (in_array('unauthenticated user', $logged_out_user->roles)) {
          drupal_set_message('Oops - it looks like you haven\'t verified your account yet! Please check your email for the verification link - or ' . l(t('resend validation e-mail'), 'revalidate-email/' . $_COOKIE['Drupal_visitor_not_verified_logoff']));
          // user_cookie_save(array('not_verified.logoff' => 0));
        }
        else {
          user_cookie_delete('not_verified.logoff');
        }
      }
    }
  }

  // Bounce non admin onto personal info instead of user/edit.
  if (!in_array('hbm_admin', $user->roles) || $user->uid != 1) {
    unset($variables['tabs']);

    if (strrpos(current_path(), 'user/' . $user->uid . '/edit') !== FALSE) {
      drupal_goto('user/personal-information/settings');
    }
  }

  // $msg_count = privatemsg_unread_count($uw->value());
  // dpm( $msg_count );

  $variables['social'] = theme('social_nav');
  $variables['custom_nav'] = $user->uid != 0 ? theme('custom_nav') : FALSE;
  $variables['title_search_class'] = FALSE;

  $search_menu = theme('search_menu');
  $variables['search_menu'] = $search_menu;

  if (!$uw->field_my_tcs->value() && $user->uid != 0) {
    $tc_msg = t('Welcome to Hair & Beauty Models! To get started, please make sure you accept the') . ' ' . l('terms and conditions', 'terms') . ' ' . '<strong>' . l('here', 'user/personal-information/settings', array('fragment' => 'edit-field-my-tcs')) . '</strong>.';
    drupal_set_message($tc_msg, 'warning', FALSE);
  }

  if (strrpos(current_path(), 'search') !== FALSE) {
    $variables['no_footer'] = TRUE;
    unset($variables['tabs']);
  }

  if ((arg(0) == 'user' && is_numeric(arg(1)) && !arg(2) || strrpos(current_path(), '/settings') !== FALSE) && strpos(current_path(), 'user/reset') === FALSE) {
    $variables['content_column_class'] = ' class="col-sm-pull-3 col-sm-9"';
  }

  if ($user->uid == 0) {
    unset($variables['tabs']);
    if (current_path() == 'user') {
      drupal_goto('user/login');
    }
    if (current_path() == 'user/login') {
      drupal_set_title('Sign in');
    }
    if (current_path() == 'user/register') {
      drupal_set_title('Sign up');
    }
    if (current_path() == 'user/password') {
      drupal_set_title('Request new password');
    }
  }

  // Tweenmax
//  drupal_add_js('http://cdnjs.cloudflare.com/ajax/libs/gsap/1.18.4/TweenMax.min.js', array('type' => 'external'));

  // drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/skrollr/0.6.30/skrollr.min.js', array('type' => 'external'));
  // drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/jquery-noty/2.3.8/packaged/jquery.noty.packaged.min.js', array('type' => 'external'));

  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.12.0/moment.min.js', 'external');
//  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/ScrollMagic/2.0.5/ScrollMagic.min.js', 'external');
//  drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/ScrollMagic/2.0.5/plugins/debug.addIndicators.min.js', 'external');
  drupal_add_js(libraries_get_path('raty-fa-0.1.1') . '/' . 'lib/jquery.raty-fa.js');

  // dpm(current_path());
  // dpm_once($_SERVER['REQUEST_URI']);

  // Set navbar to fixed.
  // navbar navbar-default navbar-fixed-top
  $variables['navbar_classes_array'][1] = 'container-fluid';

  if (strrpos(current_path(), 'search') !== FALSE && strrpos(current_path(), 'ts/') === FALSE && strrpos(current_path(), 'messages/') === FALSE ||
    strpos(current_path(), 'previous-jobs') !== FALSE ||
    strpos(current_path(), 'my-jobs') !== FALSE ||
    strpos(current_path(), 'watchlist') !== FALSE ||
    strpos(current_path(), 'job-requests') !== FALSE
  ) {
    drupal_add_js('https://npmcdn.com/imagesloaded@4.1/imagesloaded.pkgd.min.js', 'external');
//    drupal_add_js('https://npmcdn.com/masonry-layout@4.0.0/dist/masonry.pkgd.min.js', 'external');
//    drupal_add_js(drupal_get_path('theme', 'models') . '/' . 'js/hbm_user_jobs.js');
  }

  if (strrpos(current_path(), 'search') !== FALSE && strrpos(current_path(), 'ts/') === FALSE && strrpos(current_path(), 'messages/') === FALSE) {
    drupal_add_js(drupal_get_path('theme', 'models') . '/' . 'js/hbm_search.js');
    // drupal_add_js('https://cdnjs.cloudflare.com/ajax/libs/ScrollMagic/2.0.5/plugins/debug.addIndicators.min.js', 'external');
    $variables['container_class'] = 'container';
    $variables['title_search_class'] = 'event-page';
//    $variables['content_column_class'] = ' class="col-sm-9 event-page"';
    $variables['content_column_class'] = ' class="col-sm-pull-3 col-sm-9 event-page"';

    $variables['hb_header_class'] = 'pull-left';

    $slick_block = block_load('search_api_sorts', 'search-sorts');
    $block = _block_get_renderable_array(_block_render_blocks(array($slick_block)));
    $variables['filter_blocks'] = drupal_render($block);
  }


  if (strpos(current_path(), 'job/create') !== FALSE) {
    if ($user->uid != 1) {
      if ($uw->field_flags_running_posts->value() >= 5) {
        drupal_set_message(t('Hi !name, you currently have 5 jobs running. To post another, you must wait until one of your jobs has completed.', array('!name' => $uw->field_first_name->value() ? $uw->field_first_name->value() : $uw->label())), 'info', FALSE);
        drupal_goto('my-jobs');
      }
    }
    // $variables['content_column_class'] = ' class="col-sm-pull-3 col-sm-9"';
  }

  // Alllll stuffs for the author pic and top nav stuff.
  if ((strpos(current_path(), 'node') !== FALSE) ||
    (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/edit') !== FALSE) ||
    (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/feedback') !== FALSE) ||
    (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/clients') !== FALSE) ||
    (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/photos') !== FALSE)
  ) {

    $nw = entity_metadata_wrapper('node', arg(1));

    if ($nw->getBundle() == 'job') {

      // Bounce people off the edit or manage clients page if the job is completed.
      if ($nw->field_hb_completed->value()) {
        if (strpos(current_path(), 'job/' . $nw->getIdentifier() . '/edit') !== FALSE || strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/clients') !== FALSE) {
          // If person is admin or hbadmin...
          // if ($user->uid != 1) {
          drupal_set_message(t('Oops - this job has been completed - no more edits! :)'), 'info', FALSE);
          drupal_goto('node/' . $nw->getIdentifier());
          // }
        }
      }

      // Pause a job button.
      $pause_form = drupal_get_form('models_forms_pause_form');
      $modal_options = array(
        'attributes' => array(
          'id' => 'job-pause-form-popup',
          'class' => array('job-pause-form-popup-modal')
        ),
        'heading' => t('Pause Job:') . ' ' . $nw->label(),
        'body' => drupal_render($pause_form),
      );
      $variables['job_pause_form'] = theme('bootstrap_modal', $modal_options);

      // Cancel a job button.
      $cancel_form = drupal_get_form('models_forms_cancel_form');
      $modal_options = array(
        'attributes' => array(
          'id' => 'job-cancel-form-popup',
          'class' => array('job-cancel-form-popup-modal')
        ),
        'heading' => t('Cancel Job:') . ' ' . $nw->label(),
        'body' => drupal_render($cancel_form),
      );
      $variables['job_cancel_form'] = theme('bootstrap_modal', $modal_options);

      if ($nw->field_hb_feedb_size->value()) {
        if ($nw->field_hb_feedb_size->value() == $nw->field_hb_client_size->value()) {
          // Cancel a job button.
          $complete_form = drupal_get_form('models_forms_complete_form');
          $modal_options = array(
            'attributes' => array(
              'id' => 'job-complete-form-popup',
              'class' => array('job-complete-form-popup-modal')
            ),
            'heading' => t('Job Completed:') . ' ' . $nw->label(),
            'body' => drupal_render($complete_form),
          );
          $variables['job_complete_form'] = theme('bootstrap_modal', $modal_options);
        }
      }


      // if ( strpos(current_path(), 'job/') !== FALSE && is_numeric(arg(1)) ) {
      $variables['content_column_class'] = ' class="col-sm-pull-3 col-sm-9"';
      // }


      drupal_add_js(libraries_get_path('slick') . '/' . 'slick/slick.min.js');
      drupal_add_css(libraries_get_path('slick') . '/' . 'slick/slick.css');
      drupal_add_css(libraries_get_path('slick') . '/' . 'slick/slick-theme.css');
      drupal_add_js(drupal_get_path('module', 'models_nav') . '/js/models_nav.js');

      // if (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/clients') !== FALSE) {
      //   if ($nw->field_hb_assigned->value()) {
      //     drupal_goto('node/' . $nw->getIdentifier());
      //   }
      // }

      // Page titles clean up
      if ((strpos(current_path(), 'job/') !== FALSE && is_numeric(arg(1)) && strpos(current_path(), '/clients') !== FALSE)) {
        if ($nw->field_hb_users_eck->value()) {
          $reqs = sizeof($nw->field_hb_users_eck->value());
        }
        else {
          $reqs = FALSE;
        }
//        drupal_set_title($reqs > 0 ? $nw->label() . ' - Client Requests (' . $reqs . ')' : $nw->label() . ' - Client Requests');
      }

      // Page titles clean up
      if ((strpos(current_path(), 'job/') !== FALSE && is_numeric(arg(1)) && strpos(current_path(), '/photos') !== FALSE)) {
        drupal_add_js(array('photo_nid' => $nw->getIdentifier()), 'setting');
//        drupal_set_title($nw->label() . ' - Photos');
      }

      // Initiate custom job navigation if logged in user = author.
      if ($nw->author->getIdentifier() == $uw->getIdentifier()) {
        $variables['my_nav'] = theme('my_nav');
      }
      else {
        $variables['my_nav'] = FALSE;
        $variables['show_bg'] = TRUE;
      }

      $variables['hb_header_class'] = 'header-title';

      $mypic = $nw->author->value()->picture;
      if ($mypic) {
        $pic = '<div class="my-image img-circle">' . theme('image_style', array(
            'style_name' => 'profile',
            'path' => $nw->author->value()->picture->uri,
            'attributes' => array('class' => array('img-circle'))
          )) . '</div>';
      }
      else {
        $pic = '<div class="my-image img-circle">' . theme('image_style', array(
            'style_name' => 'profile',
            'path' => 'public://pictures/picture-default.png',
            'attributes' => array('class' => array('img-circle'))
          )) . '</div>';
      }
      $variables['author_pic'] = l($pic, 'user/' . $nw->author->getIdentifier(), array(
        'html' => TRUE,
        'attributes' => array('class' => array('author-pic'))
      ));

      $stars = $nw->author->field_my_overall_rating->value() ? $nw->author->field_my_overall_rating->value() : 0;

//      $variables['author_rating'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>';
      $variables['author_rating'] = FALSE;
      $variables['author_feedback_amount'] = FALSE;

//      if (1 == 1) {
//        $fbk = $nw->author->field_my_total_feedback->value() ? $nw->author->field_my_total_feedback->value() : 0;
//        $variables['author_feedback_amount'] = '<div class="hb-feedback-score">' . l($fbk . ' ' . t('feedback'), 'user/' . $nw->author->getIdentifier() . '/feedback') . ' | ' . l(t('send message'), 'messages/new/' . $nw->author->getIdentifier(), array('query' => array('destination' => 'node/' . $nw->getIdentifier()))) . '</div>';
//      }
//      else {
//        $variables['author_feedback_amount'] = '<div class="hb-feedback-score">' . t('- no feedback -') . '</div>';
//      }

//      $job_details = '<div class="yoga-intro">';
//      $job_details .= '<div class="hb-time">';
//      $job_details .= '<span>' . t('Posted by') . ' ' . l($nw->author->label(), 'user/' . $nw->author->getIdentifier()) . '</span>, ';
//      $job_details .= '<span>' . format_date($nw->created->value(), 'timeago', 'Y-m-d H:i:s', 'UTC') . '</span>';
//      $job_details .= '</div>';
//      $job_details .= '<div>';
//      $job_details .= tweaks_get_hb_cost($nw);
//      $job_details .= $nw->field_hb_type->value() != 'personal' ? '<span class="hdr-hb-type hb-' . strtolower($nw->field_hb_type->value()) . '">' . ucfirst($nw->field_hb_type->value()) . '</span>' : FALSE;
//      $job_details .= $nw->field_hb_completed->value() ? '<span class="hdr-hb-type hdr-hb-complete">' . t('This job has ended') . '</span>' : FALSE;
//
//
//      $job_details .= '</div>';
//      $job_details .= '</div>';

//      $variables['job_details'] = $job_details;
      $variables['job_details'] = FALSE;
      // dpm(theme_date_time_ago($ts));

      // $stars = $uw->field_my_overall_rating->value() ? $uw->field_my_overall_rating->value() : 0;
      // $variables['author_rating'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>';
      // $variables['content_column_class'] = ' class="col-sm-12 event-page"';

      // Page titles clean up
      if ((strpos(current_path(), 'job/') !== FALSE && is_numeric(arg(1)) && strpos(current_path(), '/clients') !== FALSE)) {

        // Client request accept / remove
        $client_request_form = drupal_get_form('models_forms_confirm_clients_form');
        $modal_options = array(
          'attributes' => array(
            'id' => 'job-publish-form-popup',
            'class' => array('job-publish-form-popup-modal')
          ),
          'heading' => t('Confirm Clients'),
          'body' => drupal_render($client_request_form),
        );
        $variables['client_request_confirm_form'] = theme('bootstrap_modal', $modal_options);
      }
    }
  }

  // Ignore below if user/reset is in the path.
  if (strpos(current_path(), 'user/reset') === FALSE) {

    // Build up the users home page top bar..
    if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2) ||
      strpos(current_path(), 'previous-jobs') !== FALSE ||
      strpos(current_path(), 'user/') !== FALSE && strpos(current_path(), '/feedback') !== FALSE ||
      strpos(current_path(), 'user/') !== FALSE && strpos(current_path(), '/photos') !== FALSE ||
      strpos(current_path(), 'my-jobs') !== FALSE ||
      strpos(current_path(), 'watchlist') !== FALSE ||
      strpos(current_path(), 'job-requests') !== FALSE ||
      (arg(0) == 'user' && !is_numeric(arg(1)) && arg(2))
    ) {
      // Bump anons to the login page when looking at users..
      if ($user->uid == 0) {
        drupal_goto('user/login');
      }

      if (in_array('unauthenticated user', $user->roles)) {
        require_once(drupal_get_path('module', 'user') . '/user.pages.inc');
        user_logout();
        // drupal_set_message(t('Oops - it looks like you haven\'t verified your account yet! Please check your email for the verification link - or request a new password'), 'status', FALSE);
        // drupal_goto('search');
      }

      // Delete the 'just registered' set_variable.
      if (variable_get('just_registered_' . $user->uid)) {
        variable_del('just_registered_' . $user->uid);
      }

      $variables['cover_pic'] = $uw->field_hb_cover_pic->value() ? 'style="background:url(' . image_style_url('coverpic', $uw->field_hb_cover_pic->value()['uri']) . ')"' : FALSE;


      if (is_numeric(arg(1))) {
        if ($user->uid == arg(1)) {
          $greeting = t('Welcome back'); // If cookie set?
          $greeting = t('Hi') . ', ';
          drupal_set_title($greeting . $uw->field_first_name->value());
          $pic = tweaks_get_profile_picture($uw->value());
          $author_pic = tweaks_get_profile_url($pic, $uw->getIdentifier());
          $stars = $uw->field_my_overall_rating->value() ? $uw->field_my_overall_rating->value() : 0;
          $job_details = tweaks_get_profile_intro($uw);
          $author_feedback_amount = tweaks_get_feedback_amount($uw);
        }
        else {
          $person = entity_metadata_wrapper('user', arg(1));
          drupal_set_title($person->field_my_name->value());
          $pic = tweaks_get_profile_picture($person->value());
          $author_pic = tweaks_get_profile_url($pic, $person->getIdentifier());
          $stars = $person->field_my_overall_rating->value() ? $person->field_my_overall_rating->value() : 0;
          $job_details = tweaks_get_profile_intro($person);
          $author_feedback_amount = tweaks_get_feedback_amount($person);
        }
      }
      else {
        // HACKATHON
        // $greeting = t('Welcome back'); // If cookie set?
        // $greeting = t('Hi') . ', ';
        // drupal_set_title($greeting . $uw->field_first_name->value());
        $pic = tweaks_get_profile_picture($uw->value());
        $author_pic = tweaks_get_profile_url($pic, $uw->getIdentifier());
        $stars = $uw->field_my_overall_rating->value() ? $uw->field_my_overall_rating->value() : 0;
        $job_details = tweaks_get_profile_intro($uw);
        $author_feedback_amount = tweaks_get_feedback_amount($uw);
      }

      $variables['hb_header_class'] = 'header-title pull-left';
      $variables['author_pic'] = $author_pic;
      $variables['author_rating'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>';
      $variables['author_feedback_amount'] = $author_feedback_amount;
      $variables['job_details'] = $job_details;

      // Initiate custom job navigation if logged in user = author.
      if (arg(1) == $uw->getIdentifier() ||
        strpos(current_path(), 'previous-jobs') !== FALSE ||
        strpos(current_path(), 'my-jobs') !== FALSE ||
        strpos(current_path(), 'user/') !== FALSE && strpos(current_path(), '/photos') !== FALSE ||
        strpos(current_path(), 'job-requests') !== FALSE ||
        strpos(current_path(), 'watchlist') !== FALSE ||
        strpos(current_path(), 'job-requests') !== FALSE ||
        (arg(0) == 'user' && !is_numeric(arg(1)) && arg(2))
      ) {
        $variables['my_nav'] = theme('my_nav', array('user_nav' => $uw->getIdentifier()));
      }
      else {
        $variables['my_nav'] = theme('my_nav', array(
          'user_nav' => $uw->getIdentifier(),
          'someone_else' => TRUE
        ));
      }
    }
  }

  if (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/photos') !== FALSE || strpos(current_path(), 'user/photos') !== FALSE) {
    drupal_add_css(libraries_get_path('dropzone') . '/' . 'dist/min/basic.min.css');
    drupal_add_css(libraries_get_path('dropzone') . '/' . 'dist/min/dropzone.min.css');
    drupal_add_js(libraries_get_path('dropzone') . '/' . 'dist/min/dropzone.min.js');
  }
}

/**
 * Implements hook_preprocess_html().
 */
function models_preprocess_html(&$variables) {
  if ((strpos(current_path(), 'node') !== FALSE) ||
    (strpos(current_path(), 'job/') !== FALSE && strpos(current_path(), '/clients') !== FALSE)
  ) {
    $variables['classes_array'][] = 'event-mode';
  }
}

/**
 * Implements hook_preprocess_region().
 */
function models_preprocess_region(&$variables) {
  // dpm($variables);
  if ($variables['region'] == 'content') {
    // if (arg(0) == 'user') {
    //   $variables['classes_array'][] = 'row';
    // }
  }
}

/**
 * Implements theme_status_messages().
 */
// function models_status_messages($variables) {
//   global $user;
//   $display = $variables['display'];
//   $output = '';

//   $status_heading = array(
//     'status' => t('Status message'),
//     'error' => t('Error message'),
//     'warning' => t('Warning message'),
//     'info' => t('Informative message'),
//   );

//   // Map Drupal message types to their corresponding Bootstrap classes.
//   // @see http://twitter.github.com/bootstrap/components.html#alerts
//   $status_class = array(
//     'status' => 'success',
//     'success' => 'success',
//     'error' => 'danger',
//     'warning' => 'warning',
//     // Not supported, but in theory a module could send any type of message.
//     // @see drupal_set_message()
//     // @see theme_status_messages()
//     'info' => 'info',
//   );

//   // Custom noty stuffs..
//   $noty = array();
//   $capture = TRUE;

//   foreach (drupal_get_messages($display) as $type => $messages) {

//     if (strpos($type, ':') !== FALSE) {
//       $typetmp = explode(':', $type);
//       $type = $typetmp[0];
//       $pos = $typetmp[1];
//       $timer = $typetmp[2];
//     }

//     $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';

//     $output .= "<div class=\"alert alert-block$class messages $type\">\n";
//     $output .= "  <a class=\"close\" data-dismiss=\"alert\" href=\"#\">&times;</a>\n";

//     if (!empty($status_heading[$type])) {
//       $output .= '<h4 class="element-invisible">' . $status_heading[$type] . "</h4>\n";
//     }

//     if (count($messages) > 1) {
//       $output .= " <ul>\n";
//       $msg = " <ul>";
//       foreach ($messages as $message) {
//         $output .= '  <li>' . $message . "</li>\n";
//         $msg .= '  <li>' . $message . "</li>";
//       }
//       $output .= " </ul>\n";
//       $msg .= " </ul>";
//     }
//     else {
//       $output .= $messages[0];
//       $msg = $messages[0];
//     }

//     if ($capture) {
//       switch ($type) {
//         case 'status':
//           $type = 'success';
//           break;
//         case 'info':
//           $type = 'information';
//           break;
//       }
//       $noty[] = array(
//         'type' => $type,
//         'msg' => $msg,
//         'pos' => isset($pos) ? $pos : FALSE,
//         'timer' => isset($timer) ? $timer : FALSE,
//       );
//     }

//     $output .= "</div>\n";
//   }

//   if ($user->uid != 1) {
//     if ($user->uid != 0) {
//       // drupal_add_js(array('noty' => $noty), 'setting');
//     }
//     else {
//       if (current_path() == 'user/register') {
//         // drupal_add_js(array('noty' => $noty), 'setting');
//       }
//     }
//   }

//   return $output;
// }

/**
 * Returns HTML for an active facet item.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', and 'options'. See
 *   the l() function for information about these variables.
 *
 * @see l()
 *
 * @ingroup themeable
 */
function models_facetapi_link_active($variables) {

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
  );
  $variables['text'] = t('!facetapi_deactivate_widget !facetapi_accessible_markup', $replacements);
  $variables['options']['html'] = TRUE;
  // Remove trailing text
  return theme_link($variables);
}

/**
 * Returns HTML for the deactivation widget.
 *
 * @param $variables
 *   An associative array containing the keys 'text', 'path', and 'options'. See
 *   the l() function for information about these variables.
 *
 * @see l()
 * @see theme_facetapi_link_active()
 *
 * @ingroup themable
 */
function models_facetapi_deactivate_widget($variables) {
  // Display trailing text as link.
  return $variables['text'];
}

/**
 * Implements hook_preprocess_entity.
 */
function models_preprocess_entity(&$variables) {
  if ($variables['entity_type'] == 'feedback') {
    $ew = entity_metadata_wrapper('feedback', $variables['elements']['#entity']->id);
    $nw = entity_metadata_wrapper('node', $variables['field_feedb_nid'][0]['nid']);

// dpm($ew->value());
// dpm($variables);

    if ($ew->field_feedb_type->value() == 'owner') {
      $mypic = $ew->uid->value()->picture;
      $u_id = $ew->uid->getIdentifier();
      $author = l($ew->uid->label(), 'user/' . $ew->uid->getIdentifier(), array('attributes' => array('class' => array('uname'))));
      $stars = $ew->uid->field_my_overall_rating->value() ? $ew->uid->field_my_overall_rating->value() : 0;
    }
    else {
      $mypic = $nw->author->value()->picture;
      $u_id = $nw->author->getIdentifier();
      $author = l($nw->author->label(), 'user/' . $nw->author->getIdentifier(), array('attributes' => array('class' => array('uname'))));
      $stars = $nw->author->field_my_overall_rating->value() ? $nw->author->field_my_overall_rating->value() : 0;
    }
    if ($mypic) {
      $pic = '<div class="my-image img-circle">' . l(theme('image_style', array(
          'style_name' => 'profile',
          'path' => $mypic->uri,
          'attributes' => array('class' => array('img-circle'))
        )), 'user/' . $u_id, array('html' => TRUE)) . '</div>';
    }
    else {
      $pic = '<div class="my-image img-circle">' . l(theme('image_style', array(
          'style_name' => 'profile',
          'path' => 'public://pictures/picture-default.png',
          'attributes' => array('class' => array('img-circle'))
        )), 'user/' . $u_id, array('html' => TRUE)) . '</div>';
    }

    $variables['pic'] = $pic;
    $variables['author'] = $author;
    $variables['type'] = '<div class="field-name-field-feedb-type">' . t('as: ') . $ew->field_feedb_type->value() . '</div>';

    $variables['comment_type'] = $ew->field_feedb_type->value() == 'owner' ? '<div class="field-name-field-feedb-type type-client">' . t('Client') . '</div>' : '<div class="field-name-field-feedb-type type-owner">' . t('Job Owner') . '</div>';

    $variables['author_rating'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $stars . '"></div>';
    $variables['stars'] = '<div class="hb-rating raty raty-readonly" data-rating="' . $ew->field_rating->value() . '"></div>';
    $variables['job'] = l($nw->label(), 'node/' . $nw->getIdentifier()) . ' <span class="fb-created">(' . format_date($ew->created->value(), 'normal', 'Y-m-d H:i:s', 'UTC') . ')</span>';
  }
}

function models_preprocess_views_view_fields(&$vars) {
  if ($vars['view']->name == 'jobs_rhs') {
    if ($vars['view']->current_display == 'block') {
      $nw = entity_metadata_wrapper('node', arg(1));
      $vars['fields']['field_hb_price']->content = $nw->field_hb_price_text->value() ? '<p><i class="fa fa-dollar"></i> ' . $nw->field_hb_price_text->value() . '</p>' : FALSE;
    }

  }
}

function models_preprocess_views_view(&$vars) {
  // if ($vars['name'] == 'related_jobs_by_terms') {
  //   $vars['view']->human_name = 'waaa';
  // }
  if ($vars['name'] == 'jobs_rhs') {
    if ($vars['display_id'] == 'block') {
      global $user;
      $uw = entity_metadata_wrapper('user', $user->uid);
      $nw = entity_metadata_wrapper('node', arg(1));

      // If job is NOT assigned..
      if (!$nw->field_hb_assigned->value()) {

        // If job is NOT published..
        if (!$nw->status->value()) {

          if ($nw->field_hb_type->value() != 'personal') {
            $job_publish_text = !$nw->field_hb_paused->value() ? t('Publish Job') : t('Resume Job');
          }
          else {
            $job_publish_text = !$nw->field_hb_paused->value() ? t('Publish') : t('Resume!');
          }

          $job_publish = l($job_publish_text, '#', array(
            'attributes' => array(
              'data-toggle' => array('modal'),
              'data-target' => array('#job-publish-form-popup'),
              'class' => array('btn btn-success btn-block')
            )
          ));
          $vars['job_publish_button'] = ($nw->author->getIdentifier() != 000) ? '<div class="hb-rhs-job-button">' . $job_publish . '</div>' : FALSE;
        }
        // If job is published..
        else {
          $btn_text = $nw->field_hb_type->value() != 'personal' ? t('Request Job') : t('Offer Service');
          $btn_class = 'btn-info';
          if ($nw->field_hb_users_eck->value()) {
            foreach ($nw->field_hb_users_eck->getIterator() as $k => $u) {
              if ($u->field_feedb_user->getIdentifier() == $uw->getIdentifier()) {
                $btn_text = $nw->field_hb_type->value() != 'personal' ? t('Remove Request') : t('Remove Offer');
                $btn_class = 'btn-danger';
                break;
              }
            }
          }

          if ($nw->author->getIdentifier() != $uw->getIdentifier()) {
            if ($user->uid != 0) {
              $job_details = l($btn_text, '#', array(
                'attributes' => array(
                  'data-toggle' => array('modal'),
                  'data-target' => array('#job-request-form-popup'),
                  'class' => array('btn btn-block ' . $btn_class)
                )
              ));
            }
            else {
              $job_details = l($btn_text, 'user/login', array('attributes' => array('class' => array('btn btn-block ' . $btn_class))));
            }
          }
          else {
            $job_details = l(t('Edit Job'), 'job/' . $nw->getIdentifier() . '/edit', array('attributes' => array('class' => array('btn btn-block btn-success'))));
          }
          $vars['job_button'] = '<div class="hb-rhs-job-button">' . $job_details . '</div>';
        }
      }
      else {
        // Author to leave feedback
        if ($uw->getIdentifier() == $nw->author->getIdentifier()) {
          $fb_completed = $nw->field_hb_feedb_size->value() == $nw->field_hb_client_size->value() ? TRUE : FALSE;
          $fbk_desc = $fb_completed ? t('Feedback is complete - click below to view') : t('Your job has been assigned - to leave feedback click below');
          $fbk_btn_text = $fb_completed ? t('View Feedback') : t('Leave Feedback');
        }
        else {
          // Allow feedback if this user is an active client of the job.
          $uw_label = str_replace(' ', '_', strtolower($uw->label()));
          $title = 'client_' . $uw_label . '_uid_' . $uw->getIdentifier() . '_nid_' . $nw->getIdentifier();
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', 'feedback')
            ->entityCondition('bundle', 'feedback')
            ->propertyCondition('title', $title, '=')
            ->fieldCondition('field_client_selected', 'value', 1, '=');
          $result = $query->execute();

          if (sizeof($result)) {
            // Now to check that the client has completed their feedback to the owner.
            $title = '%_aid_' . $nw->author->getIdentifier() . '_uid_' . $uw->getIdentifier() . '_nid_' . $nw->getIdentifier() . '%';
            $query = new EntityFieldQuery();
            $query->entityCondition('entity_type', 'feedback')
              ->entityCondition('bundle', 'feedback')
              ->propertyCondition('title', $title, 'like');
            $result = $query->execute();

            if (sizeof($result)) {
              $aid = reset($result['feedback'])->id;
              $aw = entity_metadata_wrapper('feedback', $aid);
              if ($aw->field_feedb_received->value()) {
                $fbk_btn_text = t('View Feedback');
                $fbk_desc = t('Your job feedback is complete - click below to view');;
              }
              else {
                $fbk_desc = t('You can now leave feedback for the job owner');
                $fbk_btn_text = t('Leave Feedback');
              }
            }
          }
          else {
            $fbk_btn_text = FALSE;
            $fbk_desc = t('This Job has expired.') . ' ' . l(t('Click here to view more jobs'), 'search');
          }
        }

        if ($fbk_btn_text) {
          $vars['job_button'] = '<p class="feedback-note"><strong>' . $fbk_desc . '</strong></p>';
          $vars['feedback_button'] = '<div class="hb-rhs-job-button">' . l($fbk_btn_text, 'job/' . $nw->getIdentifier() . '/feedback', array('attributes' => array('class' => array('btn btn-danger btn-block')))) . '</div>';
        }
        else {
          $vars['job_button'] = '<p class="feedback-note"><strong>' . $fbk_desc . '</strong></p>';;
          $vars['feedback_button'] = FALSE;
        }
      }
    }
  }
}

/**
 * Quick function to dpm only one call from a loop etc.
 */
function dpm_once($input, $name = NULL, $type = 'status') {
  $backtrace = debug_backtrace();
  $caller = array_shift($backtrace);
  $executed = &drupal_static(__FUNCTION__ . $caller['file'] . $caller['line'], FALSE);
  if (!$executed) {
    $executed = TRUE;
    if (function_exists('dpm')) {
      dpm($input, $name, $type);
    }
  }
}
