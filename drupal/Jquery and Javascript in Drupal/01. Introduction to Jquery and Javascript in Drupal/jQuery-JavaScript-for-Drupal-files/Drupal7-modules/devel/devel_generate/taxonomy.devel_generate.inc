<?php
//$Id: taxonomy.devel_generate.inc,v 1.3 2010/03/18 13:14:46 weitzman Exp $

function taxonomy_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_taxonomy_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _taxonomy_devel_generate($object, $field, $instance, $bundle);
  }
}

function _taxonomy_devel_generate($object, $field, $instance, $bundle) {
  $object_field = array();
  // TODO: For free tagging vocabularies that do not already have terms, this
  // will not result in any tags being added.
  // Insert new data:
  $max = db_query('SELECT MAX(tid) FROM taxonomy_term_data')->fetchField();
  $candidate = mt_rand(1, $max);
  $query = db_select('taxonomy_term_data', 't');
  $tid = $query
            ->fields('t', array('tid'))
            ->condition('t.vid', $field['settings']['allowed_values'][0]['vid'], '=')
            ->condition('t.tid', $candidate, '>=')
            ->range(0,1)
            ->execute()
            ->fetchField();
  $object_field['tid'] = (int) $tid;
  return $object_field;
}