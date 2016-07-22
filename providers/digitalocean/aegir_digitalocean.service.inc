<?php

module_load_include('service.inc', 'aegir_cloud');

/**
 * Digital Ocean provider.
 */
class hostingService_provider_digital_ocean extends hostingService_provider {
  public $type = 'digital_ocean';
  public $name = 'DigitalOcean';

  function form(&$form) {
    parent::form($form);

    // Don't allow editing.
    if (!$this->server->nid) {
      $default_options = variable_get('aegir_digital_ocean_default_options', array());
      $options = $this->getDigitalOceanOptions();

      // If there are no options, show a link to the settings form.
      if (empty($options)) {
        $form['warning'] = array(
            '#markup' => t('You must first configure your !link to use this provider.', array(
                    '!link' => l(t('DigitalOcean Credentials'), 'admin/hosting/cloud'))
            ),
        );
        return;
      }

      $form['provider_options'] = array();
      $form['provider_options']['region'] = array(
        '#type' => 'select',
        '#title' => t('Region'),
        '#options' => $options['regions'],
        '#default_value' => $default_options['aegir_digital_ocean_default_region'],
      );
      $form['provider_options']['image'] = array(
        '#type' => 'select',
        '#title' => t('Image'),
        '#options' => $options['images'],
        '#default_value' => $default_options['aegir_digital_ocean_default_image'],
      );
      $form['provider_options']['size'] = array(
        '#type' => 'select',
        '#title' => t('Server Size'),
        '#options' => $options['sizes'],
        '#default_value' => $default_options['aegir_digital_ocean_default_size'],
      );
      $form['provider_options']['keys'] = array(
        '#type' => 'checkboxes',
        '#title' => t('SSH Keys'),
        '#options' => $options['keys'],
        '#default_value' => $default_options['aegir_digital_ocean_default_keys'],
      );
      $form['provider_options']['backups'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable Backups'),
        '#default_value' => $default_options['aegir_digital_ocean_default_backups'],
      );
      $form['provider_options']['ipv6'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable IPv6'),
        '#default_value' => $default_options['aegir_digital_ocean_default_ipv6'],
      );
      $form['provider_options']['private_networking'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable Private Networking'),
        '#default_value' => $default_options['aegir_digital_ocean_default_private_networking'],
      );
      $form['provider_options']['remote_server'] = array(
        '#type' => 'checkbox',
        '#title' => t('Setup as remote aegir server'),
        '#default_value' => $default_options['aegir_digital_ocean_default_remote_server'],
      );
      //$form['provider_options']['cloud_config'] = array(
      //  '#type' => 'textarea',
      //  '#title' => t('Cloud Config'),
      //  '#default_value' => $default_options['aegir_digital_ocean_default_cloud_config'],
      //);
    }
  }

  /**
   * Process options
   */
  function getDigitalOceanOptions() {
    $options = variable_get('aegir_cloud_digital_ocean_options', array());
    return $options;
  }

  public function context_options($task_type, $ref_type, &$task) {
    parent::context_options($task_type, $ref_type, $task);
    $task->context_options['digital_ocean_token'] = variable_get('aegir_cloud_digital_ocean_api_token', NULL);
  }
}