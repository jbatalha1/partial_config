<?php

/**
 * Implements hook_menu().
 */
function partial_config_menu() {
  $items['admin/config/development/configuration/content_type'] = array(
    'title' => 'Content Type Import/Export',
    'page callback' => 'backdrop_get_form',
    'page arguments' => array('config_import_single_form'),
    'access arguments' => array('synchronize configuration'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 1,
  );

  $items['admin/config/development/configuration/content_type/import'] = array(
    'title' => 'Import',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  $items['admin/config/development/configuration/content_type/export'] = array(
    'title' => 'Export',
    'page callback' => 'backdrop_get_form',
    'page arguments' => array('partial_config_export_type_form'),
    'access arguments' => array('synchronize configuration'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 1,
  );

  return $items;
}
