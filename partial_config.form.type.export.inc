<?php

/**
 * Gets all fields and field groups for a specific node type.
 *
 * @param string $node_type
 *   The machine name of the node type.
 *
 * @return array
 *   An array containing fields and field groups.
 */
function partial_config_get_fields_and_groups($node_type) {
  $result = array('fields' => array(), 'groups' => array());

  // Load the node type.
  $type = node_type_load($node_type);
  if (!$type) {
    return $result; // Node type not found.
  }

  // Retrieve fields.
  $fields = field_info_instances('node', $node_type);
  foreach ($fields as $field_name => $field) {
    $result['fields'][$field_name] = $field;
  }

  // Retrieve field groups (if Field Group module is enabled).
  if (module_exists('field_group')) {
    $groups = field_group_read_groups(array('entity_type' => 'node', 'bundle' => $node_type));
    if (!empty($groups['node'][$node_type])) {
      foreach ($groups['node'][$node_type] as $group_name => $group) {
        $result['groups'][$group_name] = $group;
      }
    }
  }

  return $result;
}


function partial_config_export_type_form($form, &$form_state) {
  // Get the available node types.
  $node_types = node_type_get_names();

  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Config'),
  );

  // Content type selector with AJAX callback.
  $form['export']['node_types'] = array(
    '#type' => 'select',
    '#title' => t('Content Type:'),
    '#options' => $node_types,
    '#default_value' => isset($form_state['values']['node_types']) ? $form_state['values']['node_types'] : '',
    '#ajax' => array(
      'callback' => 'partial_config_export_type_ajax_callback',
      'wrapper' => 'fields-wrapper',
    ),
  );

  // Wrapper for fields and groups, updated by AJAX.
  $form['export']['fields_wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'fields-wrapper'),
  );

  // Load fields and groups if a content type is selected.
  if (!empty($form_state['values']['node_types'])) {
    $selected_type = $form_state['values']['node_types'];

    // Load fields and groups.
    $fields_and_groups = partial_config_get_fields_and_groups($selected_type);
    $fields = $fields_and_groups['fields'];
    $groups = $fields_and_groups['groups'];

    // Combine fields and groups into one array for the table.
    $options = [];
    foreach ($fields as $field_name => $field_info) {
      $options[$field_name] = [
        'name' => $field_info['label'],
        // Add additional columns as needed.
        'type' => $field_info['type'],
        // ... other field details ...
      ];
    }
    foreach ($groups as $group_name => $group_info) {
      $options[$group_name] = [
        'name' => $group_info['label'],
        // Add additional columns as needed.
        // ... other group details ...
      ];
    }

    // Table select for fields and groups.
    $form['export']['fields_wrapper']['fields_and_groups'] = array(
      '#type' => 'tableselect',
      '#header' => array('Name', 'Type', /* other headers */),
      '#options' => $options,
      '#empty' => t('No fields or groups available'),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
  );

  return $form;
}

function partial_config_export_type_ajax_callback($form, &$form_state) {
  return $form['export']['fields_wrapper'];
}

function partial_config_export_type_form_validate($form, &$form_state) {

}



function partial_config_export_type_form_submit($form, &$form_state) {

}
